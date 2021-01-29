#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/2_04.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	Mat gary;
	cvtColor(src, gary, CV_BGR2GRAY);

	// 80 次 音视频 ，opencv 深宽 （音视频基础理论） 13 次 ，5 次理论知识，5 次实战
	imshow("src",src);

	// 性能优化，android 底层源码 NDK  binder（用户空间，内核空间）NDK 
	// Histogram  直方图
	Mat dst;
	equalizeHist(gary, dst);
	imshow("dst", dst);

	// 考验：2_05 彩色的，分出来，Y 提取出来，均衡化 -> 合成图 

	waitKey(0);
	return 0;
}
*/

// 获取图片的数据直方图，B G R 颜色直方图 , 任何数据的直方图
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	// 获取直方图， B G R 每个都单独分离出来（自己写个代码去分离）
	vector<Mat> bgr_s;
	split(src, bgr_s);

	// Y Cr Cb   HSV 

	// b 通道，但为什么不是 蓝色，而是一个灰度图 ?   
	// imshow("bgr_s", bgr_s[0]);

	// 计算获得直方图的数据
	// images 输入的图像
	// nimages 输入图像的个数 
	// channels 第几通道
	// mask 掩模
	// dims 需要统计的通道个数
	// histSize 等级的个数  0-255
	// ranges 数据的范围  0-255
	// uniform true 是否对得到的图片进行归一化处理
	// accumulate 在多个图像时，是否累计计算像素值的个数 false
	/*calcHist(const Mat* images, int nimages,
		const int* channels, InputArray mask,
		OutputArray hist, int dims, const int* histSize,
		const float** ranges, bool uniform = true, bool accumulate = false);*/

	int histSize = 256;
	float range[] = {0,256};
	const float * ranges = {range};
	Mat hist_b, hist_g, hist_r;
	calcHist(&bgr_s[0], 1, 0, Mat(), hist_b, 1, &histSize, &ranges, true ,false);
	calcHist(&bgr_s[1], 1, 0, Mat(), hist_g, 1, &histSize, &ranges, true, false);
	calcHist(&bgr_s[2], 1, 0, Mat(), hist_r, 1, &histSize, &ranges, true, false);

	// Mat 存的是像素值，不一定，存任意值
	// 画出来，hist_b 存的是什么？存的是各个灰度值的个数，hist_b 最小值 0 ，最大值 图片的宽*高

	// 归一化
	int hist_h = 400;
	int hist_w = 512; // 256*2
	int bin_w = hist_w / histSize;// 画笔的大小
	// alpha 最小值 
	/*normalize(InputArray src, InputOutputArray dst, double alpha = 1, double beta = 0,
		int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());*/
	// NORM_MINMAX 缩放到一定区域
	normalize(hist_b, hist_b, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_g, hist_g, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_r, hist_r, 0, hist_h, NORM_MINMAX, -1, Mat());

	// 画到一张图中
	Mat histImage(hist_h, hist_w, CV_8SC4, Scalar());
	for (int i = 1; i < histSize; i++){
		// 开始点，结束点   255 
		line(histImage, 
			Point((i - 1)*bin_w, hist_h - hist_b.at<float>(i - 1)), 
			Point(i*bin_w, hist_h - hist_b.at<float>(i)), 
			Scalar(255, 0, 0), bin_w, LINE_AA);

		line(histImage,
			Point((i - 1)*bin_w, hist_h - hist_g.at<float>(i - 1)),
			Point(i*bin_w, hist_h - hist_g.at<float>(i)),
			Scalar(0, 255, 0), bin_w, LINE_AA);

		line(histImage,
			Point((i - 1)*bin_w, hist_h - hist_r.at<float>(i - 1)),
			Point(i*bin_w, hist_h - hist_r.at<float>(i)),
			Scalar(0, 0, 255), bin_w, LINE_AA);
	}

	imshow("histImage", histImage);

	waitKey(0);
	return 0;
}