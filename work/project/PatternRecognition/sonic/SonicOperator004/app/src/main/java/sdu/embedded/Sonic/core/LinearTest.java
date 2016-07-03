package sdu.embedded.Sonic.core;

import android.util.Log;

import java.io.File;
import java.io.IOException;

import de.bwaldvogel.liblinear.Feature;
import de.bwaldvogel.liblinear.FeatureNode;
import de.bwaldvogel.liblinear.Linear;
import de.bwaldvogel.liblinear.Model;
import sdu.embedded.Sonic.client.DolphinCoreVariables;

public class LinearTest {

    static final String TAG = "LinearTest";

    static final String MODEL_ROOT = DolphinCoreVariables.DOLPHIN_HOME + "models/";

    static Model[] models = new Model[4];

    public static String[] nowModels = new String[]{
            "nf_default.dolphin",
            "fn_default.dolphin",
            "nfnf_default.dolphin",
            "cr_default.dolphin"
    };

    public static String[] defaultModels = new String[]{
            "null",
            "nf_default.dolphin",
            "fn_default.dolphin",
            "nfnf_default.dolphin",
            "cr_default.dolphin"
    };

    public LinearTest() {

    }

    static void setModel(String[] modelpaths) throws IOException {
        if (modelpaths.length < 4) {
            Log.e(TAG, "not enough models");
            return;
        }
        for (int i = 0; i < 4; i++) {
            if (modelpaths[i + 1].equals("")) {
                models[i] = null;
                nowModels[i] = "null";
            } else {
                models[i] = Linear.loadModel(new File(MODEL_ROOT + modelpaths[i + 1]));
                nowModels[i] = modelpaths[i + 1];
            }
        }
    }

    public double test_nf(double[] data) {
        if (models[0] == null) {
            Log.e(TAG, "model 0 not found");
            return 0;
        }

        Feature[] nodes = new FeatureNode[data.length];
        double[] p = new double[3];
        //double[] l = new double[3];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new FeatureNode(i + 1, data[i]);//TODO 0?
        }
        Log.i(TAG, "length" + nodes.length);

        double prediction = Linear.predict(models[0], nodes);
        //prediction = Linear.predictProbability(modelA, nodes, p);
        Log.i(TAG, "using: " + nowModels[0]);

        Log.i(TAG, "All: " + prediction + "|||" + p[0] + " " + p[1] + " " + p[2]);

        return CoreSettings.outputTable[0][(int) prediction];
    }

    public double test_fn(double[] data) {
        if (models[1] == null) {
            Log.e(TAG, "model 1 not found");
            return 0;
        }

        Feature[] nodes = new FeatureNode[data.length];
        double[] p = new double[3];
        //double[] l = new double[3];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new FeatureNode(i + 1, data[i]);//TODO 0?
        }
        Log.i(TAG, "length" + nodes.length);

        double prediction = Linear.predict(models[1], nodes);
        Log.i(TAG, "using: " + nowModels[1]);
        Log.i(TAG, "fn All: " + prediction + "|||" + p[0] + " " + p[1] + " " + p[2]);

        return CoreSettings.outputTable[1][(int) prediction];
    }

    public double test_nfnf(double[] data) {
        if (models[2] == null) {
            Log.e(TAG, "model 2 not found");
            return 0;
        }
        Feature[] nodes = new FeatureNode[data.length];
        double[] p = new double[3];
        //double[] l = new double[3];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new FeatureNode(i + 1, data[i]);//TODO 0?
        }
        Log.i(TAG, "length" + nodes.length);

        double prediction = Linear.predict(models[2], nodes);
        Log.i(TAG, "using: " + nowModels[2]);
        Log.i(TAG, "fnfn All: " + prediction + "|||" + p[0] + " " + p[1] + " " + p[2]);

        return CoreSettings.outputTable[2][(int) prediction];
    }

    public double test_cr(double[] data) {
        if (models[3] == null) {
            Log.e(TAG, "model 3 not found");
            return 0;
        }
        Feature[] nodes = new FeatureNode[data.length];
        double[] p = new double[3];
        //double[] l = new double[3];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new FeatureNode(i + 1, data[i]);//TODO 0?
        }
        Log.i(TAG, "length" + nodes.length);

        double prediction = Linear.predict(models[3], nodes);
        Log.i(TAG, "using: " + nowModels[3]);

        Log.i(TAG, "cr All: " + prediction + "|||" + p[0] + " " + p[1] + " " + p[2]);

        return CoreSettings.outputTable[3][(int) prediction];
    }

