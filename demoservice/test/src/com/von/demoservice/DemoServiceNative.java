package com.von.demoservice;

import android.os.Binder;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;

//import com.von.demoservice.IDataCallback;
import android.util.Log;

public abstract class DemoServiceNative extends Binder implements IDemoService
{
    private static final String TAG = "Bn_Demo";
    static public IDemoService asInterface(IBinder obj)
    {
        if (obj == null) {
            return null;
        }
        IDemoService in = 
            (IDemoService)obj.queryLocalInterface(descriptor);
        if (in != null) {
            return in;
        }

        return new DemoServiceProxy(obj);
    }

    DemoServiceNative()
    {
        attachInterface(this, descriptor);
    }

    public boolean onTransact(int code, Parcel data, Parcel reply, int flags)
    {
        try {
            switch (code) {
                case IDemoService.SEND_TRANSACTION: {
                    Log.i(TAG,"send");
                    data.enforceInterface(IDemoService.descriptor);
                    int cmd = data.readInt();
                    int subCmd = data.readInt();
                    int ret = send(cmd, subCmd);
                    reply.writeInt(ret);
                    return true;
                }

                case IDemoService.REGISTER_DATA_CALLBACK_TRANSACTION: {
                    Log.i(TAG,"register data callback");
                    data.enforceInterface(IDemoService.descriptor);
                    IDataCallback client = IDataCallback.Stub.asInterface(data.readStrongBinder());
                    registerDataCallback(client);
                    return true;
                }
            }
        } catch (RemoteException e) {

        }
        return false;
    }

    public IBinder asBinder()
    {
        return this;
    }
}

class DemoServiceProxy implements IDemoService {
    private static final String TAG = "Bp_Demo";
    private IBinder mRemote;
    public DemoServiceProxy(IBinder remote) {
        mRemote = remote;
    }

    public IBinder asBinder() {
        return mRemote;
    }

    public int send(int cmd, int subCmd) throws RemoteException {
        Log.i(TAG,"send cmd" + cmd + " subCmd: " + subCmd);
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();

        data.writeInterfaceToken(IDemoService.descriptor);
        data.writeInt(cmd);
        data.writeInt(subCmd);

        mRemote.transact(SEND_TRANSACTION, data, reply, 0);
        int ret = reply.readInt();
        reply.recycle();
        data.recycle();
        return ret;
    }

    public void registerDataCallback(IDataCallback callback) throws RemoteException {
        Log.i(TAG,"register data callback");
        Parcel data = Parcel.obtain();
        Parcel reply = Parcel.obtain();

        data.writeInterfaceToken(IDemoService.descriptor);
        data.writeStrongBinder(callback.asBinder());

        mRemote.transact(REGISTER_DATA_CALLBACK_TRANSACTION, data, reply, 0);
        reply.recycle();
        data.recycle();
        return;
    }

}