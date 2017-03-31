#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	高斯模糊: GaussianBlur()
	原型: void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
	@sigmaY = 0, 则 sigmaY = sigmaX. 表示高斯核函数在X/Y方向上的标准偏差
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");

	// 创建窗口
	namedWindow("SrcImage");
	namedWindow("Result");

	// 滤波
	Mat out;
	// boxFilter(image, out, -1, Size(5, 5));
	// blur(image, out, Size(7, 7));
	GaussianBlur(image, out, Size(6, 9), 0, 0);  // Size参数必须为奇数!
	/*OpenCV : (ksize.width > 0 && ksize.width % 2 == 1 && 
				ksize.height > 0 && ksize.height % 2 == 1) 
	in cv::createGaussianKernels */

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}