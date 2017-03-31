/*
	直方图均匀化: equalizeHish()
	原型: void equalizeHish(InputArray src, OutputArray dst)

	步骤:
		1) 计算输入图像的直方图H
		2) 进行直方图归一化, 直方图的组距的和为255
		3) 计算直方图积分H'
		4) 以H'作为查询表进行图像变换
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("..\\..\\picture\\opencv3\\图7.41 未经均衡化的图像.jpg");
	if (!srcImage.data) return -1;

	// 2. 转为灰度图并显示
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("Src Image gray", srcImage);

	// 3. 进行直方图均匀化
	equalizeHist(srcImage, dstImage);

	// Display
	imshow("Dst Image", dstImage);

	waitKey(0);

	return 0;
}

