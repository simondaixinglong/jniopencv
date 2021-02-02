#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/example.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	// 高斯（模糊），计算高斯卷积核，卷积操作，考虑像素之间的差值（更好的保留图像的边缘）
	// 2-3 S
	Mat dst;
	bilateralFilter(src, dst, 0, 100, 10);

	// 时空复杂度问题


	imshow("dst",dst);

	waitKey(0);
	return 0;
}

int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/example.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	// 高斯（模糊），计算高斯卷积核，卷积操作，考虑像素之间的差值（更好的保留图像的边缘）
	// 2-3 S
	Mat dst;

	int size = 55;
	Mat kernel = Mat::ones(size, size, CV_32FC1) / (size*size);

	long st = getTickCount();
	filter2D(src,dst,src.depth(),kernel);
	long et = getTickCount();
	long time = (et - st) * 1000 / getTickFrequency();
	cout << "time" << time << endl;

	// 时间复杂度问题
	// 时间复杂度 = src.rows * src.cols * size * size
	// 小的作业：手写 filter2D 的源码

	imshow("dst", dst);

	waitKey(0);
	return 0;
}
*/

// 积分图的模糊算法 size 模糊的直径
void meanBlur(Mat & src, Mat &dst, int size){
	// size % 2 == 1
	// 把原来进行填充，方便运算
	Mat mat;
	int radius = size / 2;
	copyMakeBorder(src, mat, radius, radius, radius, radius, BORDER_DEFAULT);
	// 求积分图 (作业去手写积分图的源码) 
	Mat sum_mat, sqsum_mat;
	integral(mat, sum_mat, sqsum_mat, CV_32S, CV_32S);

	dst.create(src.size(), src.type());
	int imageH = src.rows;
	int imageW = src.cols;
	int area = size*size;
	// 求四个点，左上，左下，右上，右下
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	int lt = 0, lb = 0, rt = 0, rb = 0;
	int channels = src.channels();
	for (int row = 0; row < imageH; row++)
	{
		// 思考，x0，y0 , x1 , y1  sum_mat
		// 思考，row, col, dst
		y0 = row;
		y1 = y0 + size;
		for (int col = 0; col < imageW; col++)
		{
			x0 = col;
			x1 = x0 + size;
			for (int i = 0; i < channels; i++)
			{
				// 获取四个点的值
				lt = sum_mat.at<Vec3i>(y0, x0)[i];
				lb = sum_mat.at<Vec3i>(y1, x0)[i];
				rt = sum_mat.at<Vec3i>(y0, x1)[i];
				rb = sum_mat.at<Vec3i>(y1, x1)[i];

				// 区块的合
				int sum = rb - rt - lb + lt;
				dst.at<Vec3b>(row, col)[i] = sum / area;
			}
		}
	}
}

// 模糊（保留边缘）

int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/example.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	int size = 15;
	Mat dst;
	meanBlur(src, dst, size);

	imshow("dst",dst);
	waitKey(0);
	return 0;
}










