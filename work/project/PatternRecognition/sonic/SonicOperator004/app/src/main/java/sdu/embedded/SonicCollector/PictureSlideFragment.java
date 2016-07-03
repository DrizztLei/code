//package sdu.embedded.SonicCollector;
//
//import android.annotation.SuppressLint;
//import android.graphics.Color;
//import android.os.Bundle;
//import android.support.v4.app.Fragment;
//import android.view.LayoutInflater;
//import android.view.View;
//import android.view.ViewGroup;
//import android.widget.ImageView;
//
//import seu.lab.dolphincore.R;
//
//@SuppressLint("ValidFragment")
//public class PictureSlideFragment extends Fragment {
//
//    int id = 0;
//
//    public static String rsString = "";
//
//    static int[] bg = {
//            Color.MAGENTA,
//            Color.CYAN,
//            Color.BLUE,
//            Color.GREEN,
//            Color.RED,
//            Color.YELLOW,
//            Color.MAGENTA,
//            Color.CYAN,
//            Color.BLUE,
//            Color.GREEN,
//            Color.RED,
//            Color.YELLOW
//    };
//
//    public PictureSlideFragment() {
//        super();
//    }
//
//    public PictureSlideFragment(int arg0) {
//        id = arg0;
//    }
//
//    @Override
//    public View onCreateView(LayoutInflater inflater, ViewGroup container,
//                             Bundle savedInstanceState) {
//
//        View v = inflater.inflate(R.layout.fragment_picture_slide, container, false);
//
//        ImageView imageView = (ImageView) v.findViewById(R.id.iv_main_pic);
//        imageView.setBackgroundColor(bg[id]);
//
//        return v;
//    }
//
//}