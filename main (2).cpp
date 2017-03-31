#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	方框滤波: boxFilter()
	原型: void boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), bool normalize=true, int borderType=BORDER_DEFAULT);
	@ddepth: 输入图像深度, -1表示使用原图深度src.depth()
	@ksize: 内核大小, Size(width, height)
	@anchor: 锚点--平滑点, 默认值表示核的中心
	@normalize: 是否被其区域归一化, 

	均值滤波 = 归一化的 方框滤波.
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
	boxFilter(image, out, -1, Size(6, 6));

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}