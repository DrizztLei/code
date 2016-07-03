package sdu.embedded.Sonic.client;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class DolphinCoreVariables {
    public static final String DOLPHIN_HOME = "/storage/sdcard0/dolphin_home/";
    public static final String BROADCAST_SERVER_NAME = "seu.lab.dolphin.server.BROADCAST";
    public static final String BROADCAST_CLIENT_NAME = "seu.lab.dolphin.server.BROADCAST_CLIENT";
    public static final String MODEL_PROVIDE_NAME = "seu.lab.dolphin.server.MODEL_PROVIDER";
    public static final String REMOTE_SERVICE_NAME = "seu.lab.dolphin.server.REMOTE";

    public static JSONObject DEFAULT_MODEL_CONFIG = new JSONObject();

    static {
        JSONObject masks = new JSONObject();
        for (int i = 1; i <= GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal(); i++) {
            try {
                masks.put("" + i, true);
            } catch (JSONException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        JSONArray models = new JSONArray();
        models.put("nf_default.dolphin").put("fn_default.dolphin").put("nfnf_default.dolphin").put("cr_default.dolphin");
        JSONArray outputs = new JSONArray();
        outputs.put(new JSONArray()
                .put(GestureEvent.Gestures.PUSH_PULL.ordinal())
                .put(GestureEvent.Gestures.SWIPE_LEFT_L.ordinal())
                .put(GestureEvent.Gestures.SWIPE_RIGHT_L.ordinal())
                .put(GestureEvent.Gestures.SWIPE_LEFT_P.ordinal())
                .put(GestureEvent.Gestures.SWIPE_RIGHT_P.ordinal()));
        outputs.put(new JSONArray()
                .put(GestureEvent.Gestures.PULL_PUSH.ordinal())
                .put(GestureEvent.Gestures.SWING_LEFT_L.ordinal())
                .put(GestureEvent.Gestures.SWING_RIGHT_L.ordinal())
                .put(GestureEvent.Gestures.SWING_LEFT_P.ordinal())
                .put(GestureEvent.Gestures.SWING_RIGHT_P.ordinal()));
        outputs.put(new JSONArray()
                .put(GestureEvent.Gestures.PUSH_PULL_PUSH_PULL.ordinal())
                .put(GestureEvent.Gestures.SWIPE_BACK_LEFT_L.ordinal())
                .put(GestureEvent.Gestures.SWIPE_BACK_RIGHT_L.ordinal())
                .put(GestureEvent.Gestures.SWIPE_BACK_LEFT_P.ordinal())
                .put(GestureEvent.Gestures.SWIPE_BACK_RIGHT_P.ordinal()));
        outputs.put(new JSONArray()
                .put(GestureEvent.Gestures.CROSSOVER_CLOCKWISE.ordinal())
                .put(GestureEvent.Gestures.CROSSOVER_ANTICLOCK.ordinal()));

        try {
            DEFAULT_MODEL_CONFIG.put("masks", masks);
            DEFAULT_MODEL_CONFIG.put("models", models);
            DEFAULT_MODEL_CONFIG.put("outputs", outputs);
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }
}
