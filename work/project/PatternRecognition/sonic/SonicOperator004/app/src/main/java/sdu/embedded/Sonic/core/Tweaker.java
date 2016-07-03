package sdu.embedded.Sonic.core;

import org.apache.commons.math.MathException;
import org.apache.commons.math.analysis.interpolation.BicubicSplineInterpolatingFunction;
import org.apache.commons.math.analysis.interpolation.BicubicSplineInterpolator;

import android.util.Log;

class Tweaker {

    static final String TAG = "Tweaker";

    int single_width = 0;
    int time_counter = 0;

    public Tweaker() {
    }

    public Tweaker(int width, int time) {
        single_width = width;
        time_counter = time;
        Log.i(TAG, "single_width: " + width);

    }

    double[] tweak(double[][] ori) {
        int ori_width = ori[0].length;
        if (single_width < 1 || single_width > ori[0].length / 2) single_width = ori[0].length / 2;
        if (time_counter < 1) time_counter = 50;

        double[] x = new double[ori.length];
        for (int i = 0; i < x.length; i++) {
            x[i] = i;
        }
        double[] y = new double[ori[0].length];
        for (int i = 0; i < y.length; i++) {
            y[i] = i;
        }

        double step = ((double) x.length - 1) / (time_counter);

        BicubicSplineInterpolator i = new BicubicSplineInterpolator();
        BicubicSplineInterpolatingFunction f = null;

        double[][] time_data = new double[time_counter][ori[0].length];
        try {
            f = i.interpolate(x, y, ori);

            double a = 0;
            double b = 0;
            for (int j = 0; j < time_counter; j++) {
                for (int j2 = 0; j2 < time_data[0].length; j2++) {
                    b = (double) j2;
                    time_data[j][j2] = f.value(a, b);
                    if (time_data[j][j2] < 0.000001) time_data[j][j2] = 0;
                }
                a += step;
            }
        } catch (MathException e) {
            e.printStackTrace();
        }

        double[] newdata = new double[time_counter * single_width * 2];
        for (int i1 = 0; i1 < time_counter; i1++) {
            System.arraycopy(time_data[i1], ori_width / 2 - single_width, newdata, i1 * 2 * single_width, single_width);
            System.arraycopy(time_data[i1], ori_width / 2 + 1, newdata, (i1 * 2 + 1) * single_width, single_width);
        }
        Log.i(TAG, "newdata len: " + newdata.length + " time_counter: " + time_counter + " single_width: " + single_width);
        return newdata;
    }

}


//double[] x = new double[data.length];
//for (int i = 0; i < x.length; i++) {
//	x[i] = i;
//}
//double[] y = new double[data[0].length];
//for (int i = 0; i < y.length; i++) {
//	y[i] = i;
//}
//
//int time_counter = 50;
//double step = ((double)x.length-1) / (time_counter);
//
//BicubicSplineInterpolator i = new BicubicSplineInterpolator();
//BicubicSplineInterpolatingFunction f = null;
//
//double[][] time_data = new double[time_counter][data[0].length];
//try {
//	f = i.interpolate(x, y, data);
//	
//	double a = 0;
//	double b = 0;
//	for (int j = 0; j < time_counter; j++) {
//		for (int j2 = 0; j2 < time_data[0].length; j2++) {
//			b = (double)j2;
//			time_data[j][j2] = f.value(a, b);
//		}
//		a += step;
//	}
//} catch (MathException e) {
//	e.printStackTrace();
//}
//
//double[] newdata;
//double datamax = 0;
//double datamin = 0;
//
//if(data.length < 5){
//	newdata = null;
//	Log.e("gesture", "too fast");
//}else {
//	newdata = new double[time_counter*60];
//	for (int i1 = 0; i1 < newdata.length; i1++) {
//		newdata[i1] = time_data[i1/60][i1%60];
//		if(newdata[i1] < 0.00001) newdata[i1] = 0;
//
//	}
//}