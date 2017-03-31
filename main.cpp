#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	非线性滤波: 中值滤波 \ 双边滤波
	双边  原型: void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
	@d: 在过滤过程中每个像素邻域的直径, 若d为非正数, 则会根据sigmaSpace计算出
	@sigmaColor: 颜色空间滤波器的sigma值, 值越大, 该像素邻域内有越宽广的颜色会被混合, 产生较大的半相等颜色区域
	@sigmaSpace: 坐标空间中滤波器的sigma值, 值越大, 越远的像素会相互影响. d>0 则以d为准.
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");

	// Create Window
	namedWindow("Src Image");
	namedWindow("Result");

	// 双边滤波
	Mat out;
	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);

	// Display
	imshow("Src Image", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}