/*
	Scharr滤波器: 主要配合Sobel算子运算而存在的.
	void Scharr(
		InputArray src,  // 源图
		OutputArray dst, // 目标图
		int ddepth,      // 图像深度
		int dx,          // x方向上的差分阶数
		int dy,          // y方向上的差分阶数
		double scale=1,  // 缩放因子
		double delta=0,  // delta值
		int borderType=BORDER_DEFAULT // 边界模式
	)
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 0. 创建grad_x和grad_y矩阵
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	// 1. Load Image
	Mat src = imread("..\\..\\picture\\16.jpg");
	imshow("Src Image", src);

	// 2.1 求x方向梯度
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X Scharr", abs_grad_x);

	// 2.2 求y方向梯度
	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y Scharr", abs_grad_y);

	// 3. 合并梯度(近似)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	// Display
	imshow("Scharr", dst);

	waitKey(0);

	return 0;
}