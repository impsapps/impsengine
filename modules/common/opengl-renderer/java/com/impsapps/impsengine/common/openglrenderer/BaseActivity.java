package com.impsapps.impsengine.common.openglrenderer;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.os.Bundle;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;
import com.impsapps.impsengine.common.multitouch.TouchListener;

public class BaseActivity extends Activity implements AppState{

    protected IASurfaceView surfaceView;

    @Override
    public synchronized void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        ImpsEngine.setAppState(this);

        nativeOnCreate();

        surfaceView = new IASurfaceView(this);
        surfaceView.setOnTouchListener(new TouchListener());
        ImpsEngine.notifyOnCreate(savedInstanceState);
    }

    @Override
    public synchronized void onStart(){
        super.onStart();
        ImpsEngine.notifyOnStart();
    }

    @Override
    public synchronized void onResume(){
        super.onResume();
        ImpsEngine.notifyOnResume();
        surfaceView.onResume();
    }

    @Override
    public synchronized void onPause(){
        super.onPause();
        if(android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.HONEYCOMB){
            nativeSaveGamestate();
        }
        ImpsEngine.notifyOnPause();
        surfaceView.onPause();
    }

    @Override
    public synchronized void onStop(){
        super.onStop();
        if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB){
            nativeSaveGamestate();
        }
        nativeSwitchToPausescreen();
        ImpsEngine.notifyOnStop();
    }

    @Override
    public synchronized void onDestroy(){
        super.onDestroy();
        ImpsEngine.setAppState(null);
        ImpsEngine.notifyOnDestroy();
    }

    @Override
    public Activity getActivity(){
        return this;
    }

    @Override
    public AssetManager getAssetManager(){
        return getAssets();
    }

    @Override
    public Context getContext(){
        return this;
    }

    private static native void nativeOnCreate();
    private static native void nativeSwitchToPausescreen();
    private static native void nativeSaveGamestate();
    private static native void nativeDestroyResources();

}
