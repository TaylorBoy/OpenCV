#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	����ͼ�� �� ת�ɻҶ�ͼ �� blurģ������ �� canny��Ե���
*/

int main()
{
	Mat srcImage = imread("..\\1.jpg");

	if (!srcImage.empty())
		imshow("ԭͼ", srcImage);

	Mat dstImage, edge, grayImage;  // ��������

	// 1. ������srcͬ���ͺʹ�С�ľ���(dst)
	dstImage.create(srcImage.size(), srcImage.type());

	// 2. ��ԭͼתΪ�Ҷ�ͼ
	// OpenCV2:
	// cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	// OpenCV3:
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); 

	//imshow("gray Image", grayImage);

	// 3. ʹ��3x3�ں˽���
	blur(grayImage, edge, Size(3, 3));

	//imshow("����", edge);

	// 4. ����Canny����
	Canny(edge, edge, 3, 9, 3);

	imshow("Ч��ͼ", edge);


	waitKey(0);

	return 0;
}