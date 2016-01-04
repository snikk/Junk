package com.b201.rotationtesting;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public Thread th;
    public Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.textView);
        tv.setPivotX(0.0f);
        tv.setPivotY(0.0f);
        tv.setRotation(45);

        button = (Button) findViewById(R.id.mahButton);
        button.setRotation(25);
        Log.d("B201", "button.getPivotX() = " + button.getPivotX() + " | button.getPivotY() = " + button.getPivotY());
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("B201", "Hey... Clicked on this button!");
            }
        });

        button.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d("B201", "event = " + event);
                return true;
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        th = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while (true) {
                        button.setRotation(button.getRotation() + 0.1f);
                        Thread.sleep(16);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        th.start();
    }

    @Override
    protected void onPause() {
        super.onPause();

        try {
            th.interrupt();
            th.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
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
