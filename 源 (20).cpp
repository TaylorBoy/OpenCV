#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//-------------- 宏定义 ---------------
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "效果图窗口"

//------------- 全局变量 --------------
Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

//------------- 全局函数 --------------
static void on_ThreshChange(int, void *);

//-------------- 主函数 ---------------
int main()
{
	g_srcImage = imread("..\\..\\picture\\28.jpg");
	if (!g_srcImage.data) return -1;

	// 将原图转成灰度图并进行模糊降噪
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 创建原图窗口并显示
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	// 创建滚动条
	createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	while ((char)waitKey(8) != 'q'){}

	return 0;
}

//--------------- on_ThreshChange() ----------------
static void on_ThreshChange(int, void *)
{
	// 对图像进行二值化, 控制阈值
	threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);

	// 寻找轮廓
	findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 遍历每个轮廓, 寻找其凸包
	vector<vector<Point> > hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); ++i)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);
	}

	// 绘制出轮廓及其凸包
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); ++i)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}

