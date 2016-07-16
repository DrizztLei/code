package libsvm;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) throws IOException{
		/*
		  String[] trainArgs = {"/home/elvis/final_svm"};//directory of training file  
		  String modelFile = svm_train._main(trainArgs);  
	      String[] testArgs = {"/home/elvis/final_svm", modelFile, "/home/elvis/svm_result"};//directory of test file, model file, result file  
	      Double accuracy = svm_predict._main(testArgs);
	      System.out.println("SVM Classification is done! The accuracy is " + accuracy);
	      */
	      svm_model model = svm.svm_load_model("/home/elvis/final_svm.model");
	      int size = 256;
	      svm_node[] x = new svm_node[size];
	      double[] dec_values = new double[size];
	      for(int i = 0 ; i < size ; i++){
	    	  x[i] = new svm_node();
	    	  x[i].index = i+1;
	    	  x[i].value = Math.random() * 0.3;
	    	  //System.out.println(Math.random());
	    	  //dec_values[i] = Math.random();
	      }
	      String[] parg = {
	    		  	"/home/elvis/final_svm", // 这个是存放测试数据
					"/home/elvis/temp.file.modelt", // 调用的是训练以后的模型
					"/home/elvis/out" }; // 生成的结果的文件的路径
			System.out.println("........SVM运行开始..........");
			//svm_predict p = new svm_predict();
			calculator(null);
	}
	public static int calculator(double [] info) throws IOException{
		String path_test = "/home/elvis/final_svm" , path_model = "/home/elvis/final_svm.model" , path_out = "/home/elvis/out";
	      String[] parg = { path_test , path_model , path_out // 这个是存放测试数据
	    		   // 调用的是训练以后的模型
					 }; // 生成的结果的文件的路径	      
	      svm_predict p = new svm_predict();
	      p.main(parg);
	      Scanner scanner = new Scanner(new File(path_out));
	      double result =  -1;
	      while(scanner.hasNextDouble()){
	    	  result = scanner.nextDouble();
	    	  System.out.println(result);
	      }
	      if(result < 0) throw new IOException();
	      System.out.println(p.accuracy);
	      return (int)(result+0.5);	
	}
}
