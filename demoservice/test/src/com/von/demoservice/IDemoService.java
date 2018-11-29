package com.von.demoservice;

import android.os.IBinder;
import android.os.IInterface;
import android.os.RemoteException;

//import com.von.demoservice.IDataCallback;

public interface IDemoService extends IInterface
{
    public int send(int cmd, int subCmd) throws RemoteException;
    public void registerDataCallback(IDataCallback callback) throws RemoteException;
    static final String descriptor = "von.IDemoService";

    int SEND_TRANSACTION = IBinder.FIRST_CALL_TRANSACTION;
    int REGISTER_DATA_CALLBACK_TRANSACTION = IBinder.FIRST_CALL_TRANSACTION + 1;
}