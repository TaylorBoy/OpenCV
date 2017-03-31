#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	// 1. ����ͼƬ
	Mat srcImage = imread("..\\..\\picture\\12.jpg"), dstImage;
	if (srcImage.empty())
	{
		printf("����ͼƬ����!!\n");
		return -1;
	}

	// 2. ת����ɫ�ռ�
	// void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0);
	//               ����ͼ��        ���ͼ��         ��ɫ�ռ�  ͨ����(0=Դͨ����)
	cvtColor(srcImage, dstImage, COLOR_BGR2Lab);

	imshow("ԭͼ", srcImage);
	imshow("ת��Ч��ͼ1", dstImage);

	cvtColor(srcImage, dstImage, COLOR_HSV2BGR);
	imshow("ת��Ч��ͼ2", dstImage);

	waitKey(0);

	return 0;
}