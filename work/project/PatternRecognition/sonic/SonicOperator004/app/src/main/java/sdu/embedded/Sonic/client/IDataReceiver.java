package sdu.embedded.Sonic.client;

import org.json.JSONObject;

public interface IDataReceiver {
    void onData(RealTimeData data);

    JSONObject getDataTypeMask();
}
