package com.impsapps.impsengine.common.inputoutput;

import android.support.annotation.Keep;
import android.support.annotation.NonNull;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;

import java.io.File;

public class Storage {

	@Keep
	public static String getPrivateDataDir(){
		AppState appState = ImpsEngine.getAppState();
		if(appState != null){
			File file = appState.getContext().getFilesDir();
			return file.getAbsolutePath();
		}else{
			return "";
		}
	}
}
