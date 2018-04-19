package com.impsapps.impsengine.common.androidlib;

import android.os.Bundle;

import java.util.ArrayList;
import java.util.List;

public class ImpsEngine {
    //AppState
    private static AppState appState = null;
    private static List<ActivityListener> listeners = new ArrayList<ActivityListener>();

    public static synchronized void setAppState(AppState appState){
        ImpsEngine.appState = appState;
    }

    public static synchronized AppState getAppState(){
        return appState;
    }

    public static synchronized void addActivityListener(ActivityListener listener){
        listeners.add(listener);
    }

    public static synchronized void removeActivityListener(ActivityListener listener){
        listeners.remove(listener);
    }

    public static synchronized void notifyOnCreate(Bundle savedInstanceState){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onCreate(savedInstanceState);
        }
    }

    public static synchronized void notifyOnStart(){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onStart();
        }
    }

    public static synchronized void notifyOnResume(){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onResume();
        }
    }

    public static synchronized void notifyOnPause(){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onPause();
        }
    }

    public static synchronized void notifyOnStop(){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onStop();
        }
    }

    public static synchronized void notifyOnDestroy(){
        for (int i = 0; i < listeners.size(); i++){
            listeners.get(i).onDestroy();
        }
    }
}
