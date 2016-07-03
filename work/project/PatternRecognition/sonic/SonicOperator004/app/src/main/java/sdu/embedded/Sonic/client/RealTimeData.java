package sdu.embedded.Sonic.client;

import java.io.Serializable;

public class RealTimeData implements Serializable {

    private static final long serialVersionUID = 1L;

    public static enum State {PUSH, PULL, STILL, CHAOS}

    ;

    public static enum Intensity {LOW, MEDIUM, HIGH}

    public RealTimeData(double radius2, int s, double intensity, int t,
                        int up, int low, double v, double mv,
                        double[] n, double[] f, int[] top,
                        double[] bound, int[] upperarr, int[] lowerarr) {
        radius = radius2;
        state = s;
        intensity = intensity;
        toparr = top;
        upperbound = up;
        lowerbound = low;
        velocity = v;
        max_velocity = mv;
        normal_info = n;
        feature_info = f;
        toparr = top;
        boundarr = bound;
        this.upperarr = upperarr;
        this.lowerarr = lowerarr;
    }

    public double radius;//半径
    public int state;
    public double intensity;
    public int top;
    public int upperbound;
    public int lowerbound;
    public double velocity;
    public double max_velocity;
    public double[] normal_info = null;
    public double[] feature_info = null;
    public int[] toparr = null;
    public double[] boundarr = null;
    public int[] upperarr = null;
    public int[] lowerarr = null;


    @Override
    public String toString() {
        StringBuilder sBuilder = new StringBuilder();
        sBuilder.append("RealTimeData{");
        sBuilder.append("radius: " + radius);
        sBuilder.append(", state: " + state);
        sBuilder.append(", intensity: " + intensity);
        sBuilder.append(", top: " + top);
        sBuilder.append(", upperbound: " + upperbound);
        sBuilder.append(", lowerbound: " + lowerbound);
        sBuilder.append(", velocity: " + velocity);
        sBuilder.append(", max_velocity: " + max_velocity);
        sBuilder.append("}");
        return sBuilder.toString();
    }
}
