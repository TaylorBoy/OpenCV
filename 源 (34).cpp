/*
	Sobel算子: 结合高斯平滑和微分求导, 用来计算图像的灰度函数和近似梯度
	函数 原型: void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3,
			              double scale=1, double delta=0, int borderType=BORDER_DEFAULT);
			   @ddept: 输出图像深度
			   @dx,dy: x/y方向上的差分阶数
			   @ksize: Sobel核的大小(1, 3, 5, 7)
			   @scale: 计算倒数时的可选因子
			   @delta: 结果载入dst之前的可选的delta值
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. 创建grad_x和grad_y矩阵
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//  2. Load image
	Mat src = imread("..\\..\\picture\\19.jpg");
	if (!src.data) return -1;
	imshow("Src Image", src);

	// 3.求X方向梯度
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X方向的Sobel", abs_grad_x);

	// 4. 求Y方向梯度
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向的Sobel", abs_grad_y);

	// 5. 合并梯度(近似)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	imshow("整体方向的Sobel", dst);

	waitKey(0);

	return (0);
}