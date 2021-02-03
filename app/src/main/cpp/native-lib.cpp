#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include <android/log.h>
#include "opencv2/face.hpp"
#include <vector>

using namespace cv;
using namespace face;
using namespace std;
#define TAG "FACE_TAG"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// 加载人脸识别的级联分类器
CascadeClassifier cascadeClassifier;
// android native 源码 Ptr<Xxx> -> BasicFaceRecognizer*
Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_loadCascade(JNIEnv *env, jobject instance,
                                                    jstring filePath_) {
    const char *filePath = env->GetStringUTFChars(filePath_, 0);

    cascadeClassifier.load(filePath);
    LOGE("人脸识别级联分类器加载成功");
    env->ReleaseStringUTFChars(filePath_, filePath);
}

// 马赛克人脸效果，不让大家看到我
void mosaicFace(Mat mat) {
    // 获取图片宽高
    int src_w = mat.cols;
    int src_h = mat.rows;

    // 省略人脸识别
    int rows_s = src_h / 6;
    int rows_e = src_h * 5 / 6;
    int cols_s = src_w / 6;
    int cols_e = src_w * 5 / 6;
    int size = 15;

    for (int rows = rows_s; rows < rows_e; rows += size) {
        for (int cols = cols_s; cols < cols_e; cols += size) {
            int pixels = mat.at<int>(rows, cols);
            for (int m_rows = 1; m_rows < size; ++m_rows) {
                for (int m_cols = 1; m_cols < size; ++m_cols) {
                    mat.at<int>(rows + m_rows, cols + m_cols) = pixels;
                }
            }
        }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_faceDetection__J(JNIEnv *env, jobject instance,
                                                         jlong nativeObj) {
    Mat *src = reinterpret_cast<Mat *>(nativeObj);

    int width = src->rows;
    int height = src->cols;

    Mat grayMat;
    // 2. 转成灰度图，提升运算速度，灰度图所对应的 CV_8UC1 单颜色通道，信息量少 0-255 1u
    cvtColor(*src, grayMat, COLOR_BGRA2GRAY);

    // 4. 检测人脸，这是个大问题
    // 参数 1.1 会采取上采样和降采样 ，缩放比例
    // 参数 3 检测多少次
    // 参数 Size(width / 2, height / 2) 最小脸的大小
    std::vector<Rect> faces;
    cascadeClassifier.detectMultiScale(grayMat, faces, 1.1, 3, 0, Size(width / 2, height / 2));

    if (faces.size() != 1) {
        mosaicFace(*src);
        return;
    }

    // 把脸框出来
    Rect faceRect = faces[0];
    rectangle(*src, faceRect, Scalar(255, 0, 0, 255), 4, LINE_AA);

    // 不断检测，录入 10 张，张张嘴巴，眨眨眼睛 ，保证准确率
    // 还需要注意一点，确保人脸大小一致，reSize(128,128) ,确保收集到的人脸眼睛尽量在一条线上
    // 与服务端进行比对，是不是我

    // 用一个计数器，这里我们做及时的
    Mat face = (*src)(faceRect).clone();
    resize(face, face, Size(128, 128));
    cvtColor(face, face, COLOR_BGRA2GRAY);
    // 直方均衡，harr 检测人脸
    int label = model->predict(face);
    // 训练的时候存的是 11
    if (label == 11) {
        // 识别到了自己
        LOGE("识别到了自己");
        putText(*src, "Darren", Point(faceRect.x + 20, faceRect.y - 20),
                HersheyFonts::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0, 255),2,LINE_AA);
    } else {
        // 不是自己
        LOGE("不是自己");
        putText(*src, "UnKnow", Point(faceRect.x + 20, faceRect.y - 20),
                HersheyFonts::FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0, 255),2,LINE_AA);
    }
    // 速度， 准确率, 人脸尽量正常
    mosaicFace((*src)(faceRect));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_trainingPattern(JNIEnv *env, jobject instance) {
    // 训练样本，这一步是在数据采集做的
    // train it
    vector<Mat> faces;
    vector<int> labels;

    // 样本比较少
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            Mat face = imread(format("/storage/emulated/0/s%d/%d.pgm", i, j), 0);
            if (face.empty()) {
                LOGE("face mat is empty");
                continue;
            }
            // 确保大小一致
            resize(face, face, Size(128, 128));
            faces.push_back(face);
            labels.push_back(i);
        }
    }

    for (int i = 1; i <= 8; ++i) {
        Mat face = imread(format("/storage/emulated/0/face_%d.png", i), 0);
        if (face.empty()) {
            LOGE("face mat is empty");
            continue;
        }
        resize(face, face, Size(128, 128));
        faces.push_back(face);
        labels.push_back(11);
    }

    // 训练方法
    Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
    // 采集了八张，同一个人 label 一样
    model->train(faces, labels);
    // 训练样本是 xml ，本地
    model->save("/storage/emulated/0/face_darren_pattern.xml");// 存的是处理的特征数据
    LOGE("樣本訓練成功");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_darren_ndk_day78_FaceDetection_loadPattern(JNIEnv *env, jobject instance,
                                                    jstring patternPath_) {
    const char *patternPath = env->GetStringUTFChars(patternPath_, 0);
    // 加载样本数据，Error:(142, 12) error: no matching member function for call to 'load' 怎么搞？
    // model->load(patternPath);
    FileStorage fs(patternPath, FileStorage::READ);
    // 报错，没有提示
    // CV_Assert(fs.isOpened());
    // 抛个 java 异常
    FileNode fn = fs.getFirstTopLevelNode();
    model->read(fn);
    env->ReleaseStringUTFChars(patternPath_, patternPath);
    LOGE("训练样本加载成功");
}