#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*---------------- 全局变量 ----------------*/
Mat g_srcImage, g_dstImage, g_midImage;
std::vector<Vec4i> g_lines;  // 定义一个矢量结构用于存放线段
int g_nThreshold = 100;      // 变量接收的Trackbar位置参数

/*---------------- 全局函数 ----------------*/
static void on_HoughLines(int, void *);

/*---------------- main函数 ----------------*/
int main()
{
	system("color 3F");

	g_srcImage = imread("..\\..\\picture\\21.jpg");
	imshow("Src Image", g_srcImage);

	// 创建滚动条
	namedWindow("Result Image", WINDOW_AUTOSIZE);
	createTrackbar("Value", "Result Image", &g_nThreshold, 200, on_HoughLines);

	// 边缘检测, 转灰度图
	Canny(g_srcImage, g_midImage, 50, 200, 3);
	cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR);

	// 调用一次回调函数, 和一次HoughLinesP函数
	on_HoughLines(g_nThreshold, 0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);

	// Display
	imshow("Result Image", g_dstImage);

	waitKey(0);

	return 0;
}

/*---------------- 回调函数 ----------------*/
static void on_HoughLines(int, void *)
{
	// 局部变量
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();

	//dstImage = Scalar::all(0);

	// 调用HoughLinesP()
	std::vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nThreshold + 1, 50, 10);

	// 绘制线段
	for (size_t i = 0; i < mylines.size(); ++i)
	{
		Vec4i ln = mylines[i];
		line(dstImage, Point(ln[0], ln[1]), Point(ln[2], ln[3]), Scalar(23, 180, 55), 1, LINE_AA);
	}

	// Display
	imshow("Result Image", dstImage);
}