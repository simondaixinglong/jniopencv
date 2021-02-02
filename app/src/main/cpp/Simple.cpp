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

int getBlockSum(Mat &sum_mat, int x0, int y0, int x1, int y1, int ch){
	// ��ȡ�ĸ����ֵ
	int lt = sum_mat.at<Vec3i>(y0, x0)[ch];
	int lb = sum_mat.at<Vec3i>(y1, x0)[ch];
	int rt = sum_mat.at<Vec3i>(y0, x1)[ch];
	int rb = sum_mat.at<Vec3i>(y1, x1)[ch];

	// ����ĺ�
	int sum = rb - rt - lb + lt;
	return sum;
}

float getBlockSqSum(Mat &sqsum_mat, int x0, int y0, int x1, int y1, int ch){
	// ��ȡ�ĸ����ֵ
	float lt = sqsum_mat.at<Vec3f>(y0, x0)[ch];
	float lb = sqsum_mat.at<Vec3f>(y1, x0)[ch];
	float rt = sqsum_mat.at<Vec3f>(y0, x1)[ch];
	float rb = sqsum_mat.at<Vec3f>(y1, x1)[ch];

	// ����ĺ�
	float sqsum = rb - rt - lb + lt;
	return sqsum;
}


// ����ͼ��ģ���㷨 size ģ����ֱ��
void fatsBilateralBlur(Mat & src, Mat &dst, int size, int sigma){
	// size % 2 == 1
	// ��ԭ��������䣬��������
	Mat mat;
	int radius = size / 2;
	copyMakeBorder(src, mat, radius, radius, radius, radius, BORDER_DEFAULT);
	// �����ͼ (��ҵȥ��д����ͼ��Դ��) 
	Mat sum_mat, sqsum_mat;
	integral(mat, sum_mat, sqsum_mat, CV_32S, CV_32F);

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
				int sum = getBlockSum(sum_mat, x0, y0, x1, y1, i);
				float sqsum = getBlockSqSum(sqsum_mat, x0, y0, x1, y1, i);

				float diff_sq = (sqsum - (sum * sum) / area) / area;
				float k = diff_sq / (diff_sq + sigma);

				int pixels = src.at<Vec3b>(row, col)[i];
				pixels = (1 - k)*(sum / area) + k * pixels;

				dst.at<Vec3b>(row, col)[i] = pixels;
			}
		}
	}
}

void skinDetect(const Mat &src, Mat &skinMask){
	skinMask.create(src.size(), CV_8UC1);
	int rows = src.rows;
	int cols = src.cols;

	Mat ycrcb;
	cvtColor(src, ycrcb, COLOR_BGR2YCrCb);

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			Vec3b pixels = ycrcb.at<Vec3b>(row, col);
			uchar y = pixels[0];
			uchar cr = pixels[1];
			uchar cb = pixels[2];

			if (y>80 && 85<cb<135 && 135<cr<180){
				skinMask.at<uchar>(row, col) = 255;
			}
			else{
				skinMask.at<uchar>(row, col) = 0;
			}
		}
	}
}

void fuseSkin(const Mat &src, const  Mat &blur_mat, Mat &dst, const Mat &mask){
	// �ںϣ�
	dst.create(src.size(),src.type());
	GaussianBlur(mask, mask, Size(3, 3), 0.0);
	Mat mask_f;
	mask.convertTo(mask_f, CV_32F);
	normalize(mask_f, mask_f, 1.0, 0.0, NORM_MINMAX);

	int rows = src.rows;
	int cols = src.cols;
	int ch = src.channels();

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			// mask_f (1-k)
			/*
			uchar mask_pixels = mask.at<uchar>(row,col);
			// ����λ��
			if (mask_pixels == 255){
				dst.at<Vec3b>(row, col) = blur_mat.at<Vec3b>(row, col);
			}
			else{
				dst.at<Vec3b>(row, col) = src.at<Vec3b>(row, col);
			}
			*/

			// src ��ͨ��ָ��ȥ��ȡ�� ָ�� -> Vec3b -> ��ȡ
			uchar b1 = src.at<Vec3b>(row, col)[0];
			uchar g1 = src.at<Vec3b>(row, col)[1];
			uchar r1 = src.at<Vec3b>(row, col)[2];

			// blur_mat
			uchar b2 = blur_mat.at<Vec3b>(row, col)[0];
			uchar g2 = blur_mat.at<Vec3b>(row, col)[1];
			uchar r2 = blur_mat.at<Vec3b>(row, col)[2];

			// dst 254  1
			float k = mask_f.at<float>(row,col);

			dst.at<Vec3b>(row, col)[0] = b2*k + (1 - k)*b1;
			dst.at<Vec3b>(row, col)[1] = g2*k + (1 - k)*g1;
			dst.at<Vec3b>(row, col)[2] = r2*k + (1 - k)*r1;
		}
	}
}

// ģ����������Ե��
int main(){
	Mat src = imread("C:/Users/hcDarren/Desktop/android/test3.jpg");

	if (!src.data){
		printf("imread error!");
		return -1;
	}
	imshow("src", src);

	int size = 15;
	Mat dst;
	fatsBilateralBlur(src, dst, size, size*size);
	imshow("fatsBilateralBlur", dst);
	Mat skinMask;
	skinDetect(src, skinMask);
	imshow("skinDetect", skinMask);
	Mat fuseDst;
	fuseSkin(src, dst, fuseDst, skinMask);
	imshow("fuseSkin", fuseDst);

	// ��Ե������ (���п���)
	Mat cannyMask;
	Canny(src, cannyMask, 150, 300, 3, false);
	imshow("Canny", cannyMask);
	// & ����  0 ��255 
	bitwise_and(src, src, fuseDst, cannyMask);
	imshow("bitwise_and", fuseDst);
	// ��΢����һ�¶Աȶ�(����)
	add(fuseDst, Scalar(10, 10, 10), fuseDst);
	imshow("add", fuseDst);

	// bilateralFilter(src, dst, 0, 100, 15);
	// imshow("bilateralFilter", dst);
	
	waitKey(0);
	return 0;
}










