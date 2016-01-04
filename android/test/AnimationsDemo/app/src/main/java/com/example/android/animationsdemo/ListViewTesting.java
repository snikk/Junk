package com.example.android.animationsdemo;

import android.app.Activity;
import android.database.DataSetObserver;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.ListAdapter;
import android.widget.ListView;

import java.util.List;

/**
 * Created by jglenn on 1/3/16.
 */
public class ListViewTesting extends Activity implements ListAdapter {
    public List<Item> items;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_list_view);

        ListView lv = (ListView)findViewById(R.id.listView);
        lv.setAdapter(this);

        items = new Item[] {
                new Item("Hey hey", this.getClass()),
                new Item("Another", this.getClass()),
                new Item("Third", this.getClass()),
                new Item("Fourth", this.getClass()),
                new Item("Fifth", this.getClass()),
                new Item(" hey", this.getClass()),
                new Item("Hey hey", this.getClass()),
        };
    }

    @Override
    public boolean areAllItemsEnabled() {
        return true;
    }

    @Override
    public boolean isEnabled(int position) {
        return true;
    }

    @Override
    public void registerDataSetObserver(DataSetObserver observer) {

    }

    @Override
    public void unregisterDataSetObserver(DataSetObserver observer) {

    }

    @Override
    public int getCount() {
        return 0;
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        return null;
    }

    @Override
    public int getItemViewType(int position) {
        return 0;
    }

    @Override
    public int getViewTypeCount() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    private class Item {
        public String str;
        public Class<? extends Activity> activityClass;

        public Item(String str, Class<? extends Activity> activityClass) {
            this.str = str;
            this.activityClass = activityClass;
        }
    }
}
