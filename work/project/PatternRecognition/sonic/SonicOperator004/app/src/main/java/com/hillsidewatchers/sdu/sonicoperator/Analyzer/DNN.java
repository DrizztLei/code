package com.hillsidewatchers.sdu.sonicoperator.Analyzer;

import android.annotation.SuppressLint;
import android.os.Environment;
import android.util.Log;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DNN {
    private double weight[][][];
    private static DNN dnn = new DNN();
    private int[] info;
    private double[][] offset;
    private double[][] level;
    private int argc_output, argc_input, argc_level;
    private double[] output;
    private File file;
    private Scanner scanner;

    private DNN() {
        loadData();
        initWeight();
    }

    private void initWeight() {
        // TODO Auto-generated method stub
        weight = new double[argc_level + 1][][];
        for (int i = 0; i < argc_level; ++i) {
            if (i == 0) {
                weight[0] = new double[argc_input][info[0]];
            } else {
                weight[i] = new double[info[i - 1]][info[i]];
            }
        }
        weight[argc_level] = new double[info[argc_level - 1]][argc_output];
        double var;
        for (int i = 0; i < argc_level; ++i) {
            if (i == 0) {
                for (int j = 0; j < argc_input; ++j) {
                    for (int k = 0; k < info[0]; ++k) {
                        var = scanner.nextDouble();
                        weight[0][j][k] = var;
                    }
                }
            } else {
                for (int j = 0; j < info[i - 1]; ++j) {
                    for (int k = 0; k < info[i]; ++k) {
                        var = scanner.nextDouble();
                        weight[i][j][k] = var;
                    }
                }
            }
        }
        for (int i = 0; i < info[argc_level - 1]; ++i) {
            for (int j = 0; j < argc_output; ++j) {
                var = scanner.nextDouble();
                weight[argc_level][i][j] = var;
            }
        }
        level = new double[argc_level][];
        for (int i = 0; i < argc_level; i++) {
            level[i] = new double[info[i]];
        }
        output = new double[argc_output];
    }

    @SuppressLint("LongLogTag")
    private void loadData() {
        // TODO Auto-generated method stub
        scanner = null;
        try {
            String path = Environment.getExternalStorageDirectory().getAbsolutePath()+"/sonic/net.conf";
            Log.e("sonic->path",path);
            file = new File(path);
            scanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            Log.e("Error for the File not found" , "Commit");

        }
        argc_input = scanner.nextInt();
        argc_level = scanner.nextInt();
        argc_output = scanner.nextInt();
        info = new int[argc_level];
        for (int i = 0; i < argc_level; i++) {
            info[i] = scanner.nextInt();
        }
        offset = new double[argc_level + 1][];
        for (int i = 0; i < argc_level; i++) {
            offset[i] = new double[info[i]];
        }
        offset[argc_level] = new double[argc_output];
        for (int i = 0; i < argc_level; i++) {
            for (int j = 0; j < info[i]; j++) {
                offset[i][j] = scanner.nextDouble();
            }
        }
        for (int i = 0; i < argc_output; i++) {
            offset[argc_level][i] = scanner.nextDouble();
        }
    }

    public static DNN getInstead() {
        if (dnn == null) {
            dnn = new DNN();
        }
        return dnn;
    }

    public int calculator(double[] input) {
        for (int i = 0; i < info[0]; ++i) {
            double sum = 0;
            for (int j = 0; j < argc_input; ++j) {
                sum += input[j] * weight[0][j][i];
            }
            level[0][i] = sigmod(sum + offset[0][i]);
        }
        for (int i = 1; i < argc_level; ++i) {
            for (int j = 0; j < info[i]; ++j) {
                double sum = 0;
                for (int k = 0; k < info[i - 1]; ++k) {
                    sum += level[i - 1][k] * weight[i][k][j];
                }
                level[i][j] = sigmod(sum + offset[i][j]);
            }
        }
        for (int i = 0; i < argc_output; ++i) {
            double sum = 0;
            for (int j = 0; j < info[argc_level - 1]; ++j) {
                sum += level[argc_level - 1][j] * weight[argc_level][j][i];
            }
            output[i] = (sum + offset[argc_level][i]);
        }
        return getResult();
    }

    private void pre_process(double[] input) {
        for (int i = 0; i < argc_input; i++) {
            input[i] *= 100;
        }
    }

    private int getResult() {
        int max = 0;
        for (int i = 0; i < argc_output; ++i) {
            if (output[i] > output[max]) {
                max = i;
            }
            Log.e("DNN>GETRESULT：", "" + output[i]);
        }
        return max;

    }

    private double sigmod(double value) {
        return value <= 0 ? 0 : value;
    }
}
