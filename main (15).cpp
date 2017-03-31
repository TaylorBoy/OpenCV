#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
	// 1. 使用Mat()构造函数
	Mat m1(2, 2, CV_8UC3, Scalar(128, 128, 255));
	// CV_[位数][带符号与否][类型前缀]C[通道数]
	std::cout << "m1 -- Mat(): " << std::endl << m1 << std::endl;

	// 2. 通过C\C++构造函数
	// int sz[3] = { 2, 2, 2 };  // 超过二维
	// Mat m2(3, sz, CV_8UC, Scalar::all(0));

	// 4. 利用Create()
	// 注: 此方法只用于改变尺寸, 不能设初值
	m1.create(4, 4, CV_8UC(2));
	std::cout << "m2 -- create():" << std::endl << m1 << std::endl;

	// 5. Matlab式: zeros(), ones(), eye()
	Mat m3 = Mat::eye(4, 4, CV_64F);
	std::cout << "m3 -- eye(): " << std::endl << m3 << std::endl;

	Mat m4 = Mat::ones(2, 2, CV_32F);
	std::cout << "m4 -- ones(): " << std::endl << m4 << std::endl;

	Mat m5 = Mat::zeros(3, 3, CV_8UC1);
	std::cout << "m5 -- zeros(): " << std::endl << m5 << std::endl;

	// 6. 使用逗号 -- 小矩阵
	Mat m6 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	std::cout << "m6 -- 逗号: " << std::endl << m6 << std::endl;

	// 7. 复制: clone(), copyTo()
	Mat m7 = m6.row(1).clone();
	std::cout << "m7 -- clone(): " << std::endl << m7 << std::endl;

	m6.col(1).copyTo(m7);
	std::cout << "m7 -- copyTo(): " << std::endl << m7 << std::endl;



	waitKey(0);

	return 0;
}