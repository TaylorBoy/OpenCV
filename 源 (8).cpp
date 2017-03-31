/*
	Harris角点检测: 
		直接基于灰度图像的角点提取算法.
	void cornerHarris(
		InputArray src,   // 8位单通道或者浮点型图像
		OutputArray dst,  // Harris结果
		int blockSize,    // 邻域的大小
		int ksize,        // Sobel算子孔径大小
		double k,         // Harris参数
		int borderType=BORDER_DEFAULT
	);
*/
#include <opencv2/opencv.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "程序窗口1"
#define WINDOW_NAME2 "程序窗口2"

Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30;   // 当前阈值
int max_thresh = 175;

void on_CornerHarris(int, void *);

int main()
{
	g_srcImage = imread("..\\..\\picture\\9.jpg");
	if (!g_srcImage.data) return -1;
	imshow("Src Image", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	// 存留一张灰度图
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("阈值", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);
	on_CornerHarris(0, 0);

	while ((char)waitKey(0) != 'q'){}

	return 0;
}

void on_CornerHarris(int, void *)
{
	Mat dstImage;		// 目标图
	Mat normImage;      // 归一化后的图
	Mat scaledImage;    // 线性变换后的8位无符号图

	// 初始化: 置零当前要显示的两幅图
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	// 进行角点检测
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1);
	convertScaleAbs(normImage, scaledImage);  // 将归一化后的图像线性变换成8位无符号整型

	// 进行绘制
	for (int j = 0; j < normImage.rows; ++j)
	{
		for (int i = 0; i < normImage.cols; ++i)
		{
			if ( (int)normImage.at<float>(j, i) > thresh + 80 )
			{
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2 , 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}

	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);
}


