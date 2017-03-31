#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	/* 1. ͼ����������ʾ */
	Mat img1 = imread("E:\\Code\\OpenCV\\Picture\\9.jpg");
	namedWindow("1. ����������ʾ", WINDOW_AUTOSIZE);
	imshow("1. ����������ʾ", img1);
	
	// Mat imread(const string& filename, int flags=1);
	// flags : 0--�Ҷ�, 1--ת����ɫ�ٷ���, 2--��� ANYDEPTH, 4--��ɫ ANYCOLOR


	/* 2. ����ͼ���� */
	Mat logo = imread("..\\..\\picture\\sound.png");
	Mat img2 = imread("..\\..\\picture\\12.jpg");

	namedWindow("2. Logo");
	imshow("2. Logo", logo);

	namedWindow("3. ԭͼ");
	imshow("3. ԭͼ", img2);

	// ����һ��Mat����, ���ڴ��,ͼ���ROI
	Mat imageROI;
	// ����һ:
	// imageROI = img2(Rect(300, 200, logo.cols, logo.rows));
	// ������:
	imageROI = img2(Range(150, 150 + logo.rows), Range(400, 400 + logo.cols));

	// ��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logo, 0.5, 0., imageROI);

	// ��ʾ���
	namedWindow("4. ԭͼ + Logo");
	imshow("4. ԭͼ + Logo", img2);

	/* 3. ͼ������ */
	imwrite("Output_picture.png", img2);

	waitKey(0);

	return 0;
}