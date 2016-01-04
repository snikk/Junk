package com.jiff.androidvm.jni;

import android.content.Context;
import android.content.Intent;
import android.graphics.Rect;
import android.util.Log;

import com.jiff.androidvm.BaseActivity;
import com.jiff.androidvm.views.ViewNode;

/**
 * Created by jglenn on 8/24/15.
 */
public class JNI {
    private static JNI jni;
    static {
        System.loadLibrary("JNIFunctions");
    }

    private Context context;
    private BaseActivity activity;

    public static void init(Context context) {
        if (jni != null) {
            Log.d("Jiff", "Already called init!");
            return;
        }
        jni = new JNI(context);
    }

    public static JNI instance() {
        return jni;
    }

    public static native String getString();
    public static native void startActivity();
    public static native void runExecutable(byte[] str, int size);

    public JNI(Context context) {
        this.context = context;
    }

    public void setActivity(BaseActivity activity) {
        this.activity = activity;
    }

    public BaseActivity getActivity() {
        return activity;
    }

    public static void launchActivity(Class clazz) {
        Intent i = new Intent(jni.context, clazz);
        i.setFlags(i.getFlags() | Intent.FLAG_ACTIVITY_NEW_TASK);

        ViewNode vn = new ViewNode();
        vn.children = new ViewNode[2];
        vn.margins = new Rect(10, 10, 10, 10);
        vn.width = 100;
        vn.height = 100;

        vn.children[0] = new ViewNode();
        vn.children[0].children = new ViewNode[1];
        vn.children[0].margins = new Rect(20, 20, 100, 100);
        vn.children[0].width = 200;
        vn.children[0].height = 50;

        vn.children[1] = new ViewNode();
        vn.children[1].margins = new Rect(5, 9, 700, 300);
        vn.children[1].width = 900;
        vn.children[1].height = 510;

        vn.children[0].children[0] = new ViewNode();
        vn.children[0].children[0].margins = new Rect(1, 2, 3, 4);
        vn.children[0].children[0].width = 10;
        vn.children[0].children[0].height = 10;

        i.putExtra("layout", vn);

        jni.context.startActivity(i);
    }

    public static void launchActivity(Class clazz, ViewNode node) {
        Intent i = new Intent(jni.context, clazz);
        i.setFlags(i.getFlags() | Intent.FLAG_ACTIVITY_NEW_TASK);

        i.putExtra("layout", node);

        jni.context.startActivity(i);
    }
}

