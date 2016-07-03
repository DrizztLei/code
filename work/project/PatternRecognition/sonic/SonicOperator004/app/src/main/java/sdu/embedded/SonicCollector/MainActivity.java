//package sdu.embedded.SonicCollector;
//
//import android.content.ComponentName;
//import android.content.Context;
//import android.content.Intent;
//import android.content.ServiceConnection;
//import android.graphics.Canvas;
//import android.graphics.Color;
//import android.graphics.DashPathEffect;
//import android.graphics.Paint;
//import android.graphics.Path;
//import android.graphics.PathEffect;
//import android.graphics.Rect;
//import android.media.AudioManager;
//import android.os.Build;
//import android.os.Bundle;
//import android.os.Handler;
//import android.os.IBinder;
//import android.os.Message;
//import android.os.Vibrator;
//import android.support.v4.app.FragmentActivity;
//import android.support.v4.view.ViewPager;
//import android.util.Log;
//import android.view.SurfaceView;
//import android.view.View;
//import android.view.Window;
//import android.view.WindowManager;
//import android.widget.AdapterView;
//import android.widget.ArrayAdapter;
//import android.widget.Button;
//import android.widget.Spinner;
//import android.widget.TextView;
//import android.widget.Toast;
//import android.widget.ZoomControls;
//
//import org.json.JSONException;
//import org.json.JSONObject;
//
//import java.io.File;
//import java.io.FileNotFoundException;
//import java.io.FileOutputStream;
//import java.io.IOException;
//import java.io.ObjectOutputStream;
//import java.text.DecimalFormat;
//import java.util.ArrayList;
//
//import sdu.embedded.Sonic.client.ContinuousGestureEvent;
//import sdu.embedded.Sonic.client.Dolphin;
//import sdu.embedded.Sonic.client.DolphinException;
//import sdu.embedded.Sonic.client.GestureData;
//import sdu.embedded.Sonic.client.GestureEvent;
//import sdu.embedded.Sonic.client.IDataReceiver;
//import sdu.embedded.Sonic.client.IDolphinStateCallback;
//import sdu.embedded.Sonic.client.IGestureListener;
//import sdu.embedded.Sonic.client.RealTimeData;
//import seu.lab.dolphincore.R;
//
//public class MainActivity extends FragmentActivity implements
//        IDolphinStateCallback {
//
//    static public String TAG = "MainActivity";
//
//    // Button btnStart,btnExit; //开始停止按钮
//    SurfaceView sfv; // 绘图所用
//    ZoomControls zctlX, zctlY;// 频谱图缩放
//    Spinner spinner;// 下拉菜单
//    ArrayList<String> list = new ArrayList<String>();
//    ArrayAdapter<String> adapter;// 下拉菜单适配器
//
//    TextView tView;
//    private ViewPager mPager;
//    private PictureSlidePagerAdapter mPagerAdapter;
//
//    private int shift = 30;
//    public int frequence = 0;
//
//    private int length = 256;
//    // y轴缩小的比例
//    public int rateY = 21;
//    // y轴基线
//    public int baseLine = 0;
//    // 初始化画图的一些参数
//
//    FileOutputStream fos;
//    ObjectOutputStream oos;
//
//    FileOutputStream fos2;
//    ObjectOutputStream oos2;
//
//    private Paint mPaint;
//    private Paint tPaint;
//    private Paint xPaint;
//
//    private Paint dashPaint;
//
//    boolean stop = false;
//
//    Handler handler = new Handler();
//    private static final String [] choice ={"pull","push","left","right","up","down"};
//
//    Dolphin dolphin = null;
//    IDataReceiver dataReceiver = new IDataReceiver() {
//
//        @Override
//        public void onData(RealTimeData data) {
//            // TODO Auto-generated method stub
//            // Log.i("RealTimeData", data.toString());
//            if (needCircle)
//                SimpleDrawCircle(data.radius);
//            if (needLine)
//                SimpleDrawLines(data.normal_info, data.feature_info,
//                        data.upperbound, data.lowerbound, data.velocity, data.toparr,
//                        data.boundarr, data.upperarr, data.lowerarr);
//        }
//
//        @Override
//        public JSONObject getDataTypeMask() {
//            // TODO Auto-generated method stub
//            return null;
//        }
//    };
//    IGestureListener gestureListener = new IGestureListener() {
//
//        @Override
//        public void onGesture(GestureEvent event) {
//            // TODO Auto-generated method stub
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
//
//        }
//
//        @Override
//        public JSONObject getGestureConfig() {
//            // claim the gesture you need to be true
////			JSONObject masks = new JSONObject();
////			JSONObject config = new JSONObject();
////			try {
////				for (int i = 1; i < GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i++) {
////					masks.put(""+i, true);
////				}
////				config.put("masks", masks);
////			} catch (JSONException e) {
////				Log.e("MainActivity", e.toString());
////			}
////			return config;
//
//            // claim the gesture you need to be true
//
//            JSONObject config = new JSONObject();
//            JSONObject masks = new JSONObject();
//
//            try {
//                masks.put("" + GestureEvent.Gestures.SWIPE_LEFT_L.ordinal(),
//                        true);
//                masks.put("" + GestureEvent.Gestures.SWIPE_RIGHT_L.ordinal(),
//                        true);
//                masks.put("" + GestureEvent.Gestures.PULL_PUSH_PULL.ordinal(),
//                        true);
//                masks.put("" + GestureEvent.Gestures.PUSH_PULL_PUSH.ordinal(),
//                        true);
//
//                config.put("masks", masks);
//            } catch (JSONException e) {
//                Log.e(TAG, e.toString());
//            }
//
//            return config;
//
//        }
//
//        @Override
//        public void onContinuousGestureStart(ContinuousGestureEvent event) {
//            // TODO Auto-generated method stub
//            Log.e("onContinuousGestureStart", event.toString());
//            //DrawString(df.format(event.freq) + " Hz");
//        }
//
//        @Override
//        public void onContinuousGestureUpdate(ContinuousGestureEvent event) {
//            // TODO Auto-generated method stub
//            Log.e("onContinuousGestureUpdate", event.toString());
//            //DrawString(df.format(event.freq) + " Hz");
//        }
//
//        @Override
//        public void onContinuousGestureEnd() {
//            // TODO Auto-generated method stub
//            Log.e("onContinuousGestureEnd", "onContinuousGestureEnd");
//            //DrawString("wave to start");
//
//        }
//    };
//    public String choice_m;
//
//    private static boolean need_a_gesture;
//    private int id = 0;
//    protected boolean needCircle;
//    protected boolean needLine;
//
//    //绘图相关
//    public MainActivity() {
//        super();
//
//        Log.e("build", "DEVICE:" + Build.DEVICE + " DISPLAY:" + Build.DISPLAY + " FINGERPRINT:" + Build.FINGERPRINT + " MODEL:" + Build.MODEL + " ");
//
//        // 设置画笔属性
//        mPaint = new Paint();
//        mPaint.setColor(Color.BLUE);
//        mPaint.setStrokeWidth(2);
//        mPaint.setAntiAlias(true);
//
//        tPaint = new Paint();
//        tPaint.setColor(Color.MAGENTA);
//        tPaint.setStrokeWidth(1);
//        tPaint.setAntiAlias(true);
//
//        xPaint = new Paint();
//        xPaint.setTextSize(40);
//        xPaint.setColor(Color.RED);
//        xPaint.setStrokeWidth(1);
//        xPaint.setAntiAlias(true);
//
//        dashPaint = new Paint();//设置画笔
//        dashPaint.setStyle(Paint.Style.STROKE);//设置画笔为空心
//        dashPaint.setColor(Color.GRAY);//设置画笔的颜色
//        Path path = new Path();//用于在屏幕上划线
//        path.moveTo(0, 10);
//        path.lineTo(480, 10);//在按钮和下面到图表之间划线
//        PathEffect effects = new DashPathEffect(new float[]{5, 5, 5, 5}, 1);//先绘制长度为5的实线,再绘制长度为5的空白,重复下去
//        dashPaint.setPathEffect(effects);//设置虚线的样式
//    }
//
//    @Override
//    public void onCreate(Bundle savedInstanceState) {
//        Log.w("Main", "onCreate");
//
//        requestWindowFeature(Window.FEATURE_NO_TITLE);
//        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
//                WindowManager.LayoutParams.FLAG_FULLSCREEN);
//        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
//
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.main);
//
//        try {
//            fos = openFileOutput("raw_data", Context.MODE_PRIVATE);//?这里的文件是用来保存数据的
//            oos = new ObjectOutputStream(fos);
//
//            fos2 = openFileOutput("all_raw_data", Context.MODE_PRIVATE);
//            oos2 = new ObjectOutputStream(fos2);
//        } catch (FileNotFoundException e) {
//            Log.e("file", e.toString());
//            e.printStackTrace();
//        } catch (IOException e) {
//            // TODO Auto-generated catch block
//            e.printStackTrace();
//        }
//
//        initControl();//初始化view中控件
//
////		try {
////			Installer.installModel(getAssets(), Installer.installRoot());
////		} catch (IOException e) {
////			// TODO Auto-generated catch block
////			e.printStackTrace();
////		}
//
////        try {
////            dolphin = Dolphin.getInstance(
////                    (AudioManager) getSystemService(Context.AUDIO_SERVICE),
////                    getContentResolver(),
////                    this,
////                    dataReceiver, gestureListener);
////        } catch (DolphinException e) {
////            // TODO Auto-generated catch block
////            Log.w("Main", "DolphinException");
////            e.printStackTrace();
////        } catch (JSONException e) {
////            // TODO Auto-generated catch block
////            Log.w("Main", "JSONException");
////            e.printStackTrace();
////        }
//        // dolphin.restrictChannel();
//        Intent bindIntent = new Intent(this, CollectorService.class);
//        bindService(bindIntent, connection, BIND_AUTO_CREATE);
////        calldolphin();
//    }
//    private ServiceConnection connection = new ServiceConnection() {
//
//        @Override
//        public void onServiceDisconnected(ComponentName name) {
//
//        }
//
//        @Override
//        public void onServiceConnected(ComponentName name, IBinder service) {
//
//        }
//    };
//    protected void onStart() {
//        Log.w("Main", "onStart");
////        try {
////            dolphin.prepare(getApplicationContext());//主任务开始
////        } catch (DolphinException e) {
////            // TODO Auto-generated catch block
////            e.printStackTrace();
////        }
//        super.onStart();
//    }
//
//    @Override
//    protected void onResume() {
//        Log.w("Main", "onResume");
//        super.onResume();
//    }
//
//    @Override
//    protected void onPause() {
//        Log.w("Main", "onPause");
//        super.onPause();
//
//    }
//
//    @Override
//    protected void onStop() {
//        Log.w("Main", "onStop");
//
////        try {
////            dolphin.pause();
////        } catch (DolphinException e) {
////            // TODO Auto-generated catch block
////            e.printStackTrace();
////        }
//        super.onStop();
//    }
//
//    @Override
//    protected void onDestroy() {
//        Log.w("Main", "onDestroy");
//
////        try {
////            dolphin.stop();
////        } catch (DolphinException e) {
////            // TODO Auto-generated catch block
////            e.printStackTrace();
////        }
//        super.onDestroy();
//        android.os.Process.killProcess(android.os.Process.myPid());
//    }
//
//    // 初始化控件信息
//    private void initControl() {
//
//        Button needButton = (Button) findViewById(R.id.need);
//        needButton.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                need_a_gesture = true;
//                stop = true;
//                Toast.makeText(getApplicationContext(), "need a gesture",
//                        Toast.LENGTH_SHORT).show();
//            }
//        });
//
//        Button phoneButton = (Button) findViewById(R.id.phone);
//        phoneButton.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                //dolphin.switchToEarphoneSpeaker();
//                needLine = needLine == true ? false : true;
//            }
//        });
//
//        Button mediaButton = (Button) findViewById(R.id.media);
//        mediaButton.setOnClickListener(new View.OnClickListener() {
//
//            @Override
//            public void onClick(View v) {
////				dolphin.switchToLoudspeaker();
//                needCircle = needCircle == true ? false : true;
//            }
//        });
//
//        Button delete = (Button) findViewById(R.id.delete);
//        delete.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                File f = new File("/sdcard/123");
//                f.mkdir();
//                Log.i("file", "come in file");
//                f = new File("/sdcard/123", "sample.sonic");
//                f.delete();
//            }
//        });
//
//        // //按键
//        // btnStart = (Button)this.findViewById(R.id.btnStart);
//        // btnExit = (Button)this.findViewById(R.id.btnExit);
//        // //按键事件处理
//        // btnStart.setOnClickListener(new ClickEvent());
//        // btnExit.setOnClickListener(new ClickEvent());
//        // 画笔和画板x
//        sfv = (SurfaceView) this.findViewById(R.id.SurfaceView01);
//        spinner = (Spinner) this.findViewById(R.id.spinner);
//        adapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item,choice);
//        //设置下拉列表风格
//        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
//        //将适配器添加到spinner中去
//        spinner.setAdapter(adapter);
//        spinner.setVisibility(View.VISIBLE);//设置默认显示
//        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
//            @Override
//            public void onItemSelected(AdapterView<?> arg0, View arg1,
//                                       int arg2, long arg3) {
//                // TODO Auto-generated method stub
//                choice_m = (String) ((TextView)arg1).getText();
//
//
//            }
//
//            @Override
//            public void onNothingSelected(AdapterView<?> arg0) {
//                // TODO Auto-generated method stub
//
//            }
//        });
//
//    }
//
//    public void calldolphin()
//    {
//        try {
//            dolphin = Dolphin.getInstance(
//                    (AudioManager) getSystemService(Context.AUDIO_SERVICE),
//                    getContentResolver(),
//                    this,
//                    dataReceiver, gestureListener);
//        } catch (DolphinException e) {
//            // TODO Auto-generated catch block
//            Log.w("exception","DolphinException");
//            e.printStackTrace();
//        } catch (JSONException e) {
//            // TODO Auto-generated catch block
//            Log.w("exception","JSONException");
//
//            e.printStackTrace();
//        }
//        try {
//            dolphin.prepare(getApplicationContext());//主任务开始
//        } catch (DolphinException e) {
//            // TODO Auto-generated catch block
//            e.printStackTrace();
//        }
//    }
//
//    DecimalFormat df = new DecimalFormat("0.00");
//    private int gesture_counter;
//    private int all_gesture_counter;
//
//    private void DrawString(String s) {
//
//        Canvas canvas = sfv.getHolder().lockCanvas(
//                new Rect(0, 0, 1024, sfv.getHeight()));
//        if (canvas == null) {
//            Log.e("canvas", "lock fail");
//            return;
//        }
//
//        canvas.drawColor(Color.WHITE);
//        canvas.drawText(s, 150, 250, xPaint);
//
//        canvas.save();
//        sfv.getHolder().unlockCanvasAndPost(canvas);
//    }
//
//    private void SimpleDrawLines(double[] info, double[] feature, int upper,
//                                 int lower, double max_velocity, int[] toparr, double[] boundarr,
//                                 int[] upperarr, int[] lowerarr) {
//
//        // y = (float) (baseLine - info[i] / rate * 100);
//        // x = (i) + shift;//(i-start)-800 ;//x = (i-len/4)/16 + shift ;
//        // canvas.drawLine(x, baseLine, x, y, mPaint);
////        Log.i("SONIC", "the length of info is " + info.length);//201
////        Log.i("SONIC", "the length of feature is " + feature.length);//20
////        Log.i("SONIC", "the sample of info is " + info[0]);
////        Log.i("SONIC", "the sample of feature is " + feature[0]);
////        Log.i("SONIC","hello world");
//
//        Canvas canvas = sfv.getHolder().lockCanvas(
//                new Rect(0, 0, 1024, sfv.getHeight()));
//        if (canvas == null)
//            return;
//
//        int middle = 400;
//
//        canvas.drawColor(Color.WHITE);
//        // for (int i = 0; i < info_normal.length; i++) {
//        // canvas.drawLine(i+50, baseLine, i+50, baseLine - (float)
//        // info_normal[i]*1000, xPaint);
//        // }
//        for (int i = 0; i < info.length; i++) {
//            canvas.drawLine(2 * i + 150, middle, 2 * i + 150, middle
//                    - (float) info[i] * 200, tPaint);
//        }
//        canvas.drawLine(2 * 100 + 150, middle, 2 * 100 + 150, middle
//                - (float) 1.5 * 200, xPaint);
//        canvas.drawLine(2 * upper + 150, middle, 2 * upper + 150, middle
//                - (float) 1 * 200, mPaint);
//        canvas.drawLine(2 * lower + 150, middle, 2 * lower + 150, middle
//                - (float) 0.8 * 200, mPaint);
//
//        middle = 250;
//        if (null != feature) {
//            for (int i = 0; i < feature.length; i++) {
//                canvas.drawLine(2 * i + 150, middle, 2 * i + 150, middle
//                        - (float) feature[i] * 2000, tPaint);
//            }
//        }
//
//        // for (int i = 0; i < topList.size() && i < 64; i++) {
//        // canvas.drawCircle(2*i+600, middle - ((float)
//        // topList.get(topList.size()-1-i) - 100)*2, 2, mPaint);
//        // }
//
//        middle = 100;
//        if (null != toparr) {
//            for (int i = 0; i < toparr.length; i++) {
//                canvas.drawLine(2 * i + 150, middle, 2 * i + 150, middle
//                        - (float) (toparr[i] - 100), xPaint);
//            }
//        }
//        middle = 100;
//        if (null != boundarr && null != lowerarr && null != upperarr) {
//            for (int i = 0; i < toparr.length; i++) {
//                canvas.drawLine(2 * i + 350, middle, 2 * i + 350, middle
//                        - (float) (boundarr[i] - 100), xPaint);
//            }
//            for (int i = 0; i < lowerarr.length; i++) {
//                canvas.drawCircle(2 * i + 350, middle
//                        - (float) (lowerarr[i] - 100), 1, mPaint);
//            }
//            for (int i = 0; i < upperarr.length; i++) {
//                canvas.drawCircle(2 * i + 350, middle
//                        - (float) (upperarr[i] - 100), 1, mPaint);
//            }
//        }
//
//        canvas.drawText("" + max_velocity, 400, 200, tPaint);
//        canvas.save();
//
//        sfv.getHolder().unlockCanvasAndPost(canvas);
//    }
//
//    private void saveGesture(GestureData.RichFeatureData portableData) {//存放声波信息和对应手势到文件
//        Log.i("saveGesture","save!");
//        need_a_gesture = false;
//        try {
//            portableData.id = id;
//            portableData.feature_id = GestureEvent.Gestures.PULL_PUSH.ordinal();
//            id++;
//            oos.writeObject(portableData);
//            gesture_counter++;
//            Log.e("gesture", "capped");
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private void saveAllGesture(GestureEvent event) {
//
//        try {
//            GestureEvent e = (GestureEvent) event.clone();
//            e.rich_feature_data = null;
//
//            oos2.writeObject(e);
//            all_gesture_counter++;
//
//            Log.e("gesture", "logged");
//        } catch (IOException e) {
//            e.printStackTrace();
//        } catch (CloneNotSupportedException e) {
//            // TODO Auto-generated catch block
//            e.printStackTrace();
//        }
//    }
//
//    private void sendGestureToUI(String rsString) {
//        Message msg = mFlipHandler.obtainMessage();
//        msg.obj = rsString;
//        if (rsString.contains("left")) {
//            msg.arg1 = -1;
//        }
//        if (rsString.contains("right")) {
//            msg.arg1 = 1;
//        }
//        msg.what = 0;
//        msg.sendToTarget();
//    }
//
//    private void SimpleDrawCircle(double radius) {
//        Canvas canvas = sfv.getHolder().lockCanvas(
//                new Rect(0, 0, 1024, sfv.getHeight()));
//        if (canvas == null)
//            return;
//        canvas.drawColor(Color.WHITE);
//        canvas.drawCircle(400, 250, (float) (((radius + 1) * 80) + 10), tPaint);
//        canvas.save();
//        sfv.getHolder().unlockCanvasAndPost(canvas);
//    }
//
//    /**
//     * 按键事件处理
//     */
//    // class ClickEvent implements View.OnClickListener{
//    // @Override
//    // public void onClick(View v){
//    // Button button = (Button)v;
//    // if(button == btnStart){
//    // if(button.getText().toString().equals("Start")){
//    // //dolphin.start();
//    // }else if (button.getText().equals("Stop")) {
//    // //end();
//    // }
//    // }
//    // else {
//    // new AlertDialog.Builder(AudioMaker.this)
//    // .setTitle("提示")
//    // .setMessage("确定退出?")
//    // .setPositiveButton("确定", new DialogInterface.OnClickListener() {
//    // public void onClick(DialogInterface dialog, int whichButton) {
//    // setResult(RESULT_OK);//确定按钮事件
//    // AudioMaker.this.finish();
//    // finish();
//    // }
//    // })
//    // .setNegativeButton("取消", new DialogInterface.OnClickListener() {
//    // public void onClick(DialogInterface dialog, int whichButton) {
//    //
//    // }
//    // })
//    // .show();
//    // }
//    // }
//    // }
//
//    public Handler mFlipHandler = new Handler() {
//        int id = 5;
//
//        @Override
//        public void handleMessage(Message msg) {
//            if (msg.what == 0) {
//                int i = msg.arg1;
//                Toast.makeText(getApplicationContext(), (String) msg.obj,
//                        Toast.LENGTH_SHORT).show();
//                if (i > 0) {
//                    Log.e("flip", "to right" + id);
//                    id -= 1;
//                    id = id == 1 ? 2 : id;
//                    mPager.setCurrentItem(id, true);
//                } else if (i < 0) {// left
//                    id += 1;
//                    id = id == 10 ? 9 : id;
//                    Log.e("flip", "to left" + id);
//                    mPager.setCurrentItem(id, true);
//                }
//            }
//            super.handleMessage(msg);
//        }
//    };
//
//    @Override
//    public void onCoreReady() {
//        Log.e("dolphin", "start");
//        try {
//            dolphin.start();
//        } catch (DolphinException e) {
//            // TODO Auto-generated catch block
//            e.printStackTrace();
//        }
//    }
//
//    @Override
//    public void onNoisy() {
//        Log.e("dolphin", "too nosiy");
//    }
//
//    @Override
//    public void onCoreFail() {
//        handler.post(new Runnable() {//android中不允许Activity中启动的除主线程外的线程访问UI界面,用post(runnable)对象来更新主线程UI
//
//            @Override
//            public void run() {
//                Toast.makeText(getApplicationContext(), "音量太小", Toast.LENGTH_SHORT).show();
////				MainActivity.this.finish();
//            }
//        });
//    }
//
//    @Override
//    public void onNormal() {
//        Log.i("dolphin", "normal working");
//    }
//    public String getChoice()
//    {
//        return choice_m;
//    }
//
//    @Override
//    public void writesucc() {
//        Vibrator vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
//        vibrator.vibrate(100);
//    }
//
//
//}