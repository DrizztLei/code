package sdu.embedded.Sonic.core;

import sdu.embedded.Sonic.client.GestureEvent;

import android.media.AudioFormat;
import android.media.AudioRecord;

public class CoreSettings {
    public static final int frequency = 48000;//分辨率
    public static final int channelConfiguration = AudioFormat.CHANNEL_IN_MONO;
    public static final int audioEncodeing = AudioFormat.ENCODING_PCM_16BIT;

    static final int yMax = 2;//Y轴缩小比例最大值
    static final int yMin = 2;//Y轴缩小比例最小值  
    static int minBufferSize = AudioRecord.getMinBufferSize(frequency,
            channelConfiguration,
            audioEncodeing);
    static int topValue = 0;
    static double[] raw_normal_info_mean = new double[201];
    static boolean[] mask_flags = new boolean[GestureEvent.gesture.length];

    public static final int NF = 0;
    public static final int FN = 1;
    public static final int NFNF = 2;
    public static final int CR = 3;

    public static final int data_width = 30;
    public static final int data_time = 30;

    static int[] gesture_group = new int[4];

    static int[][] outputTable = new int[4][5];

}
