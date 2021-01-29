#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test.jpg");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src",src);

	// 1.Canny ��Ե���
	Mat gary;
	cvtColor(src, gary, COLOR_BGR2GRAY);
	Mat cannryImage;
	Canny(gary, cannryImage, 140, 250, 3);
	imshow("cannryImage", cannryImage);

	// 2. HoughLinesP
	// lines ��Ϣ�����������ֱ�ߣ�ÿ��ֱ��������
	// rho ���ؼ�϶ɨ��
	// theta ÿ�����ӵĽǶ� CV_PI / 180 = 1�� 
	// threshold ����ֵ 
	// minLineLength �ߵ���С���� 
	// maxLineGap �ߵ�֮��ļ�϶
	vector<Vec4f> plines;
	HoughLinesP(cannryImage, plines, 1, CV_PI / 360 , 170, 30, 15);
	for (int i = 0; i < plines.size(); i++)
	{
		Vec4f pline = plines[i];

		line(src, Point(pline[0], pline[1]), Point(pline[2], pline[3]), Scalar(0,0,255), 4, LINE_AA);
	}

	imshow("result",src);

	waitKey(0);
	return 0;
}


int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/ct.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);

	// 1.Canny ��Ե���
	Mat gary;
	cvtColor(src, gary, COLOR_BGR2GRAY);

	// minDist ����Բ֮�����С����
	// param1 ͶƱ�ۼӽ���������ٲ�����Բ
	// param2 ����ֵ 
	// minRadius ��С�İ뾶
	// maxRadius ���İ뾶
	vector<Vec3f> circles;
	HoughCircles(gary, circles, HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);

	for (int i = 0; i < circles.size(); i++)
	{
		Vec3f cc = circles[i];
		circle(src, Point(cc[0],cc[1]), cc[2], Scalar(0,0,255), 4 , LINE_AA);
	}

	imshow("result", src);

	waitKey(0);
	return 0;
}

// ͼƬ����ӳ�� QQ �ϴ��ռ���Ƭ����Ч�˾���������ͲЧ��
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);

	// map1 x�������ӳ�����
	// map2 y�������ӳ�����
	Mat map_x(src.size(), CV_32FC1);
	Mat map_y(src.size(), CV_32FC1);

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			// Mat ? 
			// 1080 * 720
			// (0,0)   ->    src.cols - col    (720,0)
			map_x.at<float>(row, col) = col;
			map_y.at<float>(row, col) = static_cast<float>(src.rows - row);
			// ��Ͳ
		}
	}

	Mat dst;
	remap(src,dst,map_x, map_y, 1);

	imshow("dst", dst);

	waitKey(0);
	return 0;
}
*/






