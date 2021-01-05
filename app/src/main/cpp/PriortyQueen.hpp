//
// Created by simonday on 2021/1/5.
//

#ifndef MY_APPLICATION_PRIORTYQUEEN_HPP
#define MY_APPLICATION_PRIORTYQUEEN_HPP

#include "../../../../../../../../Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/c++/v1/__bit_reference"

using namespace std;

template<class T>
class PriortyQueen {
	int count = 0;
	int index = 0;
	T *array = NULL;

private:

	void shiftUp(int index) {
		if (index > 1 && array[index] > array[index / 2]) {
			swap(array[index], array[index / 2]);
			shiftUp(index / 2);
		}
	}

	void shiftDown(int k) {
		while (k * 2 <= index) {//到底的情况
			//最大指向左孩子
			int max = 2 * k;
			//判断是否有右孩子,且右孩子大于左孩子
			if (max + 1 <= index && array[max + 1] > array[max]) {
				max += 1;
			}
			//最大的是自己
			if (array[k] > array[max]) {
				break;
			}
			//交换，最大的网上冒
			swap(array[k], array[max]);
			k = max;
		}
	}

public:
	PriortyQueen(int count) {
		this->count = count;
		array = new T[count];
	}

	bool isEmpty() {
		return index == 0;
	}

	void push(T t) {
		array[index + 1] = t;
		index++;
		shiftUp(index);
		for (int i = 0; i < index; ++i) {
			__android_log_print(ANDROID_LOG_ERROR, "TAG", "%d", array[i + 1]);
		}
		__android_log_print(ANDROID_LOG_ERROR, "TAG", "====================");
	}

	T pop() {
		T max = array[1];
		array[1] = array[index];
		index--;
		shiftDown(1);
		return max;
	}

};


#endif //MY_APPLICATION_PRIORTYQUEEN_HPP
