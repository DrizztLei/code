package sdu.embedded.Sonic.client;

import android.content.ContentProviderClient;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.RemoteException;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import sdu.embedded.Sonic.core.CoreManager;
import sdu.embedded.Sonic.echo.UltrasonicManager;

public class Dolphin implements ICoreStateCallback, IEchoStateCallback {
    static final String TAG = "Dolphin";

    private static final String version = "0.20";
    private static Dolphin dolphin = null;

    private static JSONObject gestureConfigs;

    private ICoreManager coreManager = null;
    private IEchoManager echoManager = null;

    private IDataReceiver receiver = null;
    private IGestureListener listener = null;
    private IDolphinStateCallback callback = null;

    private int sonicChannel = -1;

    private ContentResolver contentResolver;

    private int currentState = States.STOPPED.ordinal();

    private boolean isRestrictChannel = false;

    private static Context context = null;
    public static enum States {
        STOPPED, PREPARING, READY, WORKING, PAUSED
    }

    public int getCurrentState() {
        return currentState;
    }

    public static Dolphin getInstance(//单例模式设计,使只有一个dolphin对象
                                      AudioManager audioManager,
                                      ContentResolver contentResolver,
                                      IDolphinStateCallback callback,
                                      String result,Context context,
                                      IDataReceiver receiver,
                                      IGestureListener listener) throws DolphinException, JSONException {
        if (dolphin == null)
            dolphin = new Dolphin();
        if (dolphin.coreManager == null)
            dolphin.coreManager = CoreManager.getCoreManager(dolphin,result,context);
        if (dolphin.echoManager == null)
            dolphin.echoManager = UltrasonicManager.getEchoManager(
                    audioManager, dolphin);//声波管理器初始化

        if (audioManager == null || callback == null || contentResolver == null) {
            throw new DolphinException("audioManager/callback/contentResolver cannot be null");
        }
        if (listener == null && receiver == null) {
            throw new DolphinException("listener & receiver cannot be null at the same time");
        }

        dolphin.callback = callback;//回调类即mainactivity
        dolphin.contentResolver = contentResolver;
        if (receiver != null) {
            dolphin.receiver = receiver;
            dolphin.setDataReceiver(receiver);//数据接收监听
        }
        if (listener != null) {
            dolphin.listener = listener;
            dolphin.setGestureListener(listener);//手势监听
        }

        return dolphin;
    }

    public void setDataReceiver(IDataReceiver receiver) throws DolphinException {
        coreManager.setDataReceiver(receiver);
    }

    public void setGestureListener(IGestureListener listener) throws DolphinException, JSONException {
        coreManager.setGestureListener(listener);
        gestureConfigs = listener.getGestureConfig();
        if (gestureConfigs == null) {
            throw new DolphinException("gesture mask cannot be null");
        }
        JSONObject masks = gestureConfigs.getJSONObject("masks");
        if (masks.length() == 0) {
            throw new DolphinException("please turn on at least ONE gesture");
        }
        setGestureConfig(contentResolver, gestureConfigs);
    }

    private Dolphin() {
        // 收集信息，环境检查
        // 初始化超声环境，自我检测，调整参数
        // 开始工作
        Log.i(TAG, "version: " + version);
    }

