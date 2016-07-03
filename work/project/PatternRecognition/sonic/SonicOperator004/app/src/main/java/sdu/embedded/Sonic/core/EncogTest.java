package sdu.embedded.Sonic.core;//package seu.lab.dolphin.core;
//
//import java.io.IOException;
//import org.encog.neural.data.NeuralData;
//import org.encog.neural.data.NeuralDataPair;
//import org.encog.neural.data.basic.BasicNeuralData;
//import org.encog.neural.data.basic.BasicNeuralDataPair;
//import org.encog.neural.networks.BasicNetwork;
//import org.encog.util.SerializeObject;
//import android.os.Environment;
//import android.util.Log;
//
//class EncogTest {
//	BasicNetwork network;
//	public EncogTest(){
//
//		try {			
//			network = (BasicNetwork) SerializeObject.load(
//					Environment.getExternalStorageDirectory()+"/dolphin_brain");
//
//		} catch (ClassNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			Log.e("EncogTest", e.toString());
//			e.printStackTrace();
//		}
//
//	}
//	public double[] test(double[] data) {
//		NeuralDataPair pair = new BasicNeuralDataPair(new BasicNeuralData(data));
//
//		final NeuralData output = network.compute(pair.getInput());
//
//		double[] rs = new double[AudioProcessThread.TYPE];
//		String msg = "";
//		
//		for (int i = 0; i < rs.length; i++) {
//			rs[i] = output.getData(i);
//			rs[i] = rs[i] < 0.1 ? 0 : rs[i];
//			rs[i] = rs[i] > 0.9 ? 1 : rs[i];
//			rs[i] = rs[i] == 1 || rs[i] == 0 ? rs[i] : 0.5;
//			msg+=rs[i]+",";
//		}
//		Log.e("rs", msg);
//		return rs;
//	}
//}
