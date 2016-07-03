package sdu.embedded.Sonic.core;

import android.content.Context;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import sdu.embedded.Sonic.client.ContinuousGestureEvent;
import sdu.embedded.Sonic.client.DolphinCoreVariables;
import sdu.embedded.Sonic.client.GestureEvent;
import sdu.embedded.Sonic.client.ICoreManager;
import sdu.embedded.Sonic.client.ICoreStateCallback;
import sdu.embedded.Sonic.client.IDataReceiver;
import sdu.embedded.Sonic.client.IGestureListener;
import sdu.embedded.Sonic.client.RealTimeData;

public class CoreManager implements ICoreManager {

    static final String TAG = "CoreManager";

    private static CoreManager coreManager;
    private static ICoreStateCallback callback;

    private IDataReceiver receiver = null;
    private IGestureListener listener = null;

    private List<short[]> shortResultList = new LinkedList<short[]>(); // FFT 处理后的数据
    private List<RealTimeData> realTimeDataList = null;
    private List<GestureEvent> gestureEventList = null;

    private boolean isWorking = false;
    private boolean isSingle = true;

    private AudioFetchThread audioFetchThread = null;
    private AudioProcessThread audioProcessThread = null;
    private GestureEventDispatcher eventDispatcher = null;
    private RealTimeDataDispatcher dataDispatcher = null;
    public  String result = "";
    Context context = null;
    public static CoreManager getCoreManager(ICoreStateCallback callback,String result,Context context) {
        CoreManager.callback = callback;
        if (coreManager != null) {
            coreManager.receiver = null;
            coreManager.listener = null;
            if (coreManager.realTimeDataList != null)
                coreManager.realTimeDataList.clear();
            if (coreManager.gestureEventList != null)
                coreManager.gestureEventList.clear();
            coreManager.audioFetchThread = null;
            coreManager.audioProcessThread = null;
            coreManager.eventDispatcher = null;
            coreManager.dataDispatcher = null;
        }
        return coreManager == null ? coreManager = new CoreManager(result,context) : coreManager;
    }

    private CoreManager(String result,Context context) {
        this.result = result;
        this.context = context;
//		audioFetchThread = new AudioFetchThread(fftResultList);
//		audioProcessThread = new AudioProcessThread(fftResultList,
//				realTimeDataList,gestureEventList);
    }

    @Override
    public void setDataReceiver(IDataReceiver receiver) {
        if (receiver == null) {
            this.receiver = null;
            if (isWorking) dataDispatcher.stopGracefully();

            AudioProcessThread.needRealtimeData = false;
            Log.i(TAG, "setDataReceiver to null");

        } else {
            this.receiver = receiver;

            if (realTimeDataList == null)
                realTimeDataList = new LinkedList<RealTimeData>();

            if (dataDispatcher == null || !dataDispatcher.isAlive()) {
                dataDispatcher = new RealTimeDataDispatcher();
                if (isWorking) dataDispatcher.start();
            }
            AudioProcessThread.needRealtimeData = true;
            Log.i(TAG, "setDataReceiver ok");
        }
    }

    @Override
    public void setGestureListener(IGestureListener listener) {
        if (listener == null) {
            this.listener = null;
            if (isWorking) eventDispatcher.stopGracefully();

            AudioProcessThread.needGesture = false;
            Log.i(TAG, "setGestureListeners to null");
        } else {
            this.listener = listener;

            if (gestureEventList == null)
                gestureEventList = new LinkedList<GestureEvent>();

            if (eventDispatcher == null || !eventDispatcher.isAlive()) {
                eventDispatcher = new GestureEventDispatcher();
                if (isWorking) eventDispatcher.start();
            }
            AudioProcessThread.needGesture = true;
            Log.i(TAG, "setGestureListeners ok");

        }

    }

    @Override
    public boolean isWorking() {
        return isWorking;
    }

    @Override
    public void setSingleMode(boolean isSingle) {
        this.isSingle = isSingle;
    }

    @Override
    public boolean isSingle() {
        return isSingle;
    }

    @Override
    public void prepare() {
        Log.i(TAG, "prepare");

        audioProcessThread.turnToPrepare();
    }

