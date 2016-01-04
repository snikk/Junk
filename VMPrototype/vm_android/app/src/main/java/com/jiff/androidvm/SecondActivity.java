package com.jiff.androidvm;

import android.os.Bundle;
import android.os.PersistableBundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import com.jiff.androidvm.views.ViewNode;

/**
 * Created by jglenn on 8/24/15.
 */
public class SecondActivity extends BaseActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ViewNode vn = getIntent().getParcelableExtra("layout");
        if (vn != null) {
            printViewNode(vn);
        }
        setContentView(createNode(vn));

//        Button b = (Button) findViewById(R.id.mahButton);
//        b.setOnTouchListener(new View.OnTouchListener() {
//            @Override
//            public boolean onTouch(View v, MotionEvent event) {
//                Log.d("Jiff", "event = " + event);
//                return false;
//            }
//        });
    }

    public void printViewNode(ViewNode vn) {
        Log.d("Jiff", "ViewNode | rect = " + vn.margins + " | vn.width = " + vn.width + " | vn.height = " + vn.height);
        Log.d("Jiff", "CHILDREN!-------------------------------------------------");
        if (vn.children != null) {
            for (ViewNode n : vn.children)
                printViewNode(n);
        }
        Log.d("Jiff", "END_CHILDREN!-------------------------------------------------");
    }

    private View createNode(ViewNode vn) {
        View v;
        switch (vn.type) {
            case ViewNode.RELATIVE:
                RelativeLayout rl = new RelativeLayout(this);
                if (vn.children != null) {
                    for (ViewNode ch : vn.children) {
                        rl.addView(createNode(ch));
                    }
                }
                v = rl;
                break;
            case ViewNode.VIEW:
                v = new View(this);
                break;

            default:
                return null;
        }

        v.setId(vn.id);

        RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(vn.width, vn.height);
        lp.setMargins(vn.margins.left, vn.margins.top, vn.margins.right, vn.margins.bottom);
        v.setBackgroundColor(vn.bgColor);

        if (vn.relationships != null) {
            for (ViewNode.Relationship relation : vn.relationships) {
                lp.addRule(relation.relationship, relation.otherID);
            }
        }

        v.setLayoutParams(lp);

        return v;
    }
}
