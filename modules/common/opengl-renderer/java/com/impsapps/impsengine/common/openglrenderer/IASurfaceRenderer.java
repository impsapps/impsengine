package com.impsapps.impsengine.common.openglrenderer;

import android.opengl.GLSurfaceView;
import android.os.Process;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class IASurfaceRenderer implements GLSurfaceView.Renderer{

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        android.os.Process.setThreadPriority(Process.THREAD_PRIORITY_URGENT_DISPLAY);
        onSurfaceCreated();
    }

    @Override
    public void onDrawFrame(GL10 unused) {
        onDrawFrame();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        onSurfaceChanged(width, height);
    }

    private static native void onSurfaceCreated();
    private static native void onSurfaceChanged(int width, int height);
    private static native void onDrawFrame();
}
