package sdu.embedded.Sonic.core;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.hillsidewatchers.sdu.sonicoperator.Analyzer.Main;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import edu.emory.mathcs.jtransforms.dct.DoubleDCT_1D;
import sdu.embedded.Sonic.client.ContinuousGestureEvent;
import sdu.embedded.Sonic.client.GestureData;
import sdu.embedded.Sonic.client.GestureData.RichFeatureData;
import sdu.embedded.Sonic.client.GestureData.SimplePatten;
import sdu.embedded.Sonic.client.GestureEvent;
import sdu.embedded.Sonic.client.ICoreStateCallback;
import sdu.embedded.Sonic.client.RealTimeData;
import sdu.embedded.Sonic.echo.UltrasonicManager;

public class AudioProcessThread extends Thread {

    static final String TAG = "AudioProcessThread";
    Intent intent = null;
	/*

	 * 静态常量区
	 */
    static final double sonicVelocity = 340;
    static final int gesturePrefix = 3;
    static final int gestureSuffix = 6;
    static final int range = 201;
    static final int halfrange = range / 2;

    public final static int TYPE = 6;

    static boolean needGesture = false, needRealtimeData = false;

    static final short[][] further_patten = {
            {0, 1, -1, 0, 0, 0},
            {0, -1, 1, 0, 0, 0},
            {0, 1, -1, 1, -1, 0}
    };
    static final short[][] simple_patten = {
            {0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, -1, 0, 0, 0, 0},
            {0, 1, -1, 1, 0, 0},
            {0, -1, 1, -1, 0, 0},
            {0, -1, 1, -1, 1, 0},
    };

    private static final long FREQ_THRESHOLD = 2 * 1000;

    /*
     * 工具区
     */
    static LinearTest linearTest = new LinearTest();
    static FFT fft = new FFT();
    static Tweaker tweaker = new Tweaker(CoreSettings.data_width, CoreSettings.data_time);

    /*
     * 共享全局变量区
     */
    public List<short[]> shortResultList = null;// FFT 处理后的数据
    public boolean[] maskFlags = null;

    /*
     * 私有全局变量，loop间存储用
     */
    private boolean isProcessing = false;
    private boolean isPeeking = true;
    private int peekedCounter = 0;
    private boolean isPreparing = true;
    private boolean isNoisy = false;
    private int noiseCounter = 0;

    private ICoreStateCallback callback = null;
    private List<RealTimeData> realTimeDataList = null;
    private List<GestureEvent> gestureEventList = null;

    RRList<Integer> topList = new RRList<Integer>(100);
    RRList<Double> boundList = new RRList<Double>(100);
    RRList<Integer> upperboundList = new RRList<Integer>(100);
    RRList<Integer> lowerboundList = new RRList<Integer>(100);
    RRList<Double> top_valueList = new RRList<Double>(100);
    RRList<Integer> stateList = new RRList<Integer>(3);
    RRList<Double> intensityList = new RRList<Double>(100);
    RRList<Double> freqList = new RRList<Double>(3);
    RRList<double[]> featureInfoList = new RRList<double[]>(100);
    RRList<double[]> rawInfoList = new RRList<double[]>(50);

    private boolean isInAGesture = false;
    private boolean isANewGestureTested = false;
    private boolean isANewGestureConcluded = false;
    private boolean isContinueGesture = false;
	
	/*
	 * 结果输出区
	 */

    private double radius = 0;
    private double intensity = 0;
    int[] toparr = new int[100];
    double[] boundarr = new double[100];

    // 每次loop的暂时使用区域，减少多次初始化
    private int[] info_int = new int[range];

    private double[] info = new double[range];

//	private double[] normal_info = new double[range];

    private double[] raw_normal_info = new double[range];

    private double[] raw_normal_info_noisy = new double[range];

    private String resultString = "";

    private String lastResultString = "";

    private int raw_top;

    private int top;

    private double sum;

    private double rawSum;

    private int state;

    private double[] feature_info;

    private double speed;

    private boolean isFast;

    private int choice;

    private boolean prepared = false;

    private int prepareCounter;

    private double noisy_sum;

    private double core_sum;

    private int upperbound;

    private int lowerbound;

    private double velocity;

    private double topvelocity;

    private double bound;

    private double freq;

    private long singleLoopStartTime;

    private double lastFreq;

    private boolean freqPos;

    private boolean lastFreqPos;

    private long lastFreqPosChange;

    private int freqChangeCounter;

    private int[] upperIntegers = new int[100];

    private int[] lowerIntegers = new int[100];

    private String errString;

    private RichFeatureData saveData;

    private long duration;

    private int sonicChannel;

    private int sonicPeak;

    private double boundThreshold = 0;

    private String result = "";



    private List<Double> samples = new ArrayList<Double>();

    private List<Double> finalsam = new ArrayList<>();

    private Context context = null;
    public AudioProcessThread(
            ICoreStateCallback callback,
            List<short[]> shortResultList,
            List<RealTimeData> realTimeDataList,
            List<GestureEvent> gestureEventList,
            String result,Context context) {

        this.callback = callback;//回调类是dolphin
        this.shortResultList = shortResultList;//存放fft处理后对数据
        this.realTimeDataList = realTimeDataList;
        this.gestureEventList = gestureEventList;
        this.result = result;
        this.context = context;
        boundThreshold = UltrasonicManager.isTablet && FFT.intel ? 0.015 : 0;
        intent = new Intent();
        intent.setAction("com.hillsidewatchers.sdu.sonicoperator.collectorServerReceiver");

        Log.i(TAG, "boundThreshold : " + boundThreshold);
    }

