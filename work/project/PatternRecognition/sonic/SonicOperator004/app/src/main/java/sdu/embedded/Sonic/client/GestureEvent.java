package sdu.embedded.Sonic.client;

import java.io.Serializable;

import sdu.embedded.Sonic.client.GestureData.RichFeatureData;

public class GestureEvent implements Serializable, Cloneable {
    /**
     *
     */
    private static final long serialVersionUID = 2L;

    public static enum Gestures {


        STILL,
        PUSH,
        PULL,
        PUSH_PULL_PUSH,
        PULL_PUSH_PULL,
        PULL_PUSH_PULL_PUSH,
        PUSH_PULL,
        PULL_PUSH,
        PUSH_PULL_PUSH_PULL,
        SWIPE_LEFT_L,
        SWIPE_RIGHT_L,
        SWIPE_LEFT_P,
        SWIPE_RIGHT_P,
        SWING_LEFT_L,
        SWING_RIGHT_L,
        SWING_LEFT_P,
        SWING_RIGHT_P,
        SWIPE_BACK_LEFT_L,
        SWIPE_BACK_RIGHT_L,
        SWIPE_BACK_LEFT_P,
        SWIPE_BACK_RIGHT_P,
        CROSSOVER,
        CROSSOVER_CLOCKWISE,
        CROSSOVER_ANTICLOCK
    }

    public static final String[] gesture = {
            "still",
            "push",
            "pull",
            "push pull push",
            "pull push pull",
            "pull push pull push",

            "push pull",
            "pull push",
            "push pull push pull",

            "swipe to left landscape",
            "swipe to right landscape",
            "swipe to left portrait ",
            "swipe to right portrait",

            "swing to left landscape",
            "swing to right landscape",
            "swing to left portrait ",
            "swing to right portrait",

            "swipe back left landscape",
            "swipe back right landscape",
            "swipe back left portrait ",
            "swipe back right portrait",

            "crossover",
            "crossover clockwise",
            "crossover anti clockwise"
    };

    public static final boolean[] learnable = {
            false, // "still",
            false, // "push",
            false, // "pull",
            false, // "push pull push",
            false, // "pull push pull",
            false, // "pull push pull push",

            true,  // "push pull",
            true,  // "pull push",
            true,  // "push pull push pull",

            true,  // "swipe to left landscape",
            true,  // "swipe to right landscape",
            true,  // "swipe to left portrait ",
            true,  // "swipe to right portrait",

            true,  // "swing to left landscape",
            true,  // "swing to right landscape",
            true,  // "swing to left portrait ",
            true,  // "swing to right portrait",

            true,  // "swipe back left landscape",
            true,  // "swipe back right landscape",
            true,  // "swipe back left portrait ",
            true,  // "swipe back right portrait",

            false, // "crossover",
            true,  // "crossover clockwise",
            true,  // "crossover anti clockwise"
    };

    public GestureEvent() {
    }

    public GestureEvent(boolean c, int t, long du, double speed2, double intensitys, double intensitys2, boolean f, String r, String e, RichFeatureData d) {
        isConclusion = c;
        type = t;
        speed = speed2;
        duration = du;
        intensityMax = intensitys;
        intensityMean = intensitys2;
        isFast = f;
        result = r;
        err = e;
        rich_feature_data = d;
    }


    public boolean isConclusion;
    public int type;
    public long duration;
    public double speed;
    public double intensityMax;
    public double intensityMean;
    public boolean isFast;
    public String result;
    public String err;
    public RichFeatureData rich_feature_data = null;

    @Override
    public Object clone() throws CloneNotSupportedException {

        return super.clone();
    }

    @Override
    public String toString() {
        StringBuilder sBuilder = new StringBuilder();
        sBuilder.append("GestureEvent{");
        sBuilder.append("isConclusion: " + isConclusion);
        sBuilder.append(", type: " + type);
        sBuilder.append(", duration: " + duration);
        sBuilder.append(", speed: " + speed);
        sBuilder.append(", result: " + result);
        sBuilder.append("}");
        return sBuilder.toString();
    }
}
