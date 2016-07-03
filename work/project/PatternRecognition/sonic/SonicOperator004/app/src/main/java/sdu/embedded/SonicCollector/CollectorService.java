package sdu.embedded.SonicCollector;

import android.annotation.SuppressLint;
import android.app.ActivityManager;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.media.AudioManager;
import android.os.Binder;
import android.os.IBinder;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Toast;

import com.hillsidewatchers.sdu.sonicoperator.Analyzer.OutputDataAnalyzer;
import com.hillsidewatchers.sdu.sonicoperator.DatabaseManager.DBSQLiteDao;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Map;

import sdu.embedded.Sonic.client.ContinuousGestureEvent;
import sdu.embedded.Sonic.client.Dolphin;
import sdu.embedded.Sonic.client.DolphinException;
import sdu.embedded.Sonic.client.GestureEvent;
import sdu.embedded.Sonic.client.IDataReceiver;
import sdu.embedded.Sonic.client.IDolphinStateCallback;
import sdu.embedded.Sonic.client.IGestureListener;
import sdu.embedded.Sonic.client.RealTimeData;

public class CollectorService extends Service implements

        IDolphinStateCallback {
    Dolphin dolphin = null;
    String result = "";
    Context context = this;
    DBSQLiteDao dbsqLiteDao = null;
    ActivityManager activityManager = null ;
    CollectorServerReceiver collectorServerReceiver = null;
    IntentFilter intentFilter = null;
    private static final String TAG = "CollectorService";
    private static final String mobile_operation = "mobile_operation";
    private static final String sonic_operation = "sonic_operation";
    private static final String connection = "connection";
    private static final String PULL = "pull";
    private static final String PUSH = "push";
    private static final String LEFT = "left";
    private static final String RIGHT = "right";
    private static final String UP = "up";
    private static final String DOWN = "down";




    IDataReceiver dataReceiver = new IDataReceiver() {

        @Override
        public void onData(RealTimeData data) {
            // TODO Auto-generated method stub
            // Log.i("RealTimeData", data.toString());
//            if (needCircle)
//                SimpleDrawCircle(data.radius);
//            if (needLine)
//                SimpleDrawLines(data.normal_info, data.feature_info,
//                        data.upperbound, data.lowerbound, data.velocity, data.toparr,
//                        data.boundarr, data.upperarr, data.lowerarr);
        }

        @Override
        public JSONObject getDataTypeMask() {
            // TODO Auto-generated method stub
            return null;
        }
    };
    IGestureListener gestureListener = new IGestureListener() {

        @Override
        public void onGesture(GestureEvent event) {
            // TODO Auto-generated method stub
//            if (event.isConclusion) {
//                Log.e("save", need_a_gesture + ":"
//                        + (event.rich_feature_data != null));
//                if (need_a_gesture && event.rich_feature_data != null) {
//                    saveGesture(event.rich_feature_data);
//                } else {
//                    need_a_gesture = false;
//                }
////                saveGesture(event.rich_feature_data);
//
////				saveAllGesture(event);
//                Log.e("log", event.toString());
//                DrawString(gesture_counter + " / " + all_gesture_counter + "  "
//                        + event.result);
//            }
            dbsqLiteDao = new DBSQLiteDao(context);
        }

        @Override
        public JSONObject getGestureConfig() {
            // claim the gesture you need to be true
//			JSONObject masks = new JSONObject();
//			JSONObject config = new JSONObject();
//			try {
//				for (int i = 1; i < GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i++) {
//					masks.put(""+i, true);
//				}
//				config.put("masks", masks);
//			} catch (JSONException e) {
//				Log.e("MainActivity", e.toString());
//			}
//			return config;

            // claim the gesture you need to be true

            JSONObject config = new JSONObject();
            JSONObject masks = new JSONObject();

            try {
                masks.put("" + GestureEvent.Gestures.SWIPE_LEFT_L.ordinal(),
                        true);
                masks.put("" + GestureEvent.Gestures.SWIPE_RIGHT_L.ordinal(),
                        true);
                masks.put("" + GestureEvent.Gestures.PULL_PUSH_PULL.ordinal(),
                        true);
                masks.put("" + GestureEvent.Gestures.PUSH_PULL_PUSH.ordinal(),
                        true);

                config.put("masks", masks);
            } catch (JSONException e) {
//                Log.e(TAG, e.toString());
            }

            return config;

        }

        @SuppressLint("LongLogTag")
        @Override
        public void onContinuousGestureStart(ContinuousGestureEvent event) {
            // TODO Auto-generated method stub
            Log.e("onContinuousGestureStart", event.toString());
            //DrawString(df.format(event.freq) + " Hz");
        }

        @SuppressLint("LongLogTag")
        @Override
        public void onContinuousGestureUpdate(ContinuousGestureEvent event) {
            // TODO Auto-generated method stub
            Log.e("onContinuousGestureUpdate", event.toString());
            //DrawString(df.format(event.freq) + " Hz");
        }

        @Override
        public void onContinuousGestureEnd() {
            // TODO Auto-generated method stub
            Log.e("onContinuousGestureEnd", "onContinuousGestureEnd");
            //DrawString("wave to start");

        }
    };
    @Override
    public void onCreate() {
        if(activityManager==null){
            activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        }
        try {
            dolphin = Dolphin.getInstance(
                    (AudioManager) getSystemService(Context.AUDIO_SERVICE),
                    getContentResolver(),
                    this,result,context,
                    dataReceiver, gestureListener);

        } catch (DolphinException e) {
            // TODO Auto-generated catch block
            Log.w("exception","DolphinException");
            e.printStackTrace();
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            Log.w("exception","JSONException");

            e.printStackTrace();
        }
    Log.i("debug","service is on");
        if(dolphin==null)
            Log.i("debug","dolphin is null");
        try {
            dolphin.prepare(getApplicationContext());//主任务开始
        } catch (DolphinException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        super.onCreate();

    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i("debug","service onstartcomm");
        try {
            dolphin = Dolphin.getInstance(
                    (AudioManager) getSystemService(Context.AUDIO_SERVICE),
                    getContentResolver(),
                    this,result,context,
                    dataReceiver, gestureListener);
        } catch (DolphinException e) {
            // TODO Auto-generated catch block
            Log.w("exception","DolphinException");
            e.printStackTrace();
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            Log.w("exception","JSONException");

            e.printStackTrace();
        }
        try {
            dolphin.prepare(getApplicationContext());//主任务开始
        } catch (DolphinException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        unregisterReceiver(collectorServerReceiver);
        try {
            dolphin.stop();
        } catch (DolphinException e) {
            e.printStackTrace();
        }
    }

    public CollectorService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        return new MsgBinder();
    }

    @Override
    public void onCoreReady() {
        Log.e("dolphin", "start");
        try {
            dolphin.start();
        } catch (DolphinException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    @Override
    public void onNoisy() {
        Log.e("dolphin", "too nosiy");

    }

    @Override
    public void onCoreFail() {

    }

    @Override
    public void onNormal() {
        Log.i("dolphin", "normal working");

    }

    @Override
    public String getChoice() {
        return null;
    }

    @Override
    public void writesucc() {
        Vibrator vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        vibrator.vibrate(100);
    }
    public class MsgBinder extends Binder {
        /**
         * 获取当前Service的实例
         * @return
         */
        public CollectorService getService(){
            return CollectorService.this;
        }
    }
    public class CollectorServerReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.e("MainActivity","MainActivity的receiver已经收到消息");
            int result = (int) intent.getExtras().get("result");
            Log.e(TAG,String.valueOf(result));
            /**
             * OutputDataAnalyzer outputDataAnalyzer = new OutputDataAnalyzer();
             outputDataAnalyzer.outputData(record_map.get("info"));
             */
            //pull push left right up down
            switch (result){
//                case 0:
//                    Toast.makeText(context,"识别出的手势为："+PULL,Toast.LENGTH_SHORT).show();
//                    DoAction(PULL);
//                    break;
//                case 1:
//                    Toast.makeText(context,"识别出的手势为："+PUSH,Toast.LENGTH_SHORT).show();
//                    DoAction(PUSH);
//                    break;
//                case 2:
//                    Toast.makeText(context,"识别出的手势为："+LEFT,Toast.LENGTH_SHORT).show();
//                    DoAction(LEFT);
//                    break;
//                case 3:
//                    Toast.makeText(context,"识别出的手势为："+RIGHT,Toast.LENGTH_SHORT).show();
//                    DoAction(RIGHT);
//                    break;
//                case 4:
//                    Toast.makeText(context,"识别出的手势为："+UP,Toast.LENGTH_SHORT).show();
//                    DoAction(UP);
//                    break;
//                case 5:
//                    Toast.makeText(context,"识别出的手势为："+DOWN,Toast.LENGTH_SHORT).show();
//                    DoAction(DOWN);
//                    break;

                case 0:
                    Toast.makeText(context,"识别出的手势为："+LEFT,Toast.LENGTH_SHORT).show();
                    DoAction(LEFT);
                    break;
                case 1:
                    Toast.makeText(context,"识别出的手势为："+RIGHT,Toast.LENGTH_SHORT).show();
                    DoAction(RIGHT);
                    break;
                case 2:
                    Toast.makeText(context,"识别出的手势为："+UP,Toast.LENGTH_SHORT).show();
                    DoAction(UP);
                    break;
                case 3:
                    Toast.makeText(context,"识别出的手势为："+DOWN,Toast.LENGTH_SHORT).show();
                    DoAction(DOWN);
                    break;
                /**
                 * 此处如果切换成小红点模式，再做处理
                 */

            }
//            Toast.makeText(context,"识别出的手势为："+result,Toast.LENGTH_SHORT).show();
        }
    }


    private void DoAction(String gesture){
        Log.e(TAG,"DoAction:"+gesture);
        Map<String,String> sonic_map ;
        Map<String,String> connection_map;
        Map<String,String> record_map;
        if(dbsqLiteDao==null){
            dbsqLiteDao = new DBSQLiteDao(context);
        }
        sonic_map = dbsqLiteDao.query(sonic_operation," info = ?",new String[]{gesture});
        if(sonic_map.size()!=0){
            String gesture_name = sonic_map.get("name");
            connection_map = dbsqLiteDao.query(connection," gesture_name = ?",new String[]{gesture_name});
            String record_name = connection_map.get("record_name");
            Toast.makeText(context, "开始播放从数据库中找到的屏幕操作的属性", Toast.LENGTH_SHORT).show();
            ComponentName cn = activityManager.getRunningTasks(1).get(0).topActivity;
            String packageName = cn.getPackageName();
            Log.e(TAG,"顶层应用的包名是"+packageName);
            //用于点击播放按钮，做播放处理
            record_map = dbsqLiteDao.query(mobile_operation,"packagename=? and name=?",new String[]{packageName,record_name
            });
            if((record_map!=null)&&(record_map.size()!=0)&&!record_map.get("info").equals("")){
                Log.e(TAG,record_map.get("info"));
                OutputDataAnalyzer outputDataAnalyzer = new OutputDataAnalyzer();
                outputDataAnalyzer.outputData(record_map.get("info"));
            }
            else {
                Toast.makeText(context,"数dsfs据库中没有找到该应用下的操作信息，请进行录制",Toast.LENGTH_SHORT).show();
                Log.e(TAG,"从数据库中没有找到这个名字，这个包名的动作");
            }
        }
        else {
//            Toast.makeText(context,"没有查询到之前有过这个手势",Toast.LENGTH_SHORT).show();
        }
    }
    public void registReceiver(){
        intentFilter = new IntentFilter();
        collectorServerReceiver = new CollectorServerReceiver();
        intentFilter.addAction("com.hillsidewatchers.sdu.sonicoperator.collectorServerReceiver");
        registerReceiver(collectorServerReceiver,intentFilter);
    }

    @Override
    public boolean onUnbind(Intent intent) {
        return super.onUnbind(intent);

    }

}
