//package sdu.embedded.SonicCollector;
//
//import android.app.Activity;
//import android.content.ComponentName;
//import android.content.Intent;
//import android.content.ServiceConnection;
//import android.os.Bundle;
//import android.os.IBinder;
//
//import seu.lab.dolphincore.R;
//
//public class TTActivity extends Activity {
//    private ServiceConnection connection = new ServiceConnection() {
//
//        @Override
//        public void onServiceDisconnected(ComponentName name) {
//
//        }
//
//        @Override
//        public void onServiceConnected(ComponentName name, IBinder service) {
//
//        }
//    };
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_tt);
//        Intent bindIntent = new Intent(this, CollectorService.class);
//        bindService(bindIntent, connection, BIND_AUTO_CREATE);
//    }
//}
