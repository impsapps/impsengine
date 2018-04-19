package com.impsapps.impsengine.common.opengl;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Build;
import android.support.annotation.Keep;
import android.support.annotation.Nullable;
import android.view.Display;
import android.view.WindowManager;

import com.impsapps.impsengine.common.androidlib.AppState;
import com.impsapps.impsengine.common.androidlib.ImpsEngine;
import com.impsapps.impsengine.common.clib.Library;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitmapHelper {

	public static int baseWidth = 1920;
	public static int baseHeight = 1080;

	private static int sampleSize = 0;

	private static void setSampleSizeIfNeeded(Context context){
		if (sampleSize == 0){
			WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
			Display display = wm.getDefaultDisplay();

			int width, height;

			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
				Point size = new Point();
				display.getSize(size);
				width = size.x;
				height = size.y;
			}else{
				width = display.getWidth();
				height = display.getHeight();
			}

			if(width <= baseWidth/4 && height <= baseHeight/4) sampleSize=4;
			else if(width <= baseWidth/2 && height <= baseHeight/2) sampleSize=2;
		}
	}

	@Nullable
	@Keep
	public static Bitmap createBitmapFromAsset(String assetName){
		AppState appState = ImpsEngine.getAppState();
		if (appState != null){
			Context context = appState.getContext();
			setSampleSizeIfNeeded(context);

			BitmapFactory.Options options = new BitmapFactory.Options();
			options.inScaled=false;
			options.inSampleSize = sampleSize;

			AssetManager assetManager = appState.getAssetManager();
			while(true){
				try{
					InputStream inputStream;
					Bitmap bitmap = null;
					try {
						inputStream = assetManager.open(assetName);
						bitmap = BitmapFactory.decodeStream(inputStream, null, options);
					} catch (IOException e) {
					}
					return bitmap;
				}catch(OutOfMemoryError e){
					Library.onMemoryWarning();
				}
			}
		}
		return null;
	}

	@Keep
	public static Bitmap createBitmapFromScreen(int x, int y, int width, int height){
		int size = width * height;
		ByteBuffer buffer = ByteBuffer.allocateDirect(size * 4);
		buffer.order(ByteOrder.nativeOrder());
		GLES20.glReadPixels(x, y, width, height, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, buffer);
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		bitmap.copyPixelsFromBuffer(buffer);
		int pixels[] = new int[size];
		bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
		bitmap.setPixels(pixels, size - width, -width, 0, 0, width, height);
		return bitmap;
	}

	private static int getDrawableId(Context context, String name){
		return context.getResources().getIdentifier(name, "drawable", context.getPackageName());
	}

	@Keep
	public static void bind(Bitmap bitmap){
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);

		if (isPow2(bitmap.getWidth()) == false || isPow2(bitmap.getHeight()) == false) {
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);
		}
		GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
	}
	
	private static boolean isPow2(int value){
	    if (value <= 0) return false;
        return (value & (value - 1)) == 0;
	}
}