    public void stopGracefully() {
        Log.i(TAG, "stopGracefully");

        isProcessing = false;
        synchronized (shortResultList) {
            shortResultList.clear();
            shortResultList.notifyAll();
        }

        // clear the noise vector
        for (int i = 0; i < CoreSettings.raw_normal_info_mean.length; i++) {
            CoreSettings.raw_normal_info_mean[i] = 0;
        }

        Log.i(TAG, "stopped Gracefully");

    }

    public void run() {
        Log.i(TAG, "run");

        isProcessing = true;
        List<short[]> buf = null;
        short[] tmpBuf;
        int[] fftBuf;
        RealTimeData data = null;
        GestureEvent event = null;

        while (isProcessing) {
            synchronized (shortResultList) {
                if (shortResultList.size() == 0) {
                    try {
                        shortResultList.wait();
                    } catch (InterruptedException e) {
                        Log.e(TAG, e.toString());
                        e.printStackTrace();
                    }
                }
                buf = (List<short[]>) ((LinkedList<short[]>) shortResultList).clone();
                shortResultList.clear();
            }

            for (int i = 0; i < buf.size() && i < 5; i++) {
                tmpBuf = buf.get(i);
//                Log.i("Sonic","tmpbuf is "+tmpBuf[0]);
                fftBuf = fft.transform(tmpBuf, tmpBuf.length);

                if (fftBuf.length != 2049) {
                    Log.e(TAG, "FFT Buf length!=2049");
                    continue;
                }
//                Log.i("Sonic","fftBuf is "+fftBuf[fftBuf.length-1]);

                if (isPeeking) {
                    peek(fftBuf);
                    continue;
                }

                SimpleAnaylse(fftBuf);//对数据进行分析,同时决定是否要进行手势分析

                if (isPreparing) continue;

                if (isTooNoisy()) {
                    Log.e(TAG, "noisy, waiting");
                    if (!isNoisy) {
                        isNoisy = true;
                        new Thread() {
                            public void run() {
                                callback.onNoisy();
                            }
                        }.start();
                    }
                    continue;
                } else {
                    if (isNoisy) {
                        isNoisy = false;
                        new Thread() {
                            public void run() {
                                callback.onNormal();
                            }
                        }.start();
                    }
                }
                if (needRealtimeData) {
                    data = getRealtimeData();
                    synchronized (realTimeDataList) {
                        realTimeDataList.add(data);
                        realTimeDataList.notifyAll();
                    }
                }
                if (needGesture && hasNewGesture()) {
                    event = getGestureEvent();
                    synchronized (gestureEventList) {
                        gestureEventList.add(event);
                        gestureEventList.notifyAll();
                    }
                }
            }
        }
        Log.i(TAG, "run end");
    }

    private boolean hasNewGesture() {
        return isANewGestureConcluded || isANewGestureTested;
    }

	/* 
	*  寻找可以发声音的频率
	*/

    private void peek(int[] buffer) {
        Log.i(TAG, "peek,peekedCounter:" + peekedCounter);
        if (peekedCounter < 10) {
            peekedCounter++;
            return;
        } else if (peekedCounter > 10) {
            return;
        }

        peekedCounter++;

        for (sonicChannel = 2; sonicChannel > 0; sonicChannel--) {
            sonicPeak = UltrasonicManager.freqbinTable[sonicChannel];
            Log.i(TAG, "peek sonicPeak:" + sonicPeak);

            int j;
            for (j = sonicPeak - 5; j < sonicPeak + 6; j++) {
                if (buffer[j] > 1000) break;
            }
            Log.i(TAG, "peek buffer[" + j + "]:" + buffer[j]);

            if (buffer[j] <= 1000) break;
        }

        if (!callback.onSelectSonic(sonicChannel))
            sonicChannel = 2;
    }

