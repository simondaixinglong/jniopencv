#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	
	Mat src = (Mat_<double>(3, 3) << 50, 50, 50, 60, 60, 60, 70, 70, 70);
	// 求平均值怎么求？
	// (50+50+50+...+70)/9 = 60
	// 标准方差怎么求？
	// ((50-60)的平方 + (50-60)的平方 + (50-60)的平方 + ... + (70-60)的平方)/9 = 开根号(66.6666666667) = 8.1649658093 
	Mat mean, stddev;
	meanStdDev(src, mean, stddev);
	cout << mean << endl;
	cout << stddev << endl;

	cout << "========================================" << endl;


	// 协方差矩阵怎么求？
	Mat covar;
	calcCovarMatrix(src, covar, mean, COVAR_NORMAL | COVAR_ROWS);
	cout << mean << endl;
	cout << covar << endl;

	cout << "========================================" << endl;

	// 协方差矩阵再去求特征和特征向量
	src = (Mat_<double>(2, 2) << 100,100,100,100);
	Mat eigenvalues, eigenvectors;
	eigen(src, eigenvalues, eigenvectors);
	cout << eigenvalues << endl;
	cout << eigenvectors << endl;

	waitKey(0);
	getchar();
	return 0;
}
*/

// PCA 原理与应用 ，降维
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/example.png");

	int size = src.rows * src.cols;
	Mat data(size, 3, CV_8UC1);

	for (int i = 0; i < size; i++)
	{
		int row = i / src.cols;
		int col = i - row * src.cols;

		data.at<uchar>(i, 0) = src.at<Vec3b>(row, col)[0];
		data.at<uchar>(i, 1) = src.at<Vec3b>(row, col)[1];
		data.at<uchar>(i, 2) = src.at<Vec3b>(row, col)[2];
	}

	// 最终降维的数据
	PCA pca_analyze(data, Mat(), CV_PCA_DATA_AS_ROW);

	cout << pca_analyze.mean << endl;
	cout << pca_analyze.eigenvalues << endl;
	cout << pca_analyze.eigenvectors << endl;

	waitKey(0);
	getchar();
	return 0;
}

