#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//------------- 宏定义 --------------
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "轮廓图"

//------------ 全局变量 -------------
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

//------------ 全局函数 -------------
static void on_ThreshChange(int, void *);

//------------ main函数 -------------
int main()
{
	system("color 1F");

	g_srcImage = imread("..\\..\\picture\\27.jpg");
	if (!g_srcImage.data) return -1;

	// 1. 转成灰度图并模糊降噪
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 2. 创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	// 3. 创建滚动条并初始化
	createTrackbar("Canny阈值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	while (char(waitKey(9)) != 'q'){}

	return 0;
}

//---------------- on_ThreshChange() -----------------
static void on_ThreshChange(int, void *)
{
	// 用Canny算子检测边缘
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	// 寻找轮廓
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 绘制轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); ++i)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}
