package com.impsapps.impsengine.misc.bundleinfo;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;

public class BundleInfo {

    private static String appVersion = "";

    public static String getAppVersion(){
        if ("".equals(appVersion)){
            AppState appState = ImpsEngine.getAppState();
            if (appState != null){
                try {
                    Context c = appState.getContext();
                    PackageInfo pInfo = c.getPackageManager().getPackageInfo(c.getPackageName(), 0);
                    appVersion = pInfo.versionName;
                } catch (PackageManager.NameNotFoundException e) {
                    e.printStackTrace();
                }
            }

        }
        return appVersion;
    }
}
