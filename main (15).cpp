#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
	// 1. ʹ��Mat()���캯��
	Mat m1(2, 2, CV_8UC3, Scalar(128, 128, 255));
	// CV_[λ��][���������][����ǰ׺]C[ͨ����]
	std::cout << "m1 -- Mat(): " << std::endl << m1 << std::endl;

	// 2. ͨ��C\C++���캯��
	// int sz[3] = { 2, 2, 2 };  // ������ά
	// Mat m2(3, sz, CV_8UC, Scalar::all(0));

	// 4. ����Create()
	// ע: �˷���ֻ���ڸı�ߴ�, �������ֵ
	m1.create(4, 4, CV_8UC(2));
	std::cout << "m2 -- create():" << std::endl << m1 << std::endl;

	// 5. Matlabʽ: zeros(), ones(), eye()
	Mat m3 = Mat::eye(4, 4, CV_64F);
	std::cout << "m3 -- eye(): " << std::endl << m3 << std::endl;

	Mat m4 = Mat::ones(2, 2, CV_32F);
	std::cout << "m4 -- ones(): " << std::endl << m4 << std::endl;

	Mat m5 = Mat::zeros(3, 3, CV_8UC1);
	std::cout << "m5 -- zeros(): " << std::endl << m5 << std::endl;

	// 6. ʹ�ö��� -- С����
	Mat m6 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	std::cout << "m6 -- ����: " << std::endl << m6 << std::endl;

	// 7. ����: clone(), copyTo()
	Mat m7 = m6.row(1).clone();
	std::cout << "m7 -- clone(): " << std::endl << m7 << std::endl;

	m6.col(1).copyTo(m7);
	std::cout << "m7 -- copyTo(): " << std::endl << m7 << std::endl;



	waitKey(0);

	return 0;
}