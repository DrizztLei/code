package sdu.embedded.Sonic.core;

import java.util.List;

import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class AudioFetchThread extends Thread {

    static final String TAG = "AudioFetchThread";

    AudioRecord audioRecord;// 录音
    boolean isRecording = false;
    static boolean isPreparing = true;
    List<short[]> shortResultList = null;// fft 处理前的数据

    public AudioFetchThread(List<short[]> shortResultList) {
        this.shortResultList = shortResultList;

        audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC,
                CoreSettings.frequency, CoreSettings.channelConfiguration,
                CoreSettings.audioEncodeing, CoreSettings.minBufferSize);

        // if(AcousticEchoCanceler.isAvailable())
        // AcousticEchoCanceler.create(audioRecord.getAudioSessionId());

        // NoiseSuppressor.create(audioRecord.getAudioSessionId());
        // if(AutomaticGainControl.isAvailable()){
        // AutomaticGainControl.create(audioRecord.getAudioSessionId());
        // Log.e("gain", "gain");
        // }
        // AutomaticGainControl.
    }

    public void stopGracefully() {
        isRecording = false;
        shortResultList.clear();
        Log.i(TAG, "stopped Gracefully");
    }

    public void run() {
        Log.i(TAG, "run");

        isRecording = true;
        short[] buffer = new short[2048];
        try {
            audioRecord.startRecording();

            Log.i(TAG, "sample rate: " + audioRecord.getSampleRate());
            Log.i(TAG, "min BufferSize: " + CoreSettings.minBufferSize);

            for (int i = 0; isRecording; i = (i + 1) % 8) {// TODO bug fix
                audioRecord.read(buffer, 512 * i, 512);

                if (i != 7) continue;

//				if(true){
//					StringBuilder stringBuilder = new StringBuilder();
//					Log.e(TAG, "start");
//
//					for (int j = 0; j < buffer.length && j < 100; j++) {
//						stringBuilder.append(buffer[j]+",");
//					}
//					Log.e(TAG, stringBuilder.toString());
//					Log.e(TAG, "end");
//				}

                synchronized (shortResultList) {
                    shortResultList.add(buffer);
                    shortResultList.notifyAll();//同一个shortResultList对象既在AudioFetchThread线程中,也在AudioProessThread中,这里面得到后,唤醒
                    //在另一个线程中,进一步处理
                }
            }
            audioRecord.stop();
//			audioRecord.release();
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
        Log.i(TAG, "run end");
    }

    public void turnToRealWork() {
        isPreparing = false;
    }
}
