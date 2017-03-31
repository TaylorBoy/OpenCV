#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*-------------------- 全局变量 --------------------*/

// 原图, 原图的灰度图, 目标图
Mat g_srcImage, g_srcGrayImage, g_dstImage;

// Canny
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;    // Trackbar Value

// Sobel
Mat g_sobelGradient_x, g_sobelGradient_y;
Mat g_sobelAbsGradient_x, g_sobelAbsGradient_y;
int g_sobelKernelSize = 1;		// Trackbar Value

// Scharr
Mat g_scharrGradient_x, g_scharrGradient_y;
Mat g_scharrAbsGradient_x, g_scharrAbsGradient_y;

/*-------------------- 全局函数 --------------------*/

static void on_Canny(int, void *);
static void on_Sobel(int, void *);
void Scharr();  // 封装了Scharr边缘检测相关代码的函数

/*--------------------- 主函数 ---------------------*/

int main()
{
	system("color 2F");

	// Load image
	g_srcImage = imread("..\\..\\picture\\20.jpg");
	if (!g_srcImage.data) return -1;

	// Display src image
	imshow("Src Image", g_srcImage);

	// 创建与src同类型同大小的矩阵dst
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// 将原图转为灰度图
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);

	// 创建显示窗口
	namedWindow("Canny", WINDOW_AUTOSIZE);
	namedWindow("Sobel", WINDOW_AUTOSIZE);

	// 创建Trackbar
	createTrackbar("Value1", "Canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("Value2", "Sobel", &g_sobelKernelSize, 3, on_Sobel);

	// 调用回调函数
	on_Canny(0, 0);
	on_Sobel(0, 0);

	// Scharr 边缘检测
	Scharr();

	while (char(waitKey(9)) != 'q') {}

	return 0;
}


/*---------------------- on_Canny() ----------------------*/
static void on_Canny(int, void *)
{
	// 1. 3x3内核降噪
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));

	// 2. 运行Canny算子
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	// 3. 将g_dstImage所有元素置0
	g_dstImage = Scalar::all(0);

	// 4. 将Canny算出的边缘图作为掩码, 将原图src拷到目标图dst
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	// Display
	imshow("Canny", g_dstImage);
}

/*---------------------- on_Sobel() ----------------------*/
static void on_Sobel(int, void *)
{
	// 1. 求X方向梯度
	Sobel(g_srcImage, g_sobelGradient_x, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_x, g_sobelAbsGradient_x);

	// 2. 求Y方向梯度
	Sobel(g_srcImage, g_sobelGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_y, g_sobelAbsGradient_y);

	// 3. 合并梯度
	addWeighted(g_sobelAbsGradient_x, 0.5, g_sobelAbsGradient_y, 0.5, 0., g_dstImage);

	// Display
	imshow("Sobel", g_dstImage);
}

/*---------------------- Scharr() ----------------------*/
void Scharr()
{
	// 1. 求X方向梯度
	Scharr(g_srcImage, g_scharrGradient_x, CV_16S, 1, 0, 1, 0);
	convertScaleAbs(g_scharrGradient_x, g_scharrAbsGradient_x);  // 计算绝对值, 并将结果转成8位

	// 2. 求Y方向梯度
	Scharr(g_srcImage, g_scharrGradient_y, CV_16S, 0, 1, 1, 0);
	convertScaleAbs(g_scharrGradient_y, g_scharrAbsGradient_y);

	// 3. 合并梯度
	addWeighted(g_scharrAbsGradient_x, 0.5, g_scharrAbsGradient_y, 0.5, 0, g_dstImage);

	// Display
	imshow("Scharr", g_dstImage);
}