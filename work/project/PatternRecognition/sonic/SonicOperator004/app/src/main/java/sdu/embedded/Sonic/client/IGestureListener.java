package sdu.embedded.Sonic.client;

import org.json.JSONObject;

public interface IGestureListener {
    void onGesture(GestureEvent event);

    void onContinuousGestureStart(ContinuousGestureEvent event);

    void onContinuousGestureUpdate(ContinuousGestureEvent event);

    void onContinuousGestureEnd();

    JSONObject getGestureConfig();
}
