package com.von.demoservice;

oneway interface IDataCallback {
    void onReceiveBytes(int resultCode, in byte[] data);
}