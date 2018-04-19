package com.impsapps.impsengine.common.androidlib;

import android.app.Application;

import com.impsapps.impsengine.common.clib.Library;

public class BaseApplication extends Application {

	@Override
	public void onLowMemory() {
		Library.onMemoryWarning();
		super.onLowMemory();
	}
}
