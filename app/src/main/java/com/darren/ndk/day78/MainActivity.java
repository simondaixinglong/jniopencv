package com.darren.ndk.day78;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.JavaCameraView;
import org.opencv.core.Core;
import org.opencv.core.Mat;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity implements CameraBridgeViewBase.CvCameraViewListener {
    private FaceDetection mFaceDetection;
    private File mCascadeFile;
    JavaCameraView cameraView;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("opencv_java3");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Example of a call to a native method
        cameraView = findViewById(R.id.sample_text);
        cameraView.setCameraIndex(Camera.CameraInfo.CAMERA_FACING_FRONT);
        cameraView.setCvCameraViewListener(this);

        copyCascadeFile();
        mFaceDetection = new FaceDetection();
        mFaceDetection.loadCascade(mCascadeFile.getAbsolutePath());

        File file = new File(Environment.getExternalStorageDirectory(), "1.png");
        Log.e("TAG", file.getAbsolutePath());
    }

    private void copyCascadeFile() {
        try {
            // load cascade file from application resources
            InputStream is = getResources().openRawResource(R.raw.haarcascade_frontalface_default);
            File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
            mCascadeFile = new File(cascadeDir, "haarcascade_frontalface_default.xml");
            if (mCascadeFile.exists()) return;
            FileOutputStream os = new FileOutputStream(mCascadeFile);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = is.read(buffer)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            is.close();
            os.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        cameraView.enableView();
    }

    @Override
    protected void onPause() {
        super.onPause();
        cameraView.disableView();
    }

    @Override
    public void onCameraViewStarted(int width, int height) {

    }

    @Override
    public void onCameraViewStopped() {

    }

    // 获取相机的数据 -> Mat -> SurfaceView 上
    @Override
    public Mat onCameraFrame(Mat inputFrame) {
        // 在这里写业务逻辑
        if (this.getResources().getConfiguration().orientation
                == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
                && cameraView.getCameraIndex() == Camera.CameraInfo.CAMERA_FACING_FRONT) {
            Core.rotate(inputFrame, inputFrame, Core.ROTATE_90_COUNTERCLOCKWISE);
        }else if (this.getResources().getConfiguration().orientation
                == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
                && cameraView.getCameraIndex() == Camera.CameraInfo.CAMERA_FACING_BACK) {
            Core.rotate(inputFrame, inputFrame, Core.ROTATE_90_CLOCKWISE);
        }
        mFaceDetection.faceDetection(inputFrame);
        return inputFrame;
    }
}
