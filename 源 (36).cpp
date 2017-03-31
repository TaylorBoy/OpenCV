
/*
	<< 阈(yù)值化 >>

	1. 固定阈值操作: threshold()
	void threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);
	@thresh: 阈值具体值
	@maxval: 当type取CV_THRESH_BINARY / CV_THRESH_BINARY_INV阈值类型时的最大值
	@type  : 阈值类型(
		0, THRESH_BINARY,     dst(x, y) = maxval [src(x,y) > thresh] ORTHERWISE = 0
		1, THRESH_BINARY_INV, 相反 ↑
		2, THRESH_THUNC,      dst(x, y) = 0 [src(x,y) > thresh] OTHERWISE = src(x, y)
		3, THRESH_TOZERO,	  dst(x, y) = src(x, y) [src(x,y) > thresh] OTHERWISE = 0
		4, THRESH_TOZERO_INV, 相反 ↑
	)

	2. 自适应阈值操作: adaptiveThreshold()
	void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C);
	@adaptiveMethod: 指定自适应阈值算法(
		ADAPTIVE_THRESH_MEAN_C,    : T(x, y) = blockSize * blockSize邻域内(x,y)减去常数C的平均值 // mean: 平均
		ADAPTIVE_THRESH_GAUSSIAN_C : T(x, y) = blockSize * blockSize邻域内(x,y)减去C与高斯床交叉相关的加权总和.
		)  
	@thresholdType : 阈值类型, 必须取
		THRESH_BINARY      : dst(x, y) = maxValue [src(x,y) > T(x,y)] otherwise 0
		THRESH_BINARY_INV  : 相反 ↑
	@blockSize: 计算阈值大小的一个像素的邻域尺寸, 取3, 5, 7等
	@C: 减去平均或加权值后的常数, 一般为正数(可<=0)
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-------------- 宏 ---------------
#define WINDOW_NAME "阈值化"

//----------- 全局变量 ------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_dstImage, g_grayImage;

//----------- 全局函数 ------------
static void on_Threshold(int, void *);

int main()
{
	// Load Image
	g_srcImage = imread("..\\..\\picture\\18.jpg");
	if (!g_srcImage.data) return -1;

	// 存留一份原图的灰度图
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	// 创建窗口并显示原图
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow("原图", g_srcImage);

	// 创建滑动条
	createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	createTrackbar("参数", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);

	// 初始化回调函数
	on_Threshold(0, 0);

	while (char(waitKey(9)) != 'q'){}

	waitKey(0);

	return 0;
}

//----------- 回调函数 -----------
static void on_Threshold(int, void *)
{
	// 调用阈值函数
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	// Display
	imshow(WINDOW_NAME, g_dstImage);
}