    public void start() {
        Log.i(TAG, "start");

        audioProcessThread.turnToRealWork();
        audioFetchThread.turnToRealWork();

        isWorking = true;

        if (eventDispatcher != null) {
            (eventDispatcher = new GestureEventDispatcher()).start();

        }
        if (dataDispatcher != null) {
            (dataDispatcher = new RealTimeDataDispatcher()).start();

        }
    }

//	@Override
//	public void resume() {
//		Log.i(TAG, "resume");
//		
//		if(AudioFetchThread.isPreparing && AudioProcessThread.isPreparing){
//			Log.i(TAG, "after perpare resume");
//			return;
//		}
//		
//		Log.i(TAG, "nomal resume");
//
//		shortResultList.clear();
//		if(realTimeDataList != null)
//			realTimeDataList.clear();
//		if(gestureEventList != null)
//			gestureEventList.clear();
//		
//		(audioProcessThread = new AudioProcessThread(
//				callback,
//				shortResultList,
//				realTimeDataList,
//				gestureEventList)).start();
//		
//		(audioFetchThread = new AudioFetchThread(shortResultList)).start();
//		
//		if(eventDispatcher != null)
//			(eventDispatcher = new GestureEventDispatcher()).start();
//		if(dataDispatcher != null)
//			(dataDispatcher = new RealTimeDataDispatcher()).start();
//	}

    @Override
    public void pause() {
        Log.i(TAG, "pause");

        isWorking = false;

        if (audioFetchThread != null)
            audioFetchThread.stopGracefully();
        if (audioProcessThread != null)
            audioProcessThread.stopGracefully();
        if (eventDispatcher != null)
            eventDispatcher.stopGracefully();
        if (dataDispatcher != null)
            dataDispatcher.stopGracefully();

    }

    @Override
    public void stop() {
        Log.i(TAG, "stop");
        pause();
    }


    @Override
    public void peek() {
        Log.i(TAG, "peek");
        (audioProcessThread = new AudioProcessThread(
                callback,
                shortResultList,//shortResultList代表的是fft处理后的数据,但是在本类中并未有获取后对它的处理
                realTimeDataList,
                gestureEventList,result,context)).start();

        (audioFetchThread = new AudioFetchThread(shortResultList)).start();
    }

    class RealTimeDataDispatcher extends Thread {

        static final String TAG = "RealTimeDataDispatcher";
        boolean isDispatching = false;

        public void stopGracefully() {
            isDispatching = false;
            synchronized (realTimeDataList) {
                realTimeDataList.clear();
                realTimeDataList.notifyAll();
            }
            Log.i(TAG, "stopped Gracefully");

        }

        @Override
        public void run() {
            Log.i(TAG, "run");

            isDispatching = true;
            List<RealTimeData> list = null;
            RealTimeData data = null;
            while (isDispatching) {
                if (realTimeDataList == null) {
                    Log.i(TAG, "realTimeDataList is null, will stop");
                    return;
                }
                synchronized (realTimeDataList) {
                    if (realTimeDataList.size() == 0) {
                        try {
                            realTimeDataList.wait();
                        } catch (InterruptedException e) {
                            Log.e(TAG, e.toString());
                        }
                    }
                    list = (LinkedList<RealTimeData>) ((LinkedList<RealTimeData>) realTimeDataList).clone();
                    realTimeDataList.clear();
                }
                while (list.size() != 0) {
                    data = list.get(0);
                    list.remove(0);
                    if (data == null) continue;
                    if (receiver == null) return;
                    receiver.onData(data);
                }
            }
            Log.i(TAG, "run end");
        }
    }

    class GestureEventDispatcher extends Thread {
        static final String TAG = "GestureEventDispatcher";

        boolean isDispatching = false;

        public void stopGracefully() {
            isDispatching = false;
            synchronized (gestureEventList) {
                gestureEventList.clear();
                gestureEventList.notifyAll();
            }
            Log.i(TAG, "stopped Gracefully");
        }

