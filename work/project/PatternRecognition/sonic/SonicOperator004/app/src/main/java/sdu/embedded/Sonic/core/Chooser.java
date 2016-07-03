package sdu.embedded.Sonic.core;

import sdu.embedded.Sonic.client.GestureData.RichFeatureData;

class Chooser {

    int sample_num = 0;

    public Chooser(int n) {
        sample_num = n;
    }

    RichFeatureData[] choose(RichFeatureData[] datas) {
        if (sample_num < 3 || sample_num > datas.length / 2 || datas.length < sample_num || datas.length < 10)
            return datas;

        double step = (double) datas.length / (double) sample_num;

        RichFeatureData[] datas2 = new RichFeatureData[sample_num];

        for (int i = 0; i < sample_num; i++) {
            int idx = (int) Math.floor(i * step + step / 2 + 0.5d);
            datas2[i] = datas[idx];//
        }
        return datas2;
    }

}