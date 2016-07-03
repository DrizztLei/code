package sdu.embedded.Sonic.client;

import android.content.Context;

public interface IEchoManager {
    boolean emit(int freqIndex);

    boolean kill(int freqIndex);

    boolean autoSwitchSpeaker(Context ctx);

    boolean switchToEarphoneSpeaker();

    boolean switchToLoudspeaker();
}
