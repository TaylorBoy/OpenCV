#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
	std::string jpg = "E:\\Code\\OpenCV\\test4\\Debug\\1.jpg";

	// Mat imread(const string &filename, intflags=1); 
	// 1: Ĭ��Ϊ1, תΪ��ɫ�ٷ���, BGR (blue, green, red)
	Mat img = imread(jpg);

	// ��������, Ĭ��ΪWINGDOW_AUTOSIZE, ���ܸı��С
	namedWindow("Picture", WINDOW_NORMAL);   // �ɸı��С

	if (!img.empty()){
		imshow("Picture", img);
	}

	// 0: תΪ��ɫ�ٷ���
	Mat img2 = imread(jpg, 0);
	imshow("Picture2", img2);

	// 2: ANYDEPTH, ��ɫ���
	// 4: ANYCOLOR
	// 2 | 4: ����ԭͼ
	Mat img3 = imread(jpg, 2 | 4);
	imshow("Picture3", img3);

	// flag > 0: ������ͨ����ɫͼ��
	Mat img4 = imread(jpg, 1999);
	imshow("Picture4", img4);

	waitKey(0);

	return 0;
}