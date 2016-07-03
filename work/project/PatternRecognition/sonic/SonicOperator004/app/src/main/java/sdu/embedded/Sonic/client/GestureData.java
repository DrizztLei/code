package sdu.embedded.Sonic.client;

import java.io.Serializable;

public class GestureData {

    public static class RichFeatureData implements Serializable {//Serializable序列化用于存取对象
        private static final long serialVersionUID = 1L;
        public int id;
        public int feature_id;
        public String feature_str;
        public double[] data = null;
        public double[][] raw = null;

        @Override
        public String toString() {
            StringBuilder sBuilder = new StringBuilder();//StringBuilder类用于字符串的拼接
            sBuilder.append("SimplePatten{");
            sBuilder.append("data: {");
            for (int i = 0; i < data.length; i++) {
                sBuilder.append(data[i] + ",");
            }
            sBuilder.append("}}");
            return sBuilder.toString();
        }
    }

    public static class SimplePatten implements Serializable {
        private static final long serialVersionUID = 1L;
        public int[] data = null;
        public boolean isFast = false;
        public int time;
        public double speed;
        @Override
        public String toString() {
            StringBuilder sBuilder = new StringBuilder();
            sBuilder.append("SimplePatten{");
            sBuilder.append("data: {");

            for (int i = 0; i < data.length; i++) {
                sBuilder.append(data[i] + ",");
            }

            sBuilder.append("}}");

            return sBuilder.toString();
        }
    }


}
