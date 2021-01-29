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

	// 80 �� ����Ƶ ��opencv ��� ������Ƶ�������ۣ� 13 �� ��5 ������֪ʶ��5 ��ʵս
	imshow("src",src);

	// �����Ż���android �ײ�Դ�� NDK  binder���û��ռ䣬�ں˿ռ䣩NDK 
	// Histogram  ֱ��ͼ
	Mat dst;
	equalizeHist(gary, dst);
	imshow("dst", dst);

	// ���飺2_05 ��ɫ�ģ��ֳ�����Y ��ȡ���������⻯ -> �ϳ�ͼ 

	waitKey(0);
	return 0;
}
*/

// ��ȡͼƬ������ֱ��ͼ��B G R ��ɫֱ��ͼ , �κ����ݵ�ֱ��ͼ
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	// ��ȡֱ��ͼ�� B G R ÿ������������������Լ�д������ȥ���룩
	vector<Mat> bgr_s;
	split(src, bgr_s);

	// Y Cr Cb   HSV 

	// b ͨ������Ϊʲô���� ��ɫ������һ���Ҷ�ͼ ?   
	// imshow("bgr_s", bgr_s[0]);

	// ������ֱ��ͼ������
	// images �����ͼ��
	// nimages ����ͼ��ĸ��� 
	// channels �ڼ�ͨ��
	// mask ��ģ
	// dims ��Ҫͳ�Ƶ�ͨ������
	// histSize �ȼ��ĸ���  0-255
	// ranges ���ݵķ�Χ  0-255
	// uniform true �Ƿ�Եõ���ͼƬ���й�һ������
	// accumulate �ڶ��ͼ��ʱ���Ƿ��ۼƼ�������ֵ�ĸ��� false
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

	// Mat ���������ֵ����һ����������ֵ
	// ��������hist_b �����ʲô������Ǹ����Ҷ�ֵ�ĸ�����hist_b ��Сֵ 0 �����ֵ ͼƬ�Ŀ�*��

	// ��һ��
	int hist_h = 400;
	int hist_w = 512; // 256*2
	int bin_w = hist_w / histSize;// ���ʵĴ�С
	// alpha ��Сֵ 
	/*normalize(InputArray src, InputOutputArray dst, double alpha = 1, double beta = 0,
		int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());*/
	// NORM_MINMAX ���ŵ�һ������
	normalize(hist_b, hist_b, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_g, hist_g, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_r, hist_r, 0, hist_h, NORM_MINMAX, -1, Mat());

	// ����һ��ͼ��
	Mat histImage(hist_h, hist_w, CV_8SC4, Scalar());
	for (int i = 1; i < histSize; i++){
		// ��ʼ�㣬������   255 
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