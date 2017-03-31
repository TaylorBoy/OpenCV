#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImg = imread("..\\1.jpg");

	if (!srcImg.empty())
		imshow("[原图]", srcImg);

	// 进行均值滤波操作
	Mat dstImage;
	blur(srcImg, dstImage, Size(7, 7)); // blur: 使模糊不清,变模糊

	imshow("[效果图]", dstImage);

	waitKey(0);

	return 0;
}