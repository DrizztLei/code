package com.hillsidewatchers.sdu.sonicoperator.Analyzer;

import android.os.Environment;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
	private static String
			path_test = "",
			path_model  = "",
			path_out = "" ;
//
//
//	public static void main(String[] args) throws IOException{
//
//	      String[] parg = {
//	    		  	"/home/elvis/final_svm", // 这个是存放测试数据
//					"/home/elvis/sample.data.model", // 调用的是训练以后的模型
//					"/home/elvis/out" }; // 生成的结果的文件的路径
//			System.out.println("........SVM运行开始..........");
//			svm_predict p = new svm_predict();
//			calculator(null);
//	}
	public static int calculator(double [] info) throws IOException{
		path_test = Environment.getExternalStorageDirectory().getAbsolutePath()+"/sonic/test" ;
				path_model = Environment.getExternalStorageDirectory().getAbsolutePath()+"/sonic/set.modules" ;
				path_out = Environment.getExternalStorageDirectory().getAbsolutePath()+"/sonic/out";
		File file = new File(path_test);

		FileWriter fileWritter = new FileWriter(file.getAbsolutePath(),true);
		BufferedWriter bufferWritter = new BufferedWriter(fileWritter);
		bufferWritter.write("1 ");
		for (int i = 0 ; i < info.length ; i++){
			bufferWritter.write((i+1)+":"+info[i]+" ");
		}
		bufferWritter.flush();
		bufferWritter.close();
		String[] parg = {     path_test	    // 这个是存放测试数据
				  			, path_model	// 调用的是训练以后的模型
				  			, path_out   }; // 生成的结果的文件的路径
	      svm_predict p = new svm_predict();
		  p.main(parg);
	      Scanner scanner = new Scanner(new File(path_out));
	      double result =  -1;
	      while(scanner.hasNextDouble()){
	    	  result = scanner.nextDouble();
	    	  System.out.println("Get the result for : " + result);
	      }
		if(!file.exists()){
			file.createNewFile();
		}else{
			file.delete();
			file.createNewFile();
		}
		File file_out = new File(path_out);
		if(!file_out.exists()){
			file_out.createNewFile();
		}else{
			file_out.delete();
			file_out.createNewFile();
		}
	      if(result < 0) throw new IOException();
	      return (int)(result+0.5);
	}
}
