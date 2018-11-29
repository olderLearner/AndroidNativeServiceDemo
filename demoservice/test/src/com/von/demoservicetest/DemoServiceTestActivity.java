package com.von.demoservicetest;

import android.app.Activity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;
import android.os.IBinder;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.von.demoservice.DemoServiceManager;
import com.von.demoservice.IDataCallback;

public class DemoServiceTestActivity  extends Activity {

    public static final String TAG = "DemoServiceTest";

    private Button mRegister;
    private Button mSend;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);
        initView();
    }

    @Override
    protected void onResume() {
        super.onResume();
        DemoServiceManager.instantiate();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private void initView() {

        mRegister = (Button)findViewById(R.id.register);
        mRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View btn) {
                Log.i(TAG, "register call back");
                DemoServiceManager.registerDataCallback(new DataCallback());
            }
        });

        mSend = (Button) findViewById(R.id.sendcmd);
        mSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i(TAG,"send cmd");
                DemoServiceManager.send(20, 18);
            }
        });
    }

    private class DataCallback extends IDataCallback.Stub {
        public void onReceiveBytes(int resultCode, byte[] data) {
            if (null == data) {
                Log.e(TAG, "onReceiveBytes data is null");
                return;
            }
            Log.d(TAG, "resultCode: " + resultCode);
            if (true) {
                StringBuilder b = new StringBuilder("Recv data[" + data.length +"]:[");
                for (int i=0; i<data.length; i++) {
                    b.append(String.format("%x ", data[i]));
                }
                b.append("]");
                Log.d(TAG, b.toString());
            }
        }
    }

}