package sdu.embedded.Sonic.echo;

import sdu.embedded.Sonic.client.IEchoManager;
import sdu.embedded.Sonic.client.IEchoStateCallback;
import android.content.Context;
import android.content.res.Configuration;
import android.media.AudioManager;
import android.util.Log;

/**
 * Created by yqf on 6/30/14.
 */
public class UltrasonicManager implements IEchoManager {
    static final String TAG = "UltrasonicManager";

    private static AudioManager audioManager = null;
    public static boolean isTablet = false;//判断是否在平板上

    public final static double[] wavelenTable = new double[]{
            //2.45,
            //2.388,
            2.306, // [1632]
            2.198, // [1712]
            //2.138,
            2.1 // [1792]
    };

    public final static int[] freqbinTable = new int[]{
            1632,
            1712,
            1792
    };

    static UltrasonicEmitter emitters[] = new UltrasonicEmitter[wavelenTable.length];

    public static IEchoManager getEchoManager(AudioManager audioManager,
                                              IEchoStateCallback callback) {
        UltrasonicManager.audioManager = audioManager;
        return new UltrasonicManager();
    }

    public static boolean isTablet(Context context) {
        isTablet = (context.getResources().getConfiguration().screenLayout
                & Configuration.SCREENLAYOUT_SIZE_MASK)
                >= Configuration.SCREENLAYOUT_SIZE_LARGE;

        return isTablet;
    }

    public boolean switchToEarphoneSpeaker() {        //听筒
        if (audioManager == null)
            return false;
        audioManager.setSpeakerphoneOn(false);//设置喇叭关闭
        audioManager.setMode(AudioManager.MODE_IN_CALL);// 设置为接电话模式

        // audioManager.setParameters("noise_suppression=off");
        // audioManager.playSoundEffect();
        // TODO
//		audioManager.setStreamVolume(AudioManager.STREAM_VOICE_CALL, audioManager.getStreamMaxVolume(AudioManager.STREAM_VOICE_CALL), AudioManager.FLAG_PLAY_SOUND);
//		audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC), AudioManager.FLAG_PLAY_SOUND);

        Log.i(TAG, "switchToEarphoneSpeaker");

        return true;
    }

    public boolean switchToLoudspeaker() {//切换到扬声器工作
        if (audioManager == null)
            return false;
        audioManager.setSpeakerphoneOn(true);
        audioManager.setMode(AudioManager.MODE_RINGTONE);//设置为铃响模式

        // audioManager.setParameters("noise_suppression=off");
//		audioManager.setStreamVolume(AudioManager.STREAM_VOICE_CALL, audioManager.getStreamMaxVolume(AudioManager.STREAM_VOICE_CALL), AudioManager.FLAG_PLAY_SOUND);
//		audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC)/3, AudioManager.FLAG_PLAY_SOUND);

        Log.i(TAG, "switchToLoudspeaker");
        return true;
    }

    private UltrasonicManager() {
    }

    public boolean emit(int freqIndex) {
        if (freqIndex < 0 || freqIndex >= wavelenTable.length) return false;
        emitters[freqIndex] = emitters[freqIndex] == null
                ? new UltrasonicEmitter(wavelenTable[freqIndex])
                : emitters[freqIndex];

        return emitters[freqIndex].play();
    }


    public void test() {
        new Thread() {
            @Override
            public void run() {
                UltrasonicEmitter emitter = null;
                for (int i = 2100; i < 2300; i++) {
//                    double aa = testTable[i];
                    double aa = i;
                    aa /= 1000;
                    Log.e("emitter", "" + aa);
                    emitter = new UltrasonicEmitter(aa);
                    emitter.play();
                    try {
                        sleep(5000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    emitter.stop();
                    try {
                        sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();

    }

    public boolean kill(int freqIndex) {
        if (freqIndex < 0 || freqIndex >= wavelenTable.length) return false;
        if (emitters[freqIndex] == null) return false;
        if (!emitters[freqIndex].isEchoing) return false;
        return emitters[freqIndex].stop();
    }

    @Override
    public boolean autoSwitchSpeaker(Context ctx) {
        if (isTablet(ctx))
            return switchToLoudspeaker();
        else
            return switchToEarphoneSpeaker();
    }

}
