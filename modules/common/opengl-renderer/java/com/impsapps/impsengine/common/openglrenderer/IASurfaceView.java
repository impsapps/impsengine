package com.impsapps.impsengine.common.openglrenderer;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Build;

public class IASurfaceView extends GLSurfaceView{
    private final IASurfaceRenderer renderer;

    public IASurfaceView(Context context) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 8, 16, 0);

        // Create an OpenGL ES 2.0 context
        setEGLContextClientVersion(2);

        renderer = new IASurfaceRenderer();

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            setPreserveEGLContextOnPause(true);
        }

        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
