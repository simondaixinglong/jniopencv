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

	// 1.Canny 边缘检测
	Mat gary;
	cvtColor(src, gary, COLOR_BGR2GRAY);
	Mat cannryImage;
	Canny(gary, cannryImage, 140, 250, 3);
	imshow("cannryImage", cannryImage);

	// 2. HoughLinesP
	// lines 信息里面包含多条直线，每条直线两个点
	// rho 像素间隙扫描
	// theta 每次增加的角度 CV_PI / 180 = 1度 
	// threshold 低阈值 
	// minLineLength 线的最小长度 
	// maxLineGap 线点之间的间隙
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

	// 1.Canny 边缘检测
	Mat gary;
	cvtColor(src, gary, COLOR_BGR2GRAY);

	// minDist 两个圆之间的最小距离
	// param1 投票累加结果超过多少才能算圆
	// param2 低阈值 
	// minRadius 最小的半径
	// maxRadius 最大的半径
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

// 图片的重映射 QQ 上传空间照片，特效滤镜，镜像，万花筒效果
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);

	// map1 x方向的重映射规律
	// map2 y方向的重映射规律
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
			// 万花筒
		}
	}

	Mat dst;
	remap(src,dst,map_x, map_y, 1);

	imshow("dst", dst);

	waitKey(0);
	return 0;
}
*/






