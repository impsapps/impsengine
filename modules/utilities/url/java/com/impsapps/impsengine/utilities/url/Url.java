package com.impsapps.impsengine.utilities.url;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.Uri;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;

public class Url {
	public static void openUrlInWebview(String url){
		AppState appState = ImpsEngine.getAppState();
		if(appState != null){
			Activity activity = appState.getActivity();
			activity.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse(url)));
		}
	}
	
	public static void openReviewPageInAppstore(){
		AppState appState = ImpsEngine.getAppState();
		if(appState != null){
			Activity activity = appState.getActivity();
			Uri uri = Uri.parse("market://details?id=" + activity.getPackageName());
			Intent goToMarket = new Intent(Intent.ACTION_VIEW, uri);
			try {
				activity.startActivity(goToMarket);
			} catch (ActivityNotFoundException e) {
				activity.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("http://play.google.com/store/apps/details?id=" + activity.getPackageName())));
			}
		}
	}
}
