package sdu.embedded.Sonic.core;//package seu.lab.dolphin.core;
//
//import java.util.ArrayList;
//
//import android.util.Log;
//
//import weka.classifiers.bayes.BayesNet;
//import weka.classifiers.lazy.IBk;
//import weka.core.Attribute;
//import weka.core.FastVector;
//import weka.core.Instance;
//import weka.core.Instances;
//import weka.core.SerializationHelper;
//import weka.filters.Filter;
//import weka.filters.supervised.attribute.Discretize;
//
//public class WekaTest {
//
//	static IBk ibkA = null;
//	static IBk ibkB = null;
//	static BayesNet bayesNetA = null;
//	static BayesNet bayesNetB = null;
//	static FastVector attsA;
//	static FastVector attsB;
//	static FastVector classValA;
//	static FastVector classValB;
//	static Instances dataRawA = null;
//	static Instances dataRawB = null;
//	static Discretize discretizeA = null;
//	static Discretize discretizeB = null;
//	
//	public WekaTest() {
//		try {
//			ibkA = (IBk) SerializationHelper.read("/storage/sdcard0/nf_A_ibk.dolphin");
//			ibkB = (IBk) SerializationHelper.read("/storage/sdcard0/nf_B_ibk.dolphin");
////			bayesNetA = (BayesNet) SerializationHelper.read("/storage/sdcard0/nf_A_bysnet.dolphin");
////			bayesNetB = (BayesNet) SerializationHelper.read("/storage/sdcard0/nf_B_bysnet.dolphin");
//			discretizeA = (Discretize) SerializationHelper.read("/storage/sdcard0/nf_A_discretize.dolphin");
//			discretizeB = (Discretize) SerializationHelper.read("/storage/sdcard0/nf_B_discretize.dolphin");
//			attsA = new FastVector(251);
//			attsB = new FastVector(251);
//			classValA = new FastVector();
//	        classValA.addElement("push_pull");
//	        classValA.addElement("swipe");
//			classValB = new FastVector();
//	        classValB.addElement("swipe_left");
//	        classValB.addElement("swipe_right");
//			for (int i = 0; i < 250; i++) {
//				Attribute a = new Attribute("data"+i,i);
//				attsA.addElement(a);
//				attsB.addElement(a);
//			}
//			
//			Attribute classA = new Attribute("rs", classValA);
//			Attribute classB = new Attribute("rs", classValB);
//						
//			attsA.addElement(classA);
//			attsB.addElement(classB);
//
//			dataRawA = new Instances("TestInstances",attsA,0);
//			dataRawB = new Instances("TestInstances2",attsB,0);
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	}
//	
//	public static double test(double[] data){
//		
//		double[] instanceValue = new double[dataRawA.numAttributes()];
//		for (int i = 0; i < instanceValue.length-1; i++) {
//			instanceValue[i] = data[i];
//		}
//		instanceValue[50] = -1;
//		
//		Instance instanceA = new Instance(1.0, instanceValue);
//		
//		dataRawA.delete();
//        dataRawA.add(instanceA);
//        dataRawA.setClassIndex(dataRawA.numAttributes() - 1);
//
//		
//        Instances newInstancesA = null;
//		try {
//			newInstancesA = Filter.useFilter(dataRawA, discretizeA);
////			newInstancesA = dataRawA;
//		} catch (Exception e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}
//        newInstancesA.setClassIndex(newInstancesA.numAttributes() - 1);
//		
//        double rs = 0;
//		try {
//			rs = ibkB.classifyInstance(newInstancesA.firstInstance());
//			
//			Log.e("WekaTest","A: "+rs);
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		
//		if(rs == 0) return rs;
//		
//		double[] instanceValue2 = new double[dataRawB.numAttributes()];
//		for (int i = 0; i < instanceValue.length-1; i++) {
//			instanceValue2[i] = data[i];
//		}
//		instanceValue2[50] = -1;		
//		Instance instanceB = new Instance(1.0, instanceValue2);
//		
//		dataRawB.delete();
//        dataRawB.add(instanceB);
//        dataRawB.setClassIndex(dataRawB.numAttributes() - 1);
//        
//        Instances newInstancesB = null;
//		try {
//			newInstancesB = Filter.useFilter(dataRawB, discretizeB);
////			newInstancesB = dataRawB;
//		} catch (Exception e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}
//        newInstancesB.setClassIndex(newInstancesB.numAttributes() - 1);
//        
//		try {
//			rs = ibkB.classifyInstance(newInstancesB.firstInstance());
//			
//			Log.e("WekaTest","B: "+rs);
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		
//		return (rs+1);
//	}
//	
//}
