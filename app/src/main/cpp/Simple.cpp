#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/2_05.jpg");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src",src);

	// ���ȣ�ֱ��ͼ  BGR -> HSV
	Mat hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	vector<Mat> hsv_s;
	split(hsv, hsv_s);
	// ֱ������
	equalizeHist(hsv_s[2], hsv_s[2]);
	merge(hsv_s, hsv);

	Mat dst;
	cvtColor(hsv, dst, COLOR_HSV2BGR);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}


// ���п��������������
int main(){

	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);

	// �ݶȺͶ�ֵ��
	Mat binary;
	Canny(src, binary, 50, 150);
	imshow("binary", binary);

	findContours(InputOutputArray image, OutputArrayOfArrays contours,
		int mode, int method, Point offset = Point());

	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Mat contours_mat = Mat::zeros(src.size(), CV_8UC3);
	Rect card_rect;
	for (int i = 0; i < contours.size(); i++)
	{
		// ������
		Rect rect = boundingRect(contours[i]);
		if (rect.width > src.cols/2 && rect.height > src.rows/2){
			drawContours(contours_mat, contours, i, Scalar(0, 0, 255), 1);
			card_rect = rect;
			rectangle(contours_mat, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(255,255,255), 2);
			break;
		}
	}

	// �ü�

	imshow("contours_mat", contours_mat);

	waitKey(0);
	getchar();
}

// ͼ��أ�����β���
int main(){
	/// ����һ��ͼ��     
	const int r = 100;
	Mat src = Mat::zeros(Size(4 * r, 4 * r), CV_8UC1);

	/// ����һϵ�е㴴��һ������:
	vector<Point2f> vert(6);

	vert[0] = Point(1.5*r, 1.34*r);
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(1.5*r, 2.866*r);
	vert[3] = Point(2.5*r, 2.866*r);
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(2.5*r, 1.34*r);

	/// ��src�ڲ�����
	for (int j = 0; j < 6; j++)
	{
		line(src, vert[j], vert[(j + 1) % 6], Scalar(255), 3, 8);
	}

	// ��������
	vector < vector<Point>> contours;
	findContours(src, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// ���㵽�����ľ��� 
	Mat raw_dist(src.size(), CV_32FC1);
	for (int rows = 0; rows < src.rows; rows++)
	{
		for (int cols = 0; cols < src.cols; cols++)
		{
			raw_dist.at<float>(rows, cols) = pointPolygonTest(contours[0], Point2f(cols, rows), true);
		}
	}

	// �Ż�
	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
	for (int rows = 0; rows < src.rows; rows++)
	{
		for (int cols = 0; cols < src.cols; cols++)
		{
			// raw_dist.at<float>(rows, cols) = pointPolygonTest(contours[0], Point2f(rows, cols), true);
			if (raw_dist.at<float>(rows, cols) < 0 ){// ����
				drawing.at<Vec3b>(rows, cols)[0] = saturate_cast<int>((int)abs(raw_dist.at<float>(rows, cols)));
			}
			else if (raw_dist.at<float>(rows, cols) > 0){ // ����
				drawing.at<Vec3b>(rows, cols)[2] = saturate_cast<int>((int)(raw_dist.at<float>(rows, cols)));
			}
			else{// ��������
				drawing.at<Vec3b>(rows, cols)[0] = 255;
				drawing.at<Vec3b>(rows, cols)[1] = 255;
				drawing.at<Vec3b>(rows, cols)[2] = 255;
			}
		}
	}

	imshow("drawing", drawing);


	imshow("src", src);
	waitKey(0);
	getchar();
}
*/

int main(){
	
	Mat src = imread("C:/Users/hcDarren/Desktop/android/card_n.png");

	if (!src.data){
		printf("imread error!");
		return -1;
	}

	imshow("src", src);

	Mat markers;
	watershed(src, markers);

	imshow("markers", markers);

	waitKey(0);
	getchar();
}