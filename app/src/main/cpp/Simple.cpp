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

	// ��˹��ģ�����������˹����ˣ������������������֮��Ĳ�ֵ�����õı���ͼ��ı�Ե��
	// 2-3 S
	Mat dst;
	bilateralFilter(src, dst, 0, 100, 10);

	// ʱ�ո��Ӷ�����


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

	// ��˹��ģ�����������˹����ˣ������������������֮��Ĳ�ֵ�����õı���ͼ��ı�Ե��
	// 2-3 S
	Mat dst;

	int size = 55;
	Mat kernel = Mat::ones(size, size, CV_32FC1) / (size*size);

	long st = getTickCount();
	filter2D(src,dst,src.depth(),kernel);
	long et = getTickCount();
	long time = (et - st) * 1000 / getTickFrequency();
	cout << "time" << time << endl;

	// ʱ�临�Ӷ�����
	// ʱ�临�Ӷ� = src.rows * src.cols * size * size
	// С����ҵ����д filter2D ��Դ��

	imshow("dst", dst);

	waitKey(0);
	return 0;
}
*/

// ����ͼ��ģ���㷨 size ģ����ֱ��
void meanBlur(Mat & src, Mat &dst, int size){
	// size % 2 == 1
	// ��ԭ��������䣬��������
	Mat mat;
	int radius = size / 2;
	copyMakeBorder(src, mat, radius, radius, radius, radius, BORDER_DEFAULT);
	// �����ͼ (��ҵȥ��д����ͼ��Դ��) 
	Mat sum_mat, sqsum_mat;
	integral(mat, sum_mat, sqsum_mat, CV_32S, CV_32S);

	dst.create(src.size(), src.type());
	int imageH = src.rows;
	int imageW = src.cols;
	int area = size*size;
	// ���ĸ��㣬���ϣ����£����ϣ�����
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	int lt = 0, lb = 0, rt = 0, rb = 0;
	int channels = src.channels();
	for (int row = 0; row < imageH; row++)
	{
		// ˼����x0��y0 , x1 , y1  sum_mat
		// ˼����row, col, dst
		y0 = row;
		y1 = y0 + size;
		for (int col = 0; col < imageW; col++)
		{
			x0 = col;
			x1 = x0 + size;
			for (int i = 0; i < channels; i++)
			{
				// ��ȡ�ĸ����ֵ
				lt = sum_mat.at<Vec3i>(y0, x0)[i];
				lb = sum_mat.at<Vec3i>(y1, x0)[i];
				rt = sum_mat.at<Vec3i>(y0, x1)[i];
				rb = sum_mat.at<Vec3i>(y1, x1)[i];

				// ����ĺ�
				int sum = rb - rt - lb + lt;
				dst.at<Vec3b>(row, col)[i] = sum / area;
			}
		}
	}
}

// ģ����������Ե��

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










