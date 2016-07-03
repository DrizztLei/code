package sdu.embedded.Sonic.client;

import org.json.JSONException;
import org.json.JSONObject;

public interface ICoreManager {

    void setDataReceiver(IDataReceiver receiver);

    void setGestureListener(IGestureListener listener);

    void setGestureConfig(JSONObject config) throws JSONException;

    boolean isWorking();

    void setSingleMode(boolean isSingle);

    boolean isSingle();

    void start();

    void peek();

    void prepare();

    //	void resume();
    void pause();

    void stop();

}
