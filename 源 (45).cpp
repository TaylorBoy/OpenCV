#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/* 全局变量 */
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterValue = 3;		// 方框滤波参数
int g_nMeanBlurValue = 3;		// 均值滤波
int g_nGaussianBlurValue = 3;	// 高斯滤波

/* 全局函数 回调函数 */
static void on_BoxFilter(int, void *);
static void on_MeanBlur(int, void *);
static void on_GaussianBlur(int, void *);

/////////// 主函数 /////////////
int main()
{
	// 1. Load image
	g_srcImage = imread("..\\..\\picture\\1.jpeg");
	if (!g_srcImage.data) return -1;

	// 2. Copy to dst image
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	// 3. Dispaly src image
	imshow("srcImage", g_srcImage);

	//======================= <1>方框滤波 ============================
	// 4.1 Create Window
	namedWindow("<1>方框滤波", 1);
	// 4.2 Create Trackbar
	createTrackbar("Size: ", "<1>方框滤波", &g_nBoxFilterValue, 40, on_BoxFilter);
	// 4.3 Init call back function
	on_BoxFilter(g_nBoxFilterValue, 0);
	// Display.
	imshow("", g_dstImage1);

	//======================= <2>均值滤波 ============================
	// 4.1 Create Window
	namedWindow("<2>均值滤波", 1);
	// 4.2 Create Trackbar
	createTrackbar("Size: ", "<2>均值滤波", &g_nMeanBlurValue, 40, on_MeanBlur);
	// 4.3 Init call back function
	on_MeanBlur(g_nMeanBlurValue, 0);
	// Display.
	imshow("", g_dstImage2);

	//======================== <3>高斯滤波 ============================
	// 4.1 Create Window
	namedWindow("<3>高斯滤波", 1);
	// 4.2 Create Trackbar
	createTrackbar("Size: ", "<3>高斯滤波", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	// 4.3 Init call back function
	on_GaussianBlur(g_nGaussianBlurValue, 0);
	// Display.
	imshow("", g_dstImage3);

	///////////////////////////////////
	while (char(waitKey(10)) != 'q'){}

	return 0;
}

//------------------- on_BoxFilter() -------------------
// 方框滤波回调函数
static void on_BoxFilter(int, void *)
{
	// 方框滤波操作
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	// Dispaly
	imshow("<1>方框滤波", g_dstImage1);
}

//------------------- on_MeanBlur() -------------------
// 均值滤波回调函数
static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("<2>均值滤波", g_dstImage2);
}



//------------------- on_GaussianBlur() -------------------
// 高斯滤波回调函数
static void on_GaussianBlur(int, void *)
{
	// Size参数必须为奇数!
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
	imshow("<3>高斯滤波", g_dstImage3);
}