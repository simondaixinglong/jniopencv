#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);
	// Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	// Mat dst;
	// filter2D(src,dst,src.depth(),kernel);
	
	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);
	// 2. ת�Ҷȣ������ٶȣ�
	Mat gary;
	cvtColor(gaussian,gary,COLOR_BGR2GRAY);
	// 3. Sobel�ݶ�
	// delta �ڼ������Ļ������ټ��� delta
	// ddepth -1 ������ gary.depth() , ���� gary �ľ��ȸߵ�ֵ
	// x y , ���ݶ�һ�㲻����������Scharr ��ǿ
	Mat sobel_x,sobel_y;
	
	Sobel(gary, sobel_x, CV_32F, 1, 0, 3);
	Sobel(gary, sobel_y, CV_32F, 0, 1, 3);
	// �����ֵ
	convertScaleAbs(sobel_x, sobel_x);
	convertScaleAbs(sobel_y, sobel_y);
	
	Mat sobel;
	addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobel);

	imshow("sobel_x", sobel_x);
	imshow("sobel_y", sobel_y);
	imshow("sobel", sobel);
	imwrite("C:/Users/hcDarren/Desktop/android/card_n_sobel.png", sobel);

	waitKey(0);
	return 0;
}


int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);
	// Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	// Mat dst;
	// filter2D(src,dst,src.depth(),kernel);

	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);
	// 2. ת�Ҷȣ������ٶȣ�
	Mat gary;
	cvtColor(gaussian, gary, COLOR_BGR2GRAY);
	// 3. Sobel�ݶ�
	// delta �ڼ������Ļ������ټ��� delta
	// ddepth -1 ������ gary.depth() , ���� gary �ľ��ȸߵ�ֵ
	// x y , ���ݶ�һ�㲻����������Scharr ��ǿ
	Mat scharr_x, scharr_y;

	Scharr(gary, scharr_x, CV_16S, 1, 0, 3);
	Scharr(gary, scharr_y, CV_16S, 0, 1, 3);
	// �����ֵ
	convertScaleAbs(scharr_x, scharr_x);
	convertScaleAbs(scharr_y, scharr_y);

	Mat scharr(gary.size(),gary.type());
	// addWeighted(scharr_x, 1, scharr_y, 1, 0, scharr);
	int width = gary.cols;
	int height = gary.rows;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int x_p = scharr_x.at<uchar>(i,j);
			int y_p = scharr_y.at<uchar>(i, j);
			int p = x_p + y_p;
			scharr.at<uchar>(i, j) = saturate_cast<uchar>(p);
		}
	}

	imshow("sobel_x", scharr_x);
	imshow("sobel_y", scharr_y);
	imshow("sobel", scharr);
	imwrite("C:/Users/hcDarren/Desktop/android/card_n_scharr_2.png", scharr);

	waitKey(0);
	return 0;
}


int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);
	// Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	// Mat dst;
	// filter2D(src,dst,src.depth(),kernel);

	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);
	// 2. ת�Ҷȣ������ٶȣ�
	Mat gary;
	cvtColor(gaussian, gary, COLOR_BGR2GRAY);
	// 3. lpls
	Mat lpls;
	Laplacian(gary, lpls, CV_16S, 5);
	
	// 4. �����ֵ
	convertScaleAbs(lpls, lpls);

	// 5. ��ֵ��
	Mat thresh;
	threshold(lpls, thresh, 0 , 255 , THRESH_OTSU|THRESH_BINARY);
	// thresh 100 ���� 100 ȡ���ֵ 255 ��С�� 100 ȡ��Сֵ 0

	imshow("lpls", lpls);
	imwrite("C:/Users/hcDarren/Desktop/android/card_n_lpls.png", lpls);

	waitKey(0);
	return 0;
}


// Canny
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	// ԭ��
	// 1. ��˹ȥ����
	// 2. �Ҷ�ת��
	// 3. �����ݶ� Sobel/Scharr
	// 4. ������ź�����
	// 5. �ߵ���ֵ�����ֵͼ��0��255��threshold1 ����ֵ threshold2 ����ֵ ��
	// �� threshold1 - threshold2 ֮�䣬ȡ���ֵ 255������ȡ 0  ���� 1 ��2  1 ��3   30-60  30-90  50-100 50-150
	Mat dst;
	// L2gradient false L1gradient true
	Canny(src,dst, 50, 150, 3 , true);

	imshow("lpls", dst);
	imwrite("C:/Users/hcDarren/Desktop/android/card_n_canny_l1gradient.png", dst);

	waitKey(0);
	return 0;
}
*/

