package sdu.embedded.Sonic.client;

public class ContinuousGestureEvent extends GestureEvent {

    public ContinuousGestureEvent(double f, boolean isANewGestureConcluded) {
        super();
        freq = f;
        isEnd = isANewGestureConcluded;
    }

    public double freq;
    public boolean isEnd = false;

    @Override
    public String toString() {
        StringBuilder sBuilder = new StringBuilder();
        sBuilder.append("ContinuousGestureEvent{");
        sBuilder.append("freq: " + freq);
        sBuilder.append(",isEnd: " + isEnd);
        sBuilder.append("}");
        return sBuilder.toString();
    }

}
