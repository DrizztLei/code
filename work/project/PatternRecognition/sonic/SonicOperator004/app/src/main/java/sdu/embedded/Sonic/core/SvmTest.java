package sdu.embedded.Sonic.core;//package seu.lab.dolphin.core;
//
//import java.io.IOException;
//
//import android.util.Log;
//
//import libsvm.svm;
//import libsvm.svm_model;
//import libsvm.svm_node;
//
//public class SvmTest {
//
//	static svm_model model = null;
//	
//	public SvmTest() {
//		if(model == null){
//			try {
//				model = svm.svm_load_model("/storage/sdcard0/dolphin_brain.model");
//			} catch (IOException e) {
//				Log.e("SvmTest", e.toString());
//			}
//		}
//	}
//	
//	public double test(double[] data){
//		svm_node[] nodes = new svm_node[data.length];
//		double[] l = new double[3];
//		for (int i = 0; i < nodes.length; i++) {
//			nodes[i] = new svm_node();
//			nodes[i].index = i;//TODO 0?
//			nodes[i].value = data[i];
//		}
//		double rs = svm.svm_predict_probability(model, nodes,l);
//		Log.e("SvmTest", rs+" | p1:"+l[0]+", p2:"+l[1]+", p3"+l[2]);
//		return rs;
//	}
//
//}
