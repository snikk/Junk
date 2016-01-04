package com.jiff.androidvm;

import android.app.Activity;

import com.jiff.androidvm.jni.JNI;

/**
 * Created by jglenn on 8/24/15.
 */
public class BaseActivity extends Activity {
    @Override
    protected void onPause() {
        super.onPause();
        JNI.instance().setActivity(null);
    }

    @Override
    protected void onResume() {
        super.onResume();
        JNI.instance().setActivity(this);
    }
}