//	public double test_nf_all_cd(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelnfS, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "S: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return GestureEvent.Gestures.PUSH_PULL.ordinal();
//		
//
//		if(prediction == 1 || prediction == 3) {
//			prediction = Linear.predict(modelnfC, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "C: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_LEFT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_LEFT_P.ordinal();
//		}else if(prediction == 2 || prediction == 4) {
//			prediction = Linear.predict(modelnfD, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "D: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_RIGHT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_RIGHT_P.ordinal();
//		}
//		return 0;
//	}
//	
//	public double test_nfnf_all_cd(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelnfnfS, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "S: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return GestureEvent.Gestures.PUSH_PULL_PUSH_PULL.ordinal();
//		
//
//		if(prediction == 1 || prediction == 3) {
//			prediction = Linear.predict(modelnfnfC, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "C: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_BACK_LEFT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_BACK_LEFT_P.ordinal();
//		}else if(prediction == 2 || prediction == 4) {
//			prediction = Linear.predict(modelnfnfD, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "D: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_BACK_RIGHT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_BACK_RIGHT_P.ordinal();
//		}
//		return 0;
//	}
//	
//	
//	public double test_nf_abcd(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelnfA, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "A: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return GestureEvent.Gestures.PUSH_PULL.ordinal();
//		
//		prediction = Linear.predict(modelnfB, nodes);
//		//prediction = Linear.predictProbability(modelB, nodes, p);
//		Log.i(TAG, "B: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//
//		if(prediction == 0) {
//			prediction = Linear.predict(modelnfC, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "C: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_LEFT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_LEFT_P.ordinal();
//		}else {
//			prediction = Linear.predict(modelnfD, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "D: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWIPE_RIGHT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWIPE_RIGHT_P.ordinal();
//		}
//		return 0;
//	}
//	
//	public double test_fn_all_bcd(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelfnS, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "A: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return GestureEvent.Gestures.PULL_PUSH.ordinal();
//		
//		prediction = Linear.predict(modelfnB, nodes);
//		//prediction = Linear.predictProbability(modelB, nodes, p);
//		Log.i(TAG, "B: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//
//		if(prediction == 0) {
//			prediction = Linear.predict(modelfnC, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "C: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWING_LEFT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWING_LEFT_P.ordinal();
//		}else {
//			prediction = Linear.predict(modelfnD, nodes);
//			//prediction = Linear.predictProbability(modelB, nodes, p);
//			Log.i(TAG, "D: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//			if(prediction == 0) return GestureEvent.Gestures.SWING_RIGHT_L.ordinal();
//			if(prediction == 1) return GestureEvent.Gestures.SWING_RIGHT_P.ordinal();
//		}
//		return 0;
//	}
//	
//	public double test_fn_all_cd(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelfnS, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "A: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return GestureEvent.Gestures.PULL_PUSH.ordinal();
//		
//		if(prediction == 1 || prediction == 3) {
////			prediction = Linear.predict(modelfnC, nodes);
////			//prediction = Linear.predictProbability(modelB, nodes, p);
////			Log.i(TAG, "C: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
////			if(prediction == 0) return GestureEvent.Gestures.SWING_LEFT_L.ordinal();
////			if(prediction == 1) return GestureEvent.Gestures.SWING_LEFT_P.ordinal();
//			return GestureEvent.Gestures.SWING_LEFT_L.ordinal();
//		}else if(prediction == 2 || prediction == 4) {
////			prediction = Linear.predict(modelfnD, nodes);
////			//prediction = Linear.predictProbability(modelB, nodes, p);
////			Log.i(TAG, "D: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
////			if(prediction == 0) return GestureEvent.Gestures.SWING_RIGHT_L.ordinal();
////			if(prediction == 1) return GestureEvent.Gestures.SWING_RIGHT_P.ordinal();
//			return GestureEvent.Gestures.SWING_RIGHT_L.ordinal();
//
//		}
//		return 0;
//	}
//	
//	public double test(double[] data){
//		Feature[] nodes = new FeatureNode[data.length];
//		double[] p = new double[3];
//		//double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelnfA, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "A: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//		
//		if(prediction == 0) return prediction;
//		
//		prediction = Linear.predict(modelnfB, nodes);
//		//prediction = Linear.predictProbability(modelB, nodes, p);
//		Log.i(TAG, "B: "+prediction+"|||"+p[0]+" "+p[1]+" "+p[2]);
//
//		return (prediction+1);
//	}
//
//	
//	public double test_shadow(double[] data) {
//		Feature[] nodes = new FeatureNode[60];
//		double[] shadow = new double[60];
//		
//		for (int k2 = 0; k2 < shadow.length; k2++) {
//			shadow[k2] = 0;
//			for (int l = 0; l < 50; l++) {
//				//shadow[k2] = Math.max(shadow[k2], portableData.data[l*60+k2]);
//				shadow[k2] += data[l*60+k2];
//			}
//			if(shadow[k2] < 0.00001)shadow[k2] = 0;
//		}
//		
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new FeatureNode(i+1,data[i]);//TODO 0?
//		}
//		Log.i(TAG, "length"+nodes.length);
//		
//		double prediction = Linear.predict(modelnfS, nodes);
//		//prediction = Linear.predictProbability(modelA, nodes, p);
//		Log.i(TAG, "S: "+prediction+"|||");
//
//		return (prediction);
//	}


}
