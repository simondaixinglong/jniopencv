//
// Created by simonday on 2020/12/24.
//

#ifndef MY_APPLICATION_CARDORC_H
#define MY_APPLICATION_CARDORC_H

#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;

//会针对不同的场景，做不同的事情
namespace co1 {
	/**
	 * 找到银行区域
	 * @param mat 银行卡图片
	 * @param area 卡号区域
	 * @return 是否找到
	 */
	int find_card_area(const Mat &mat, Rect &area);

	/**
	 * 通过银行区域，截取银行卡区域
	 * @param mat
	 * @return
	 */
	int find_card_number_area(const Mat &mat, Rect &area);

	/**
	 * 找到所有的数字
	 * @param mat  截取的银行卡数字区域
	 * @param numbers  找到的所有数字
	 * @return
	 */
	int find_card_number(const Mat &mat, std::vector<Mat> numbers);

	/**
	 * 处理字符粘连
	 * @param mat
	 * @return
	 */
	int find_split_cols_pos(const Mat &mat);
}

/**
 * 备选方案
 */
namespace co2 {

}


#endif //MY_APPLICATION_CARDORC_H
