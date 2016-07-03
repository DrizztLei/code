package sdu.embedded.Sonic.core;

/**
 * Created by yqf on 4/17/14.
 */
public class FFT {

    public static boolean intel;
    static final String TAG = "PluginInstaller";

    static {
        if (android.os.Build.CPU_ABI.startsWith("x86")) {
            intel = true;
            System.loadLibrary("dolphin_x86");
        } else {
            intel = false;
            System.loadLibrary("dolphin");
        }
    }

    public int[] transform(short[] buffer, int size) {
        //return intel ? fft_x86(buffer, size) : fft(buffer, size);
         return fft(buffer, size);
    }

    public native int[] fft(short[] buffer, int size);
//    public native int[] fft_x86(short[] buffer, int size);
}
