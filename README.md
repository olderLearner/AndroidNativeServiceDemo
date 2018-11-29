# AndroidNativeServiceDemo
Demo for android native service, with java proxy api, java client could access server without jni implementation

Note:
1. based on android 4.4.3
2. add product name in device.mk, eg: device/xxx/xx.mk

    +PRODUCT_PACKAGES += \
    +   demoserver \
    +   libdemoservice

3. add startup command in rc script

    +service demoserver  system/vendor/bin/demoserver
    +   class main
    +   user system
    +   group system

4. demoserver was started in init phase, 
   test app register a callback from java side, then send a message to server, 
   server send callback data to client once got the message from client.
