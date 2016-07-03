package sdu.embedded.Sonic.echo;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

/**
 * Created by yqf on 6/30/14.
 */
public class UltrasonicEmitter {
    private static final int sampleRate = 44100;
    boolean isEchoing = false;
    UltrasonicData data = null;//样本数量int型和一个byte数组
    private AudioTrack audioTrack;//用来播放正弦波
    private double wavelen;//波长

    private static int division(int x, int y) {
        if (x < y) {//x<y,则交换x和y
            int t = x;
            x = y;
            y = t;
        }
        while (y != 0) {
            if (x == y)
                return 1;
            else {
                int k = x % y;
                x = y;
                y = k;
            }
        }
        return x;
    }

    UltrasonicEmitter(double wavelen) {
        this.wavelen = wavelen;
        data = genTone();
    }

    UltrasonicData genTone() {
        double max = 32768;
        double temp = 0;
        int tmp = 0;
        double a1;
        double a2;

        int numSamples = ((300 * (int) (1000 * wavelen)) / division(300, (int) (1000 * wavelen)));
        while (numSamples < 4800)
            numSamples *= 2;

        Log.e("genTone", "numSamples:" + numSamples);

        double sample[] = new double[numSamples];
        byte generatedSnd[] = new byte[2 * numSamples];
        try {
            for (int i = 0; i < numSamples; ++i) {
                temp = i / wavelen;
                tmp = (int) temp;
                a1 = temp - tmp;
                a2 = (i % wavelen) / wavelen;
                sample[i] = Math.sin(2 * Math.PI * a1);//Math.sin(2 * Math.PI * i / (sampleRate/freqOfTone));
            }//这里多wavelen即sampleRate/频率
            int idx = 0;
            for (final double dVal : sample) {
                // scale to maximum amplitude
                final short val = (short) ((dVal * max));
                // in 16 bit wav PCM, first byte is the low order byte
                generatedSnd[idx++] += (byte) (val & 0x00ff);//http://stackoverflow.com/questions/2413426/playing-an-arbitrary-tone-with-android
                generatedSnd[idx++] += (byte) ((val & 0xff00) >>> 8);
            }
        } catch (Exception e) {
            Log.e("e", e.toString());
        }
        return new UltrasonicData(numSamples, generatedSnd);
    }

    /**
     * AudioTrack 只能播放PCM数据流
     *
     * @return
     */

    boolean play() {
        if (isEchoing) return false;
        if (data == null) return false;
        audioTrack = new AudioTrack(
                AudioManager.STREAM_RING,//AudioManger.STREAM_RING代表播放的是铃声
                sampleRate,//采样率,一秒中有多少个样本点
                AudioFormat.CHANNEL_OUT_DEFAULT,//声道通道
                AudioFormat.ENCODING_PCM_16BIT,//编码格式,每个采样点的长度
                data.numSamples,
                AudioTrack.MODE_STREAM);

        try {
            audioTrack.play();
        } catch (Exception e) {
            Log.e("play", e.toString());
            return false;
        }

        isEchoing = true;
        new Thread() {
            @Override
            public void run() {
                while (isEchoing)
                    audioTrack.write(data.gen, 0, data.gen.length);//
            }
        }.start();

        return true;
    }

    boolean stop() {
        if (!isEchoing) return false;
        isEchoing = false;
        audioTrack.stop();
        audioTrack.release();
        return true;
    }

}
