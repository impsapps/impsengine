package com.impsapps.impsengine.common.androidlib;

import android.os.Bundle;

public interface ActivityListener {
    void onCreate(Bundle savedInstanceState);
    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();
}
