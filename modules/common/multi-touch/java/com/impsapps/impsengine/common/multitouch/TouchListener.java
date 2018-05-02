package com.impsapps.impsengine.common.multitouch;

import android.annotation.SuppressLint;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;

@SuppressLint("ClickableViewAccessibility")
public class TouchListener implements SurfaceView.OnTouchListener{

	@Override
	public synchronized boolean onTouch(View view, MotionEvent event) {
		//logMotionEvent(event);
		int action = event.getAction();
		if(isActionPointerDown(action)){
			int index = event.getActionIndex();
			long pointerId = event.getPointerId(index);
			float x = event.getX(index);
			float y = event.getY(index);
			createNewTouchHandler(pointerId, x, y);
			onTouchBegan(pointerId, x, y);
		}else if(action == MotionEvent.ACTION_MOVE){
			int numberOfPointers = event.getPointerCount();
			prepareOnTouchMoved(numberOfPointers);
			for(int i = 0; i < numberOfPointers; i++){
				long pointerId = event.getPointerId(i);
				float x = event.getX(i);
				float y = event.getY(i);
				addTouchMoved(pointerId, x, y);
			}
			executeOnTouchMoved();
		}else if(isActionPointerUp(action)){
			int index = event.getActionIndex();
			long pointerId = event.getPointerId(index);
			float x = event.getX(index);
			float y = event.getY(index);
			onTouchEnded(pointerId, x, y);
			destroyTouchHandler(pointerId);
		}
		try{
			Thread.sleep(10);
		}catch (InterruptedException e){
			e.printStackTrace();
		} 
		return true;
	}

	private static boolean isActionPointerDown(int actionCode){
        return actionCode == MotionEvent.ACTION_DOWN || actionCode % 256 == MotionEvent.ACTION_POINTER_DOWN;
	}

	private static boolean isActionPointerUp(int actionCode){
        return actionCode == MotionEvent.ACTION_UP || actionCode % 256 == MotionEvent.ACTION_POINTER_UP;
	}


	public boolean logMotionEvent(MotionEvent event) {
		switch(event.getAction()){
		case MotionEvent.ACTION_DOWN:
			logEvent(event, "ACTION_DOWN");
			break;
		case MotionEvent.ACTION_POINTER_DOWN:
			logEvent(event, "ACTION_POINTER_DOWN");
			break;
		case MotionEvent.ACTION_MOVE:
			logEvent(event, "ACTION_MOVE");
			break;
		case MotionEvent.ACTION_POINTER_UP:
			logEvent(event, "ACTION_POINTER_UP");
			break;
		case MotionEvent.ACTION_UP:
			logEvent(event, "ACTION_UP");
			break;
		default:
			logEvent(event, event.getAction() + "");
			break;
		}
		return true;
	}

	private void logEvent(MotionEvent event, String action){
		Log.e(action, "[actionIndex]: " + event.getActionIndex() + " [actionId]: " + event.getPointerId(event.getActionIndex()) + " [x]: " + event.getX() + " [y]: " + event.getY());
		String toPrint = "";
		int numberOfPointers = event.getPointerCount();
		for(int i = 0; i < numberOfPointers; i++){
			int pointerId = event.getPointerId(i);
			toPrint += pointerId + " " + event.getX(i) + " " + event.getY(i) + " "; 
		}
		Log.e(numberOfPointers + "", toPrint);
	}

	public static native void createNewTouchHandler(long touchId, float pointX, float pointY);

	public static native void onTouchBegan(long touchId, float pointX, float pointY);
	public static native void prepareOnTouchMoved(int numberOfTouches);
	public static native void addTouchMoved(long touchId, float pointX, float pointY);
	public static native void executeOnTouchMoved();
	public static native void onTouchEnded(long touchId, float pointX, float pointY);

	public static native void destroyTouchHandler(long touchId);

}
