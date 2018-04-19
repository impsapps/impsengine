package com.impsapps.impsengine.common.androidlib;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Resources;

public interface AppState {
    Activity getActivity();
    AssetManager getAssetManager();
    Context getContext();
    Resources getResources();
}
