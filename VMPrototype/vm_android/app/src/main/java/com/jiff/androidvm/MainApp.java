package com.jiff.androidvm;

import android.app.Application;

import com.jiff.androidvm.jni.JNI;

/**
 * Created by jglenn on 8/24/15.
 */
public class MainApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        JNI.init(getApplicationContext());
    }
}
