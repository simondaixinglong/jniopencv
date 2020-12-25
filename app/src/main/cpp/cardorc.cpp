//
// Created by simonday on 2020/12/24.
//

#include "cardorc.h"
#include <vector>
#include <android/log.h>

using namespace std;

int co1::find_card_area(const Mat &mat, Rect &area) {

	//首先降噪 就是高斯模糊
	Mat blur;
	GaussianBlur(mat, blur, Size(5, 5), BORDER_DEFAULT, BORDER_DEFAULT);


	//边缘梯度增强(保存图片) x,y增强 萨尔增强，索贝尔增强
	Mat gard_x, gard_y;
	Scharr(blur, gard_x, CV_32F, 1, 0);
	Scharr(blur, gard_y, CV_32F, 0, 1);

	Mat abs_gard_x, abs_gard_y;
	convertScaleAbs(gard_x, abs_gard_x);
	convertScaleAbs(gard_y, abs_gard_y);

	Mat gard;
	addWeighted(abs_gard_x, 0.5, abs_gard_y, 0.5, 0, gard);

	//写到内存
	/**
	 * Environment.getExternalStorageDirectory().getPath()，在compileSdkVersion: 29版本中，该方法标注了@Deprecated，
	 * 里面已经说明，对于Android Q的手机，应用程序不再可以直接访问此方法返回的路径，
	 * 所以会一直报错 open failed: ENOENT (No such file or directory)
	 */
//	bool a = imwrite("/storage/emulated/0/Android/data/com.simon.a/files/gard_n.jpg", gard);

	//二值化，筛选轮廓
	Mat gray;
	cvtColor(gard, gray, COLOR_BGRA2GRAY);
//	bool a = imwrite("/storage/emulated/0/Android/data/com.simon.a/files/gard_gray.jpg", gray);

	Mat binary;
	threshold(gray, binary, 40, 255, THRESH_BINARY);
//	bool a = imwrite("/storage/emulated/0/Android/data/com.simon.a/files/binary.jpg", binary);


	//稍微知道这个概念 card.io 很多图像过滤
	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		Rect rect = boundingRect(contours[i]);
		//过滤轮廓
		if (rect.width > mat.cols / 2 && rect.width != mat.cols && rect.height > mat.rows / 2) {
			//银行卡区域的宽高必须大于图片的一半
			area = rect;
//			__android_log_print(ANDROID_LOG_ERROR, "TAG", "find %d", area.width);
			break;
		}
	}
	blur.release();
	gard_x.release();
	gard_y.release();
	abs_gard_x.release();
	abs_gard_y.release();
	gard.release();
	gray.release();
	binary.release();
	return 0;
}

/**
 * 有两种方式
 * 1.精确截取，找到银联标志区域，通过比例精确截取（不过有的卡没有银联标志 70%）
 * 2.粗略截取，截取1/2到3/4处，宽度还是银行卡宽度(90%)
 * 3.找不到可以手动输入和修改
 * @param mat
 * @param area
 * @return
 */
int co1::find_card_number_area(const Mat &mat, Rect &area) {

	area.x = mat.cols / 12;
	area.y = mat.rows * 13 / 24;

	area.width = mat.cols * 5 / 6;
	area.height = mat.rows * 3 / 24;

	return 0;
}


int co1::find_card_number(const Mat &mat, std::vector<Mat> numbers) {

	//二值化，灰度处理
	Mat gray;
	cvtColor(mat, gray, COLOR_BGRA2GRAY);

	//THRESH_OTSU 自动适配合适的值,这一步很关键
	Mat binary;
	threshold(gray, binary, 90, 255, THRESH_BINARY);
//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/card_number_binary.jpg", binary);

	//降噪过滤
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(binary, binary, MORPH_CLOSE, kernel);

	//去掉干扰，填充成白色，找数字就是轮廓查询（card.io 只能识别16位）
	//查找的轮廓，现在图片是白底黑字，需要改成黑底白字
	Mat binary_not = binary.clone();
	bitwise_not(binary_not, binary_not);
//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/card_number_binary_n.jpg",binary_not);

	int mat_area = mat.rows * mat.cols;
	int min_h = mat.rows / 100000;
	vector<vector<Point>> contours;
	findContours(binary_not, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		Rect rect = boundingRect(contours[i]);
		//过滤轮廓 可以写多个条件
		//这里：面积小的过滤掉
		int react_area = rect.width * rect.height;
		if (react_area < mat_area / 2000000) {
			//小面积填充为白色背景
			drawContours(binary, contours, i, Scalar(255), -1);
		} else if (rect.height < min_h) {
			drawContours(binary, contours, i, Scalar(255), -1);
		}
	}

//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/card_number_binary_noise_n.jpg",binary);
	//截取每个数字轮廓binary(没有噪音)不行，binary_not（有噪音）
	binary.copyTo(binary_not);
	//没有噪音的 binary_not
	bitwise_not(binary_not, binary_not);

	//先把rect存起来 查找的时候有顺序错乱，还有可能出现粘连字符
	contours.clear();
	findContours(binary_not, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Rect rects[contours.size()];
	//白色图片，单颜色通道
	Mat contours_mat(binary.size(), CV_8UC1, Scalar(255));
	for (int i = 0; i < contours.size(); i++) {
		rects[i] = boundingRect(contours[i]);
		drawContours(contours_mat, contours, i, Scalar(0), 1);
	}

//	imwrite("/storage/emulated/0/Android/data/com.simon.a/files/card_number_binary_noise_n_single.jpg",
//			binary);


	//进行 冒泡 排序
	for (int i = 0; i < contours.size() - 1; ++i) {
		for (int j = 0; j < contours.size() - i - 1; ++j) {
			if (rects[j].x > rects[j + 1].x) {
				swap(rects[j], rects[j + 1]);
			}
		}
	}

	//裁剪, 彩色的mat信息量太大，不易
	numbers.clear();
	for (int i = 0; i < contours.size(); ++i) {
		Mat number(contours_mat, rects[i]);
		numbers.push_back(number);

		// 保存数字图片
//		char name[500];
//		sprintf(name, "/storage/emulated/0/Android/data/com.simon.a/files/card_number_%d.jpg", i);
//		imwrite(name, number);
	}

//	for (int i = 0; i < contours.size(); ++i) {
//		__android_log_print(ANDROID_LOG_ERROR, "TAG", "find %d", rects[i].x);
//	}

	gray.release();
	binary.release();
	binary_not.release();

	return 0;
}

int co1::find_split_cols_pos(const Mat &mat) {
	// 怎么处理粘连 ，对中心位置的左右 1/4 扫描，记录最少的黑色像素点的这一列的位置，
	// 就当做我们的字符串的粘连位置
	int mx = mat.cols / 2;
	int height = mat.rows;
	// 围绕中心左右扫描 1/4
	int start_x = mx - mx / 2;
	int end_x = mx + mx / 2;
	// 字符的粘连位置
	int cols_pos = mx;
	// 获取像素子 0 ，255
	int c = 0;
	// 最小的像素值
	int min_h_p = mat.rows;

	for (int col = start_x; col < end_x; ++col) {
		int total = 0;
		for (int row = 0; row < height; ++row) {
			// 获取像素点 opencv 基础第一堂课
			c = mat.at<Vec3b>(row, col)[0];// 单通道
			if (c == 0) {
				total++;
			}
		}
		if (total < min_h_p) {
			min_h_p = total;
			cols_pos = col;
		}
	}
	return cols_pos;
}




