        @Override
        public void run() {
            Log.i(TAG, "run");

            isDispatching = true;
            List<GestureEvent> list = null;
            GestureEvent event = null;
            boolean isContinue = false;

            while (isDispatching) {
                if (gestureEventList == null) {
                    Log.i(TAG, "gestureEventList is null, will stop");
                    return;
                }
                synchronized (gestureEventList) {
                    if (gestureEventList.size() == 0) {
                        try {
                            gestureEventList.wait();
                        } catch (InterruptedException e) {
                            Log.e(TAG, e.toString());
                        }
                    }
                    list = (LinkedList<GestureEvent>) ((LinkedList<GestureEvent>) gestureEventList).clone();
                    gestureEventList.clear();
                }
                while (list.size() != 0) {
                    event = list.get(0);
                    list.remove(0);
                    if (event == null) continue;
                    if (listener == null) return;
                    if (event instanceof ContinuousGestureEvent) {
                        ContinuousGestureEvent event2 = (ContinuousGestureEvent) event;
                        if (event2.isEnd) {
                            listener.onContinuousGestureEnd();
                            isContinue = false;
                        } else if (!isContinue) {
                            listener.onContinuousGestureStart(event2);
                            isContinue = true;
                        } else {
                            listener.onContinuousGestureUpdate(event2);
                        }
                    } else {
                        listener.onGesture(event);
                    }
                }
            }
            Log.i(TAG, "run end");
        }
    }

    @Override
    public void setGestureConfig(JSONObject config) throws JSONException {
        Log.i(TAG, "setGestureMask");

        // mask filter
        // apply constants in audio process thread
        CoreSettings.mask_flags = getMasksFlags(config.getJSONObject("masks"));

        // load models
        JSONArray models;
        if (!config.has("models"))
            models = DolphinCoreVariables.DEFAULT_MODEL_CONFIG.getJSONArray("models");
        else
            models = config.getJSONArray("models");
        String[] modelString = new String[5];
        for (int i = 1; i < 5; i++) {
            modelString[i] = models.getString(i - 1);
        }

        try {
            LinearTest.setModel(modelString);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            Log.e(TAG, "models not found");
        }

        // load output table
        JSONArray outputs = null;
        if (!config.has("outputs"))
            outputs = DolphinCoreVariables.DEFAULT_MODEL_CONFIG.getJSONArray("outputs");
        else
            outputs = config.getJSONArray("outputs");

        for (int i = 0; i < 4; i++) {
            JSONArray singleOutput = outputs.getJSONArray(i);
            for (int j = 0; j < singleOutput.length(); j++) {
                CoreSettings.outputTable[i][j] = Integer.parseInt(singleOutput.getString(j));
            }
        }

        // gesture group count
        int[] group = new int[4];

        if (CoreSettings.mask_flags[GestureEvent.Gestures.PUSH_PULL.ordinal()]) group[0]++;
        for (int i = GestureEvent.Gestures.SWIPE_LEFT_L.ordinal(); i <= GestureEvent.Gestures.SWIPE_RIGHT_P.ordinal(); i++) {
            if (CoreSettings.mask_flags[i]) group[0]++;
        }

        if (CoreSettings.mask_flags[GestureEvent.Gestures.PULL_PUSH.ordinal()]) group[1]++;
        for (int i = GestureEvent.Gestures.SWING_LEFT_L.ordinal(); i <= GestureEvent.Gestures.SWING_RIGHT_P.ordinal(); i++) {
            if (CoreSettings.mask_flags[i]) group[1]++;
        }

        if (CoreSettings.mask_flags[GestureEvent.Gestures.PUSH_PULL_PUSH_PULL.ordinal()]) group[2]++;
        for (int i = GestureEvent.Gestures.SWIPE_BACK_LEFT_L.ordinal(); i <= GestureEvent.Gestures.SWIPE_BACK_RIGHT_P.ordinal(); i++) {
            if (CoreSettings.mask_flags[i]) group[2]++;
        }

        for (int i = GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i <= GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i++) {
            if (CoreSettings.mask_flags[i]) group[3]++;
        }

        CoreSettings.gesture_group = group;
    }

    static boolean[] getMasksFlags(JSONObject masks) {
        Log.i(TAG, "getMasksFlags");
        boolean[] masks_ret = new boolean[GestureEvent.gesture.length];
        for (int i = 0; i < GestureEvent.gesture.length; i++) {
            if (masks.has("" + i)) {
                masks_ret[i] = true;
                Log.i(TAG, "gesture enabled: " + GestureEvent.gesture[i]);
            }
        }
        return masks_ret;
    }

}

