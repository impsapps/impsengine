package com.impsapps.impsengine.utilities.url;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.support.v4.content.FileProvider;
import android.util.Log;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Share {

    private static String authority = null;

    public static void setAuthorityOfFileProvider(String authority){
        Share.authority = authority;
    }

    public static void share(String text, Bitmap bitmap){
        if (authority == null){
            Log.e("Share:", "Authority has not been set!");
            return;
        }

        AppState appState = ImpsEngine.getAppState();
        if (appState != null){
            File cacheFile = new File(appState.getContext().getExternalCacheDir(), "hitverto.png");
            try {
                FileOutputStream outputStream = new FileOutputStream(cacheFile);
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
                outputStream.flush();
                outputStream.close();

                final Intent intent = new Intent(Intent.ACTION_SEND);
                intent.setType("image/png");
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.putExtra(Intent.EXTRA_TEXT, text);
                Uri path = FileProvider.getUriForFile(appState.getContext(),Share.authority, cacheFile);
                intent.putExtra(Intent.EXTRA_STREAM, path);
                appState.getActivity().startActivity(intent);
            }catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
