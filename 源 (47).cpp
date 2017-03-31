#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	均值滤波: blur()
	原型: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT);
	@ksize: 核心大小
	@anchor: 锚点

	== 归一化后的方框滤波: boxFilter(src, dst, depth, Size(w, h), anchor, TRUE, border);
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
	//boxFilter(image, out, -1, Size(5, 5));
	blur(image, out, Size(8, 8));

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}