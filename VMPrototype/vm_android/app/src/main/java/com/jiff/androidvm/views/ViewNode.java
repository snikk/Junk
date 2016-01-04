package com.jiff.androidvm.views;

import android.graphics.Rect;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.Size;

/**
 * Created by jglenn on 8/24/15.
 */
public class ViewNode implements Parcelable {
    public static final int RELATIVE  = 1;
    public static final int VIEW = 2;
    public static final int IMAGE = 3;

    public int id;
    public ViewNode[] children;
    public Rect margins;
    public int width;
    public int height;
    public int bgColor;
    public int type;
    public Relationship[] relationships;

    public ViewNode(int id, ViewNode[] children, Rect margins, int width, int height, int bgColor, int type, Relationship[] relationships) {
        this.id = id;
        this.children = children;
        this.margins = margins;
        this.width = width;
        this.height = height;
        this.bgColor = bgColor;
        this.type = type;
        this.relationships = relationships;
    }

    public ViewNode(Parcel parcel) {
        this(parcel, ClassLoader.getSystemClassLoader());
    }

    public ViewNode(Parcel parcel, ClassLoader loader) {
        id = parcel.readInt();
        children = parcel.createTypedArray(CREATOR);
        margins = (Rect) parcel.readValue(loader);
        width = parcel.readInt();
        height = parcel.readInt();
        bgColor = parcel.readInt();
        type = parcel.readInt();
        relationships = parcel.createTypedArray(Relationship.CREATOR);
    }

    public ViewNode() {

    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(id);
        dest.writeTypedArray(children, 0);
        dest.writeValue(margins);
        dest.writeInt(width);
        dest.writeInt(height);
        dest.writeInt(bgColor);
        dest.writeInt(type);
        dest.writeTypedArray(relationships, 0);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Parcelable.Creator<ViewNode> CREATOR = new Parcelable.ClassLoaderCreator<ViewNode>() {
        @Override
        public ViewNode createFromParcel(Parcel source, ClassLoader loader) {
            return new ViewNode(source, loader);
        }

        @Override
        public ViewNode createFromParcel(Parcel source) {
            return new ViewNode(source);
        }

        @Override
        public ViewNode[] newArray(int size) {
            return new ViewNode[size];
        }
    };

    public static class Relationship implements Parcelable {
        public int otherID;
        public int relationship;

        public Relationship() {}
        public Relationship(Parcel parcel) {
            otherID = parcel.readInt();
            relationship = parcel.readInt();
        }
        public Relationship(int otherID, int relationship) {
            this.otherID = otherID;
            this.relationship = relationship;
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeInt(otherID);
            dest.writeInt(relationship);
        }

        public static final Parcelable.Creator<Relationship> CREATOR = new Creator<Relationship>() {
            @Override
            public Relationship createFromParcel(Parcel source) {
                return new Relationship(source);
            }

            @Override
            public Relationship[] newArray(int size) {
                return new Relationship[size];
            }
        };
    }
}
