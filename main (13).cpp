#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	// 1. 载入图片
	Mat srcImage = imread("..\\..\\picture\\12.jpg"), dstImage;
	if (srcImage.empty())
	{
		printf("载入图片出错!!\n");
		return -1;
	}

	// 2. 转换颜色空间
	// void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0);
	//               输入图像        输出图像         颜色空间  通道数(0=源通道数)
	cvtColor(srcImage, dstImage, COLOR_BGR2Lab);

	imshow("原图", srcImage);
	imshow("转换效果图1", dstImage);

	cvtColor(srcImage, dstImage, COLOR_HSV2BGR);
	imshow("转换效果图2", dstImage);

	waitKey(0);

	return 0;
}