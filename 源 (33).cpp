/*
	拉普拉斯变换: Laplacian(), 主要利用Sobel算子
	函数原型: void Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT);
	          @ddepth: 目标图片的深度
			  @ksize : 用于计算二阶导的滤波器的空间尺寸, 大小必须为正奇数
			  @scale : 计算拉普拉斯的可选比例因子
			  @delta : 表示在结果存入目标dst之前的可选delta值
	Note: 让一幅图减去他的Laplacian算子可增强对比度.
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 0. 变量定义
	Mat src, src_gray, dst, abs_dst;

	// 1. Load Image
	src = imread("..\\..\\picture\\12.jpg");
	imshow("Src Image", src);

	// 2. 使用高斯滤波消除噪声
	GaussianBlur(src, src, Size(3, 3), 0, 0);

	// 3. 转换为灰度图
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	// 4. 使用Laplacian()
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0);

	// 5. 计算绝对值, 并将结果转换为8位
	convertScaleAbs(dst, abs_dst);

	// 6. 显示结果
	imshow("Laplacian", abs_dst);

	waitKey(0);

	return 0;
}