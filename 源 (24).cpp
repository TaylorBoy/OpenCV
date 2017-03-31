/*
	ֱ��ͼ���Ȼ�: equalizeHish()
	ԭ��: void equalizeHish(InputArray src, OutputArray dst)

	����:
		1) ��������ͼ���ֱ��ͼH
		2) ����ֱ��ͼ��һ��, ֱ��ͼ�����ĺ�Ϊ255
		3) ����ֱ��ͼ����H'
		4) ��H'��Ϊ��ѯ�����ͼ��任
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("..\\..\\picture\\opencv3\\ͼ7.41 δ�����⻯��ͼ��.jpg");
	if (!srcImage.data) return -1;

	// 2. תΪ�Ҷ�ͼ����ʾ
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("Src Image gray", srcImage);

	// 3. ����ֱ��ͼ���Ȼ�
	equalizeHist(srcImage, dstImage);

	// Display
	imshow("Dst Image", dstImage);

	waitKey(0);

	return 0;
}

