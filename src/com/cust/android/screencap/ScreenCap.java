package com.cust.android.screencap;

public class ScreenCap {

    static {
        System.loadLibrary("scrcap");
    }

    static native void captureScreenToFile(String fileName);
}
