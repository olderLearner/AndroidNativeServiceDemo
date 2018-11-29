package com.von.demoservice;

import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import java.lang.reflect.InvocationTargetException;
import java.lang.Class;
import java.lang.reflect.Method;
import com.von.demoservice.IDataCallback;

public class DemoServiceManager {
    private static final String TAG = "DemoManager";

    public static final int CMD_UPDATE_CONFIG = 1;
    public static final int CMD_SEND_DATA = 2;

    public static final int SUBCOM_NONE = 0;
    public static final int SUBCMD_UPDATE_CONFIG_VHAL = 1;
    public static final int SUBCMD_UPDATE_CONFIG_CAN = 2;
    public static final int SUBCMD_UPDATE_CONFIG_ADAS = 3;

    private static IDemoService sService;
    private static IDemoService getDemoService() {
        if (sService != null) {
            return sService;
        }
        IBinder binder = getDemoServiceBinder();
        sService = DemoServiceNative.asInterface(binder);
        return sService;
    }

    private static IBinder getDemoServiceBinder() {

        try {
            Class<?> clazz = Class.forName("android.os.ServiceManager");
            // Method[] methods = clazz.getMethods();
            // for (Method method : methods) {
            // }
            Method getService = clazz.getDeclaredMethod("getService", String.class);
            IBinder binder = (IBinder) getService.invoke(null, "von.demoservice");
            return binder;
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (SecurityException e) {
            e.printStackTrace() ;
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void instantiate() {
        getDemoService();
    }

    public static void registerDataCallback(IDataCallback callback) {
        IDemoService service = getDemoService();
        if (service == null) {
            Log.e(TAG, "can't get demo service");
            return;
        }
        Log.i(TAG, "registerDataCallback");
        try {
            service.registerDataCallback(callback);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public static int send(int cmd, int subCmd) {
        IDemoService service = getDemoService();
        if (service == null) {
            Log.w(TAG, "can't get demo service");
            return -1;
        }
        int ret = -1;
        Log.i(TAG, "send cmd: " + cmd+ " subCmd: " + subCmd);
        try {
            ret = service.send(cmd, subCmd);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return ret;
    }
}