    /*
    *  输入为FFT的结果，大约2000多个值
    */
    private void SimpleAnaylse(int[] buffer) {
		
		/* 
		*  TODO 初始化要用的数据
		*  防止直接返回后残余的值会造成累计
		*/
        int len = buffer.length;
        errString = null;
		/* 
		*  提取全频谱的最大值在哪，即寻找超声波尖峰
		*/
        int target = UltrasonicManager.freqbinTable[sonicChannel];
        sonicPeak = target;
        for (int i = target - 5; i < target + 6; i++) {
            if (buffer[sonicPeak] < buffer[i])
                sonicPeak = i;
        }
//		
//		Log.e(TAG, "sonicPeak:"+sonicPeak);
		
		/* 
		*  TODO 多个超声波尖峰的查找
		*/
		
		/* 
		*  TODO 若找不到指定强度的尖峰说明没有发声
		*/
        if (buffer[sonicPeak] < 1000) {
            //Log.e(TAG, "buffer["+sonicPeak+"] "+ buffer[sonicPeak] +" is not big enough");
//            Log.i("SONIC","sonicPeak is "+buffer[sonicPeak]+"!!!");
            noiseCounter++;
            if (noiseCounter > 200) {//若有200次没有检测到尖峰,说明环境有问题
                noiseCounter = 0;
                new Thread() {
                    public void run() {
                        Log.i("SONIC","not found sonicPeak");
                        callback.onCoreFail();
                    }
                }.start();
            }
            return;
        } else {
            noiseCounter = 0;
        }
		
		/* 
		*  TODO 和发声的比对校验
		*/
		
		/* 
		*  将尖峰周围的200个数据拷贝出来
		*  尖峰被削减为0
		*  TODO 将除去尖峰之外的发音的其他发出的干扰声线一并去除
		*/
        int start = sonicPeak - 100;
        int end = sonicPeak + 100;

        if (start + 200 > buffer.length) {
            Log.e(TAG, "can't find the peak");
            return;
        }
        System.arraycopy(buffer, start, info_int, 0, halfrange);//参数依次 源数组 源数组的开始索引 目的数组 目的数组的开始索引
        //要拷贝数据的长度
        System.arraycopy(buffer, sonicPeak + 1, info_int, halfrange + 1, halfrange);

        rawSum = 0;

        core_sum = 0;
        noisy_sum = 0;

        int low = raw_normal_info.length / 2 - 20;
        int high = raw_normal_info.length / 2 + 20;
        //现在info_int中存放的是尖峰周围的200个频率数据,但不包括尖峰
        //noisy_sum存放的是尖峰周围200个频率数据的和,关于判断周围噪音的见isTooNoisy方法
        //raw_sum存放的也是尖峰周围200个频率数据的和
        for (int i = 0; i < info_int.length; i++) {
            noisy_sum += info_int[i];
            if (i > low && i < high) core_sum += info_int[i];

            rawSum += info_int[i];
            info[i] = info_int[i];
            info[i] /= 30000;
//			normal_info[i] = info_int[i];
//			normal_info[i] /= buffer[max];
        }

        core_sum += buffer[sonicPeak];
        noisy_sum += buffer[sonicPeak];
		
		/* 
		* 用于判断是否处于噪音大的环境
		*/
        if (isTooNoisy()) {
            return;
        }
        //raw_normal_info中存放的尖峰周围包括尖峰200个频率数据在总和中的占比
        for (int i = 0; i < info_int.length; i++) {
            raw_normal_info_noisy[i] = info_int[i] / rawSum;
            if (!isPreparing) {
                raw_normal_info_noisy[i] -= CoreSettings.raw_normal_info_mean[i];
            }
            raw_normal_info[i] = raw_normal_info_noisy[i];
            //if(raw_normal_info[i] < 0) raw_normal_info[i] = -raw_normal_info[i];
            if (raw_normal_info[i] < 0.01) raw_normal_info[i] = 0;
        }
		
		/* 
		*  TODO 判断是否prepare结束
		*/


        if (isPreparing) {
            if (prepared(buffer[sonicPeak])) {
                new Thread() {
                    public void run() {
                        callback.onCoreReady();
                    }

                    ;
                }.start();
            }
            return;
        }

		/* 
		* 判断偏移主峰值在哪里,即寻找除了尖峰外的峰值第二高的频率
		*/
        top = 0;
        raw_top = 0;
        for (int i = 0; i < info.length; i++) {
            if (info[top] < info[i]) top = i;
        }
        // raw_top = top;
		
		
		/* 
		* 通过偏移简单地判断是接近还是远离
		*/
        state = RealTimeData.State.STILL.ordinal();
        if (raw_normal_info[top] < 0.1) {//(info[top] < 0.005) {
            top = 100;
        } else if (top < 99 && top > 60) {
            state = RealTimeData.State.PULL.ordinal();
        } else if (top > 101 && top < 140) {
            state = RealTimeData.State.PUSH.ordinal();
        } else if (top == 101) {
            top = 100;
            state = RealTimeData.State.PUSH.ordinal();
        } else if (top == 99) {
            top = 100;
            state = RealTimeData.State.PULL.ordinal();
        } else {
            top = 100;
        }
		
		/* 
		* 保存最近的100个top和对于的值
		*/

        topList.add(top);
        top_valueList.add(myRound(info[top], 3));
		

		/* 
		* 对200值的info做DCT提取特征
		* 将前20位特征值拷贝到feature_info中
		*/
        double[] save = new double[61];
        System.arraycopy(raw_normal_info, 70, save, 0, save.length);
        rawInfoList.add(save);

        double[] dctBuf = new double[raw_normal_info.length];
        System.arraycopy(raw_normal_info, 0, dctBuf, 0, raw_normal_info.length);
        DoubleDCT_1D dct_1d = new DoubleDCT_1D(dctBuf.length);
        dct_1d.forward(dctBuf, true);
        feature_info = new double[20];
        System.arraycopy(dctBuf, 0, feature_info, 0, 20);
        featureInfoList.add(feature_info);
		
		/* 
		* 通过最近的3个状态判断，如果三个状态
		* TODO 没看懂
		* 不满3个不是still的最终输出还是still，
		* 原先的值被保留
		*/
        stateList.add(state);
        if (state != RealTimeData.State.STILL.ordinal() && stateList.size() == 3) {
            //boolean ok = !stateList.get(1).equals("still") || !stateList.get(2).equals("still");
            boolean still = stateList.get(1).equals("still") && stateList.get(2).equals("still");
            if (still && !(state == stateList.get(1) && state == stateList.get(2))) {
                state = RealTimeData.State.STILL.ordinal();
            }
        }

		/* 
		* 判断上下界
		*/

        upperbound = top + 1;
        lowerbound = top - 1;

        int counter1 = 0;

        int counter0 = 0;
        while (upperbound < 150) {
            upperbound++;
            if (upperbound == 100) upperbound++;
            if (raw_normal_info[upperbound] <= boundThreshold) counter0++;
            else counter0 = 0;
            if (counter0 > 3) { // 3
                upperbound -= counter0;
                break;
            }
        }
        counter0 = 0;
        while (lowerbound > 50) {
            lowerbound--;
            if (lowerbound == 100) lowerbound--;
            if (raw_normal_info[lowerbound] <= boundThreshold) counter0++;
            else counter0 = 0;
            if (counter0 > 3) { // 3
                lowerbound += counter0;
                break;
            }
        }

        double bound_sum = 0;
        double bound_mean = 0;

        if (upperbound != lowerbound) {

            for (int i = lowerbound; i <= upperbound; i++) {
                bound_sum += raw_normal_info[i];
            }
            bound = 0;
            for (int i = lowerbound; i <= upperbound; i++) {
                bound += i * raw_normal_info[i] / bound_sum;
            }

            bound_mean = bound_sum / (upperbound - lowerbound);
        }

        if (upperbound - lowerbound < 5)
            bound = 100d;

        raw_top = (int) Math.floor(bound + 0.5d);

        if (bound_mean > 0.01)
            boundList.add(bound < 101 && bound > 99 ? 100d : bound);
        else {
            boundList.add(100d);
            raw_top = 100;
            // upperbound = lowerbound = 100;
        }

        upperboundList.add(upperbound);
        lowerboundList.add(lowerbound);
		
		/* 
		* 将上下界外的噪音除去
		*/
        for (int i = 0; i < lowerbound; i++) {
            raw_normal_info[i] = 0;
        }
        for (int i = upperbound; i < raw_normal_info.length; i++) {
            raw_normal_info[i] = 0;
        }
		
		/* 
		* 计算intensity
		*/

        intensity = 0;
        for (int i = lowerbound; i <= upperbound; i++) {
            intensity += info[i] * Math.abs(i - 100);
        }
        if (upperbound - lowerbound < 5)
            intensity = 0;

        this.intensity = intensity;
        intensityList.add(intensity);
		
		/* 
		* 计算sum
		*/
        sum = 0;

        if (top > 40 && top < 160) {
            for (int i = top - 16; i < top + 17; i++) {
                sum += raw_normal_info[i];
            }
        }
		
		/* 
		* 计算速度,用多普勒效应的公式,http://wenda.haosou.com/q/1384991054066977
		* topvelocity是曾出现的最大速度
		*/

        velocity = 0d;
        int shift = Math.abs(upperbound - 100) > Math.abs(lowerbound - 100) ?
                Math.abs(upperbound - 100) : Math.abs(lowerbound - 100);
        velocity = sonicVelocity * (shift) / (2 * sonicPeak + shift);
        topvelocity = topvelocity > velocity ? topvelocity : velocity;
		
		/* 
		* 计算物体大小
		*/

        int size_sum = 0;
        for (int i = lowerbound; i <= upperbound; i++) {
            size_sum += info_int[i];
        }
        double mean = 0;
        if (lowerbound != upperbound)
            mean = size_sum / (upperbound - lowerbound);
		
		
		/* 
		* 需要最近至少已经有40个top值供后续分析
		*/
        if (topList.size() <= 40) return;
		
		/* 
		* 判断最近是否有连续的6个停顿
		* 来激发手势的识别
		*/
        for (int i = 0; i < 100; i++) {
            toparr[i] = topList.get(i);
        }
        for (int i = 0; i < 100; i++) {
            boundarr[i] = boundList.get(i);
            lowerIntegers[i] = lowerboundList.get(i);
            upperIntegers[i] = upperboundList.get(i);
        }
		
		/* 
		* 判断是否需要继续做手势的识别
		*/
        if (gestureEventList == null) return;
        if(isInAGesture)
           addSam(samples,save);

        if (!isInAGesture) {
            if (testAGestureBegin()) {
                Log.i("gesture", "found a new begin");
                singleLoopStartTime = System.currentTimeMillis();
                isInAGesture = true;

                upperboundList.mark(gesturePrefix + 1);
                lowerboundList.mark(gesturePrefix + 1);

                intensityList.mark(gesturePrefix + 1);

                topList.mark(gesturePrefix + 1);
                top_valueList.mark(gesturePrefix + 1);

                boundList.mark(gesturePrefix + 1);// 向前mark4位
                rawInfoList.mark(gesturePrefix + 1);

                isANewGestureTested = classifyGesture(false);
                isANewGestureConcluded = false;
                samples.clear();
                addSam(samples,save);

            } else {
                // loop again
                isANewGestureConcluded = isANewGestureTested = false;
            }
        } else {
            if (testAGestureEnd()) {
                Log.i("gesture", "found a new end, total time = " + (System.currentTimeMillis() - singleLoopStartTime));
//                File f = new File("/sdcard/123");
//                try {
//                    f.mkdir();
//                    Log.i("file", "come in file");
//                    f = new File("/sdcard/123","sample.sonic");
//                    if(!f.exists())
//                        f.createNewFile();
//                    Log.i("file","come in -----");
//                    FileWriter fw = new FileWriter(f,true);
//                    for(int index = 0;index < raw_normal_info_noisy.length;index++)
//                    {
//                        BigDecimal bg=new BigDecimal(raw_normal_info_noisy[index]);
//
//                        fw.write(bg.setScale(14, BigDecimal.ROUND_HALF_UP)+" ");
//                    }
//                    String choice = callback.getChoice();
//                    int choice_i = 0;
//                    switch (choice)
//                    {
//                        case "pull":
//                          choice_i = 0;
//                            break;
//                        case "push":
//                            choice_i = 1;
//                            break;
//                        case "left":
//                            choice_i  =2;
//                            break;
//                        case "right":
//                            choice_i = 3;
//                            break;
//                        case "up":
//                            choice_i = 4;
//                            break;
//                        case "down":
//                            choice_i = 5;
//                            break;
//                    }
//
//                    fw.write(choice_i+" ");
//                    fw.flush();
//                    fw.close();
//                    callback.writesucc();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
              //  raw_normal_info_noisy
                Log.e(TAG,"==============调用");
                int left = samples.size() - 256;

                for (int i = 0; i < samples.size(); i++) {
                    if (samples.get(i) == 0) {
                        samples.remove(i);
                        i--;
                        left--;
                        if (left == 0)
                            break;
                    }
                }
                if(samples.size() < 256)
                {
                    Log.w("the size is ", samples.size() + " ");
                    Log.w("the left is ", left + "");
                }
                finalsam = samples.subList(0, 256);
                if (finalsam.size() != 256) {
                    Log.w("the size is ", samples.size() + " ");
                    Log.w("the left is ", left + "");
                }
                double[] finalsmaples = new double[finalsam.size()];
                for(int index = 0;index < finalsam.size();index++){
                    finalsmaples[index] = finalsam.get(index);
                }

//                DNN dnn = DNN.getInstead();
//
//                int result = dnn.calculator(finalsmaples);
//                Main svm = Main.calculator(finalsam.size());
                int result = -1;
                try {
                     result = Main.calculator(finalsmaples);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                if(result == -1){
                    Log.e("AudioProcessThread","函数错误");
                }
                //int result = svm.calculator(finalsmaples);

                Log.e(TAG,"计算出的手势的值为"+result);
                this.result = String.valueOf(result);
                intent.putExtra("result",result);
                if (intent==null){
                    Log.e(TAG,"intent==null");
                }
                if (context==null){
                    Log.e(TAG,"context==null");
                }
                context.sendBroadcast(intent);

                //pull push left right up down
                isANewGestureTested = false;
                isANewGestureConcluded = true;

                concludeGesture();

                isInAGesture = false;
            } else {
                isANewGestureConcluded = false;
                isANewGestureTested = classifyGesture(false);
            }
        }
    }
    public void addSam(List<Double> samples,double []save)
    {
        for(int index = 0;index < save.length;index++)
        {
            samples.add(save[index]);
        }
    }

    private void concludeGesture() {
        // TODO Auto-generated method stub
        classifyGesture(true);
//		topList.reset(100);
//		boundList.reset(100d);
//		upperboundList.reset(100);
//		lowerboundList.reset(100);
    }

    private boolean classifyGesture(boolean isConclude) {
		
		/* 
		 * 判断是否是连续的手势
		*/
        duration = System.currentTimeMillis() - singleLoopStartTime;
        if (duration > FREQ_THRESHOLD) {
            lastFreq = freq;
            freq = calculateFreq();
            lastResultString = resultString;
            isContinueGesture = true;
            resultString = "Continuous";
            if (freqChangeCounter < 2) return false;
            return !(freq == lastFreq);
        }
        isContinueGesture = false;
		
		/* 
		* 手势识别开始
		* 提取手势数据
		*/

        Double[] simple_data = null;
        if (isConclude)
            simple_data = new Double[boundList.cut_size(gestureSuffix)];
        else
            simple_data = new Double[boundList.cut_size(0)];


        GestureData.RichFeatureData portableData = new GestureData.RichFeatureData();
        getRichFeatureData(simple_data, portableData);

        lastResultString = resultString;
		
		/* 
		* 判断是否是crossover
		*/
        if (isConclude) {
            int CR_count = CoreSettings.gesture_group[CoreSettings.CR];
            if (CR_count > 0 && isCrossover()) {
                choice = GestureEvent.Gestures.CROSSOVER.ordinal();
                resultString = GestureEvent.gesture[choice];

                // user only choose to recognize one gesture in CR group
                // fast find it
                if (CR_count == 1) {
                    for (int i = GestureEvent.Gestures.CROSSOVER.ordinal(); i <= GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i++) {
                        if (CoreSettings.mask_flags[i]) {
                            choice = i;
                            resultString = GestureEvent.gesture[i];
                        }
                        return !lastResultString.equals(resultString);
                    }
                }

                prepareTimedData(portableData);
                if (portableData.data != null) {
                    int rsint = (int) linearTest.test_cr(portableData.data);
                    choice = rsint;
                    resultString = GestureEvent.gesture[choice];
                }

                return !lastResultString.equals(resultString);
            }
        }
		
		/* 
		* 使用人工判断比对
		* 和神经网络相结合的方式
		* 对收视进行判断
		*/

        twoWayGestureTest(simple_data, portableData);

        return !lastResultString.equals(resultString);
    }

    private void getRichFeatureData(Double[] simple_data, RichFeatureData portableData) {
        portableData.data = new double[640];

        StringBuilder sBuilder = new StringBuilder();
//		StringBuilder sBuilder1 = new StringBuilder();
        int counter = 0;
        boundList.cut(simple_data);

        for (int i = 0; i < simple_data.length; i++, counter++) {
//            Log.i("simpledata","---"+simple_data[i]+"");
            sBuilder.append((simple_data[i]) + ", ");
        }
        portableData.feature_str = sBuilder.toString();

        double[] tmparr;
        counter = 0;
        for (int i = 4; i < 36; i++) {
            tmparr = featureInfoList.get(i);
            for (int j = 0; j < tmparr.length; j++, counter++) {
                portableData.data[counter] = tmparr[j];
//				tmparr[j] = 0;
            }
        }
    }

    private boolean isCrossover() {
        if (upperboundList.cut_size(gestureSuffix) > 15) return false;

        Integer[] upp = new Integer[upperboundList.cut_size(gestureSuffix)];
        Integer[] low = new Integer[lowerboundList.cut_size(gestureSuffix)];
        upperboundList.cut(upp);
        lowerboundList.cut(low);

        int[] kupp = new int[upp.length];
        int[] klow = new int[low.length];


        int counter = 0, counterneg = 0;

        for (int i = 1; i < low.length; i++) {
            if (upp[i] > 105 && low[i] < 95) {
                counter += 1;
//				Log.e("crossover", "counter:\t"+upp[i]+"\t"+low[i]);
            }
            if ((upp[i] < 103 && upp[i] > 97) || (low[i] > 97 && low[i] < 103)) {
                counterneg += 1;
//				Log.e("crossover", "counter neg:\t"+upp[i]+"\t"+low[i]);
            }
            kupp[i] = upp[i] - upp[i - 1];
            klow[i] = low[i] - low[i - 1];
//			if(kupp[i] < 0)kupp[i] = -1;
//			if(kupp[i] > 0)kupp[i] = 1;
//			if(klow[i] < 0)klow[i] = -1;
//			if(klow[i] > 0)klow[i] = 1;
        }

//		for (int i = 0; i < upp.length; i++) {
//			string1 += upp[i]+",";
//			string2 += low[i]+",";
//		}
//		
//		Log.e("crossover", "string1:\t"+string1);
//		Log.e("crossover", "string2:\t"+string2);

        int pupp = 0, plow = 0;
        for (int i = 0; i < upp.length; i++) {
            if (upp[pupp] < upp[i]) pupp = i;
        }
        for (int i = 0; i < upp.length; i++) {
            if (low[plow] > low[i]) plow = i;
        }
        double rupp = pupp / (double) upp.length;
        double rlow = plow / (double) low.length;


        Log.i(TAG, "crossover " + counter / (double) klow.length);
        Log.i(TAG, "crossover neg " + counterneg / (double) klow.length);

        boolean rs = counter / (double) klow.length > 0.2 && counterneg / (double) klow.length < 0.4;
        Log.i(TAG, "crossover" + rs);
        return rs;
    }

    private double calculateFreq() {
//		 TODO Auto-generated method stub

        lastFreqPos = freqPos;

        if (raw_top == 100) return freq;
        freqPos = (raw_top - 100 > 0);

        if (freqPos == lastFreqPos)
            return freq;

//		StringBuilder stringBuilder = new StringBuilder();
//		for (int i = Math.min(topList.size(), 50); i >= 0; i--) {
//			stringBuilder.append(topList.get(i)+",");
//		}
//		Log.e("topList", ""+raw_top);

        freqChangeCounter++;
        double ret = 1000d / (2 * (System.currentTimeMillis() - lastFreqPosChange));
        lastFreqPosChange = System.currentTimeMillis();
        double freqMean = 0;

        if (freqChangeCounter >= 2) {

            if (freqList.size() == 3) {
//				Log.e("freq", freqList.toString());
                if (ret - (freqList.get(0) + freqList.get(1) + freqList.get(2)) / 3 > 6) {
                    Log.e("freq", "not stable: " + ret + " | " + freqList.toString());

                } else {
                    freqList.add(ret);
                }
            } else {
                freqList.add(ret);
            }

            for (int i = 0; i < freqList.size(); i++) {
                freqMean += freqList.get(i) / freqList.size();
            }
        }

        return freqMean;
    }

    private boolean testAGestureEnd() {
        StringBuilder stringBuilder0 = new StringBuilder();
        boolean has6Pause = false;
        if (!isContinueGesture) {
            has6Pause = (boundList.get(gestureSuffix) > 102 || boundList.get(gestureSuffix) < 98);
            for (int i = 0; i < gestureSuffix; i++) {
                has6Pause = has6Pause && (boundList.get(i) < 102 && boundList.get(i) > 98);
            }

            for (int i = 0; i < 30; i++) {
                stringBuilder0.append(topList.get(i) + ",");
            }
        } else {
            has6Pause = (boundList.get(20) > 102 || boundList.get(20) < 98);
            for (int i = 0; i < 20; i++) {
                has6Pause = has6Pause && (boundList.get(i) < 102 && boundList.get(i) > 98);
            }
        }

        return has6Pause;
    }

    private boolean testAGestureBegin() {

        boolean start = false;

        if (FFT.intel) {
            start = (boundList.get(gesturePrefix) < 102 && boundList.get(gesturePrefix) > 98);
            for (int i = 0; i < gesturePrefix; i++) {
                start = start && (boundList.get(i) > 101 || boundList.get(i) < 99);
            }
        } else {
            start = (boundList.get(gesturePrefix) < 102 && boundList.get(gesturePrefix) > 98);
            for (int i = 0; i < gesturePrefix; i++) {
                start = start && (boundList.get(i) > 102 || boundList.get(i) < 98);
            }
        }
        return start;
    }

    private boolean prepared(int bufferMaxValue) {

        if (prepared) return false;

        prepareCounter++;
        prepared = prepareCounter == 20;

        CoreSettings.topValue += bufferMaxValue / 20;

        for (int i = 0; i < raw_normal_info.length; i++) {
            CoreSettings.raw_normal_info_mean[i] += raw_normal_info[i] / 21;
        }

        if (prepared) {
            for (int i = 1; i < 3; i++) {
                CoreSettings.raw_normal_info_mean[100 + i] *= (10 - 2 * i) / 10f;
                CoreSettings.raw_normal_info_mean[100 - i] *= (10 - 2 * i) / 10f;
            }
        }

        return prepared;
    }

    private boolean isTooNoisy() {
        //Log.e(TAG, ""+core_sum/noisy_sum);
        return core_sum / noisy_sum < 0.2;//如果尖峰周围40个频率数据与尖峰周围200个频率数据的比小于0.2,则判断处在噪音环境中,否则尖峰周围40个数据的频率和
    }//在200个频率数据和中的占比应大于平均值

    private RealTimeData getRealtimeData() {
        if (FFT.intel) {
            if (raw_top != 100 && raw_top > 85 && raw_top < 115) {
                radius -= (raw_top - 100 > 0 ? 1 : -1) * Math.pow(raw_top - 100, 2) * (sum) / (20);
                radius = radius < -1 ? -1 : radius;
                radius = radius > 1 ? 1 : radius;
            }
        } else {
            if (raw_top != 100 && raw_top > 85 && raw_top < 115) {
                radius -= (raw_top - 100 > 0 ? 1 : -1) * Math.pow(raw_top - 100, 2) * (sum) / (50);
                radius = radius < -1 ? -1 : radius;
                radius = radius > 1 ? 1 : radius;
            }
        }

        return new RealTimeData(radius, state, intensity, top,
                upperbound, lowerbound, velocity, topvelocity,
                raw_normal_info, feature_info, toparr, boundarr, upperIntegers, lowerIntegers);
    }

    private GestureEvent getGestureEvent() {
//		Log.i(TAG, "getGestureEvent");
        if (isContinueGesture) {
            if (isANewGestureConcluded) freqList.reset(0d);
            return new ContinuousGestureEvent(freq, isANewGestureConcluded);
        }
        double[] intensitys = getIntensity();
        return new GestureEvent(isANewGestureConcluded, choice, duration, speed, intensitys[0], intensitys[1], isFast, resultString, errString, saveData);
    }

    private void prepareTimedData(GestureData.RichFeatureData portableData) {
        double[][] data = new double[rawInfoList.cut_size(gestureSuffix)][];

        data = rawInfoList.cut(data);

        portableData.data = tweaker.tweak(data);
        portableData.raw = data;

        saveData = portableData;
    }

    // TODO test
    private int groupMatch(int choice, int main, int start, int end, GestureData.RichFeatureData portableData) {
        int rsint = 0;
        switch (CoreSettings.gesture_group[choice]) {
            case 0:
                Log.i(TAG, "user choose no gesture in this group");
                return 0;
            case 1:
                Log.i(TAG, "user choose 1 gesture in this group, fast find it");
                if (CoreSettings.mask_flags[main]) {
                    return main;
                } else {
                    for (int i = start; i <= end; i++) {
                        if (CoreSettings.mask_flags[i]) {
                            return i;
                        }
                    }
                }
                break;
            default:
                Log.i(TAG, "user choose multi gesture in this group");
                prepareTimedData(portableData);
                if (portableData.data != null) {
                    Log.i(TAG, "linear test multi gesture");
                    if (choice == CoreSettings.NF) {
                        rsint = (int) linearTest.test_nf(portableData.data);
                    } else if (choice == CoreSettings.FN) {
                        rsint = (int) linearTest.test_fn(portableData.data);
                    } else if (choice == CoreSettings.NFNF) {
                        rsint = (int) linearTest.test_nfnf(portableData.data);
                    }
                }
                return rsint;
        }
        return rsint;
    }

    private void twoWayGestureTest(Double[] simple_data,
                                   GestureData.RichFeatureData portableData) {

        SimplePatten patten = simpleGestureFilt(simple_data);

        resultString = simplePattenMatch(patten);

        saveData = null;

        if (resultString.equals("further")) {
            Log.i(TAG, "gestureTest further matching");

            if (choice == GestureEvent.Gestures.PUSH_PULL.ordinal()) {
                choice = groupMatch(
                        CoreSettings.NF, choice,
                        GestureEvent.Gestures.SWIPE_LEFT_L.ordinal(),
                        GestureEvent.Gestures.SWIPE_RIGHT_P.ordinal(),
                        portableData);
                resultString = GestureEvent.gesture[choice];
            } else if (choice == GestureEvent.Gestures.PULL_PUSH.ordinal()) {
                choice = groupMatch(
                        CoreSettings.FN, choice,
                        GestureEvent.Gestures.SWING_LEFT_L.ordinal(),
                        GestureEvent.Gestures.SWING_RIGHT_P.ordinal(),
                        portableData);
                resultString = GestureEvent.gesture[choice];
            } else if (choice == GestureEvent.Gestures.PUSH_PULL_PUSH_PULL.ordinal()) {
                choice = groupMatch(
                        CoreSettings.NFNF, choice,
                        GestureEvent.Gestures.SWIPE_BACK_LEFT_L.ordinal(),
                        GestureEvent.Gestures.SWIPE_BACK_RIGHT_P.ordinal(),
                        portableData);
                resultString = GestureEvent.gesture[choice];
            }
            Log.i(TAG, "linearTest rs: " + resultString);
            // portableData.data = null;
            portableData.raw = null;
        }

        if (resultString.startsWith("err|")) {
            Log.e(TAG, "gesture err: " + resultString);
            resultString = lastResultString;
        }
    }

    private double[] getIntensity() {
        double[] rs = new double[2];

        if (intensityList.cut_size(gestureSuffix) > 2) {
            Double[] intensitys = new Double[intensityList.cut_size(gestureSuffix)];
            intensitys = intensityList.cut(intensitys);
            for (int i = 0; i < intensitys.length; i++) {
                if (intensitys[i] > rs[0])
                    rs[0] = intensitys[i];
                rs[1] += intensitys[i];
            }
            rs[1] /= intensitys.length;
        }

        return rs;
    }

    private String simplePattenMatch(SimplePatten patten) {
        int choice = -1;

        if (patten.time < 3) return "err|too fast";
        if (patten.speed < 2) return "err|too slow";

        for (int i = 0; i < further_patten.length; i++) {
            boolean ok = true;
            for (int j = 0; j < further_patten[i].length; j++) {
                ok = ok & (further_patten[i][j] == patten.data[j]);
            }
            if (ok && isANewGestureConcluded) return "further";
            if (ok && !isANewGestureConcluded) choice = GestureEvent.Gestures.PUSH_PULL.ordinal() + i;
        }

        for (int i = 0; i < simple_patten.length; i++) {
            boolean ok = true;
            for (int j = 0; j < simple_patten[i].length; j++) {
                ok = ok & (simple_patten[i][j] == patten.data[j]);
            }
            if (ok) {
                choice = i;
                break;
            }
        }

        if (choice == -1) return "err|not match";
        Log.i(TAG, "choice: " + choice);

        this.choice = choice = choice < 0 ? 0 : choice;
        return GestureEvent.gesture[choice];
    }

    private SimplePatten simpleGestureFilt(Double[] simple_data) {

        SimplePatten patten = new SimplePatten();

        int[] data = new int[simple_data.length];
        int[] data_compress = new int[simple_data.length];
        int[] data_tmp = new int[simple_data.length];
        int[] feature = new int[6];

        int counter_pos = 0, counter_neg = 0;
        double pos_sum = 0, neg_sum = 0, totol_sum = 0;
        ;
        double max = 100;
        double min = 100;
        for (int i = 0; i < data.length; i++) {
            if (simple_data[i] == 100) {
                continue;
            } else if (simple_data[i] > 100) {
                pos_sum += Math.pow((simple_data[i] - 100), 4);
                data[i] = 1;
                counter_pos++;
            } else {
                neg_sum += Math.pow((simple_data[i] - 100), 4);
                data[i] = -1;
                counter_neg++;
            }
            max = (simple_data[i] > max ? simple_data[i] : max);
            min = (simple_data[i] < min ? simple_data[i] : min);
        }

//		String string = "";
//		for (int i = 0; i < data.length; i++) {
//			string += data[i]+",";
//		}
//		Log.e("simple_data", string);

        String winnerString = Math.abs(max - 100) > Math.abs(min - 100) ? "pos" : "neg";
        winnerString = Math.abs(max - 100) == Math.abs(min - 100) ? "both" : winnerString;

        double speed = Math.abs(max - 100) > Math.abs(min - 100) ? Math.abs(max - 100) : Math.abs(min - 100);

        double counter_total = counter_neg + counter_pos;
        totol_sum = pos_sum + neg_sum;
        double pos_ratio = pos_sum / totol_sum;

//		Log.e("pos_ratio", pos_ratio+"");
//		Log.e("counter_total", counter_total+"");

        int ptr = 0;

        for (int i = 0; i < data.length; i++) {
            if (data[i] != 0)
                data_compress[ptr++] = data[i];
        }

        for (int i = 2; i < data.length; i++) {
            if (data_compress[i] == data_compress[i - 1]) {
                data_tmp[i] = data_compress[i];
                data_tmp[i - 1] = data_compress[i];
            }
        }
        data = data_tmp;


        int cut_counter = 0;
        boolean once = false, once2 = true;

        for (int i = 1, j = 0; i < data.length && j < 5; i++) {
            if (data[i] == 0) {
                cut_counter++;
//				if(cut_counter > 4 && once){
//					once = false;
//					j++;
//					feature[j] = 0;
//				}
                continue;
            }

            if (feature[j] == data[i]) {
                continue;
            }

            j++;
            feature[j] = data[i];
//			if(once2){
//				once = true;
//				once2 = false;
//			}
            cut_counter = 0;
        }

//		string = "";
//		
//		for (int i = 0; i < feature.length; i++) {
//			string += feature[i]+",";
//		}
//		Log.e("feature", string);

        patten.data = feature;
        patten.time = (int) counter_total;
        patten.speed = speed;

        if (speed > 8) patten.isFast = true;
        else patten.isFast = false;

        this.speed = patten.speed;
        this.isFast = patten.isFast;

        Log.i(TAG, "SimplePatten" + patten.toString());

        return patten;
    }

    private static double myRound(double d, int n) {
        // 分别以A:d = 0.514d, n = 1和B:d = 0.514d, n = 2为例进行分析
        d = d * Math.pow(10, n);
        // A: 0.514 * 10 -> 5.14
        // B: 0.514 * 100 -> 51.4
        d += 0.5d;
        // A: 5.14 + 0.5 -> 5.64
        // B: 51.4 + 0.5 -> 51.9
        d = (long) d;
        // A: (long)5.64 -> 5
        // B: (long)51.9 -> 51
        d = d / Math.pow(10d, n);
        // A: 5 / 10d -> 0.5
        // B: 51 / 100d -> 0.51
        return d;
    }

    public void turnToRealWork() {
        isPreparing = false;
    }

    public void turnToPrepare() {
        isPeeking = false;
    }
}