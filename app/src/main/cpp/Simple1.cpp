#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
/*
int main()
{
	// ����ͼ 
	Mat src1  = imread("C:/Users/hcDarren/Desktop/android/test1.png");// 8U 255
	Mat src2 = imread("C:/Users/hcDarren/Desktop/android/test2.png");
	Mat src3 = imread("C:/Users/hcDarren/Desktop/android/test3.png");
	
	// RGB -> HSV , ���� HS ֱ��ͼ
	Mat hsv1, hsv2, hsv3;
	cvtColor(src1, hsv1, COLOR_RGB2HSV);
	cvtColor(src2, hsv2, COLOR_RGB2HSV);
	cvtColor(src3, hsv3, COLOR_RGB2HSV);

	// ����ֱ��ͼ
	int channels[] = {0,1};
	// ����
	MatND hist1, hist2, hist3;
	int h_bins = 50;
	int s_bins = 50;
	int hist_size[] = { h_bins, s_bins };
	float h_rangs[] = {0,180};// 0~360  
	float s_rangs[] = {0,255};
	const float* rangs[] = {h_rangs, s_rangs};
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, hist_size, rangs);
	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, hist_size, rangs);
	calcHist(&hsv3, 1, channels, Mat(), hist3, 2, hist_size, rangs);

	// ��һ�� 0 - 1
	normalize(hist1, hist1, 0, 1, NORM_MINMAX);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX);
	normalize(hist3, hist3, 0, 1, NORM_MINMAX);

	// ����ֱ��ͼ��method ����
	// compareHist( const SparseMat& H1, const SparseMat& H2, int method )
	double hist1_hist1 = compareHist(hist1, hist1, CV_COMP_BHATTACHARYYA); // ��õ�
	double hist1_hist2 = compareHist(hist1, hist2, CV_COMP_BHATTACHARYYA); // �ӽ��� 1 
	double hist1_hist3 = compareHist(hist1, hist3, CV_COMP_BHATTACHARYYA); // < 0.8

	cout << hist1_hist1 << endl;
	cout << hist1_hist2 << endl;
	cout << hist1_hist3 << endl;

	imshow("src1",src1);
	imshow("src2", src2);
	imshow("src3", src3);

	waitKey(0);
	return 0;
}


Mat hueImage;
int bins = 2;
int max_bins = 180;

void hist_backprojection(int, void*){
	// ֱ��ͼ����ͶӰ�� Mat 
	// calcBackProject
	calcBackProject(const Mat* images, int nimages,
	const int* channels, InputArray hist,
	OutputArray backProject, const float** ranges,
	double scale = 1, bool uniform = true);

	Mat hist;
	int hist_size = MAX(bins, 2);
	float hue_range[] = {0,180};
	const float* ranges[] = {hue_range};
	calcHist(&hueImage, 1, 0, Mat(), hist, 1, &hist_size, ranges);
	normalize(hist, hist , 0, 255 , NORM_MINMAX);

	// ����ͶӰ�Ĵ��� ����������ֵ��
	Mat backProject;
	calcBackProject(&hueImage, 1, 0, hist, backProject, ranges);

	imshow("BackProject", backProject);
}

int main()
{
	Mat src = imread("C:/Users/hcDarren/Desktop/android/hand.png");

	if (!src.data){
		cout << "��ȡ�ļ�����" << endl;
	}

	Mat hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	// ��ҵ�����콲
	vector<Mat> hsv_s;
	split(hsv, hsv_s);
	hueImage = hsv_s[0];

	// ����һ������
	namedWindow("BackProject");
	createTrackbar("backprojection", "BackProject", &bins, max_bins, hist_backprojection);
	hist_backprojection(bins, 0);

	imshow("src", src);

	waitKey(0);
	return 0;
}


int main()
{
	Mat src = imread("C:/Users/hcDarren/Desktop/android/qd.jpg");
	Mat tmpl = imread("C:/Users/hcDarren/Desktop/android/template.png");
	if (!src.data){
		cout << "��ȡ�ļ�����" << endl;
	}

	matchTemplate( InputArray image, InputArray templ,
                                 OutputArray result, int method, InputArray mask = noArray() );
	
	Mat result(src.rows - tmpl.rows + 1, src.cols - tmpl.cols + 1, CV_32FC1);
	// ģ��ƥ��   result  ƥ�����Ľ�� �� ��СӦ���Ƕ��� image.cols image.rows
	matchTemplate(src, tmpl, result, CV_TM_CCORR_NORMED);

	// �ӽ������ȥ����Сֵ��for , �ҵ��Ǹ���Сֵ�ĵ� Point�� for ȥ�� 
	CV_EXPORTS_W void minMaxLoc(InputArray src, CV_OUT double* minVal,
		CV_OUT double* maxVal = 0, CV_OUT Point* minLoc = 0,
		CV_OUT Point* maxLoc = 0, InputArray mask = noArray());
	// ����������minVal �ں�����ͨ��ָ�븳ֵ����������ֵ��
	double minVal = 0;
	double maxVal = 0;
	Point minLoc = 0;
	Point maxLoc = 0;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

	cout << maxVal << endl;

	// ������
	rectangle(src, maxLoc, Point(maxLoc.x + tmpl.cols, maxLoc.y + tmpl.rows), Scalar(0, 0, 255), 2, 8);

	imshow("src", src);

	waitKey(0);
	return 0;
}
*/

// ���죺ͼ��������ͼ��ķ�ˮ��
// ���ܣ����ۣ�����ȥ�������أ�jni ʹ��  6 
// ʵ����4-5 �ο�  ����Ƶ����֪ʶ

// linux ����ϵͳ  frameworker ���� 10�� ���ż���
// android frameworker Դ�� ndk �� binder ������ SurfaceView  �������̣��Ż�Framework �����е�Ӧ�ÿ�����  60W  QQ���� 25K  40W 
// �����Ż� 
// ����Ƶ

// Ӧ��û���ˣ����еĶ���ͨ�� 