    private JSONObject prepareGestureConfig(ContentResolver resolver, JSONObject gestureConfigs) {
        if (resolver == null && gestureConfigs.has("models")) return gestureConfigs;

        JSONObject config;
        ContentProviderClient providerClient = resolver.acquireContentProviderClient(
                DolphinCoreVariables.MODEL_PROVIDE_NAME);
        if (providerClient == null) {
            Log.e(TAG, "server not found, put default data");
            // default data
        } else {
            try {
                ContentValues contentValues = new ContentValues();
                contentValues.put("config", gestureConfigs.toString());
                Uri ret = providerClient.insert(Uri.parse("content://modelconfigs"), contentValues);
                Log.i(TAG, "ret Uri: " + ret.toString());
                try {
                    config = new JSONObject(ret.toString());
                } catch (JSONException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            } catch (RemoteException e) {
                Log.e(TAG, e.toString());
                Log.e(TAG, "server err, put default data");
            }
        }

        return gestureConfigs;
    }

    public void setGestureConfig(ContentResolver contentResolver, JSONObject gestureConfigs) throws JSONException {

        if (dolphin == null) return;
        if (dolphin.coreManager == null) return;
        dolphin.coreManager.setGestureConfig(
                prepareGestureConfig(contentResolver, gestureConfigs));
    }

    public void prepare(final Context ctx) throws DolphinException {
        if (UltrasonicManager.isTablet(ctx))
            restrictChannel();//针对平板设置

        Log.i(TAG, "prepare");
        if (currentState == States.PREPARING.ordinal()) {
            Log.i(TAG, "dolphin is already preparing");
            return;
        }
        if (currentState == States.WORKING.ordinal()) {
            Log.i(TAG, "dolphin is already working");
            return;
        }
        if (currentState == States.STOPPED.ordinal()
                || currentState == States.PAUSED.ordinal()) {

            currentState = States.PREPARING.ordinal();
            new Thread() {
                public void run() {
//					setGestureMask(contentResolver,gestureMasks);
//					echoManager.autoSwitchSpeaker(ctx);
                    echoManager.switchToLoudspeaker();   //?听筒和扬声器不能同时工作
                    // echoManager.emit(sonicChannel);
                    coreManager.peek();                 //AudioProcessThread和AudioFetchThread线程开始工作
                }

                ;
            }.start();
        } else {
            throw new DolphinException("Dolphin should be stopped before prepare, now is " + currentState);
        }

    }

    public void start() throws DolphinException {
        Log.i(TAG, "start");
        if (currentState == States.WORKING.ordinal()) {
            Log.i(TAG, "dolphin is already working");
            return;
        }
        if (currentState == States.READY.ordinal()) {
            coreManager.start();
            currentState = States.WORKING.ordinal();
        } else {
            throw new DolphinException("Dolphin should be core ready before start, now is " + currentState);
        }
    }

    public void pause() throws DolphinException {
        Log.i(TAG, "pause");
        if (currentState == States.PAUSED.ordinal()) {
            Log.i(TAG, "dolphin is already paused");
            return;
        }
        if (currentState == States.WORKING.ordinal()
                || currentState == States.PREPARING.ordinal()) {
            echoManager.kill(sonicChannel);
            coreManager.pause();
            currentState = States.PAUSED.ordinal();
        } else {
            throw new DolphinException("Dolphin should be working before pause, now is " + currentState);
        }

    }

    public void stop() throws DolphinException {
        Log.i(TAG, "stop");
        if (currentState == States.STOPPED.ordinal()) {
            Log.i(TAG, "dolphin is already stopped");
            return;
        }
        if (currentState == States.WORKING.ordinal()
                || currentState == States.PAUSED.ordinal()
                || currentState == States.PREPARING.ordinal()) {
            echoManager.kill(sonicChannel);
            coreManager.stop();
            currentState = States.STOPPED.ordinal();
        } else {
            throw new DolphinException("Dolphin should be working before pause, now is " + currentState);

        }
    }

    public void bringBackService(Context ctx) {
        Intent intent = new Intent(DolphinCoreVariables.REMOTE_SERVICE_NAME);
        intent.putExtra("resume", true);
        ctx.startService(intent);
    }

    public void restrictChannel() {
        isRestrictChannel = true;
    }

    @Override
    public void onCoreReady() {
        Log.i(TAG, "onCoreReady");
        currentState = States.READY.ordinal();
        callback.onCoreReady();
    }

    @Override
    public void onNoisy() {
        Log.i(TAG, "onNoisy");
        callback.onNoisy();
    }

    @Override
    public void onCoreFail() {
        Log.i(TAG, "onCoreFail");
        callback.onCoreFail();

    }

    @Override
    public void onNormal() {
        Log.i(TAG, "onNormal");
        callback.onNormal();
    }

    @Override
    public boolean onSelectSonic(int index) {
        Log.e(TAG, "onSelectSonic " + index);
        if (index < 0 || index > 2) return false;

        if (isRestrictChannel) {
            index = 2;
            Log.i(TAG, "isRestrictChannel to 2");
        }

        echoManager.kill(sonicChannel);
        echoManager.emit(index);//只需调用一次,UltrasonicEmitter中emit方法中有专门的线程,来一直发射超声波
        sonicChannel = index;

        coreManager.prepare();
        return !isRestrictChannel;
    }

    public String getChoice()
    {
        return callback.getChoice();
    }

    @Override
    public void writesucc() {
        callback.writesucc();
    }
}
