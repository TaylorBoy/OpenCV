#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/* 回调函数 */
static void on_ContrastAndBirght(int, void *);

/* 全局变量 */
int g_nContrastValue;	// 对比度
int g_nBrightValue;		// 亮度
Mat g_srcImage, g_dstImage;

////////////////////////////////////////
int main()
{
	// 1. Read in image
	g_srcImage = imread("..\\..\\picture\\6.jpg");
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	// 2. 设定对比度和亮度初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	// 3. 创建效果窗口
	namedWindow("效果图");

	// 4. 创建轨迹条
	createTrackbar("对比度: ", "效果图", &g_nContrastValue, 300, on_ContrastAndBirght);
	createTrackbar("亮  度: ", "效果图", &g_nBrightValue, 200, on_ContrastAndBirght);

	// 5. 回调函数初始化
	on_ContrastAndBirght(g_nContrastValue, 0);
	on_ContrastAndBirght(g_nBrightValue, 0);

	//while (char(waitKey(100)) != 'q'){}
	waitKey(0);

	return 0;
}

/* 回调函数 */
static void on_ContrastAndBirght(int, void *)
{
	double time0 = saturate_cast<double>(getTickCount());
	// 运算: g_dstImage(i, j) = a * g_srcImage(i, j) + b
	//       输出 = 对比度a * 输入 + 亮度b
	for (int y = 0; y < g_srcImage.rows; ++y)
	{
		for (int x = 0; x < g_srcImage.cols; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = 
					saturate_cast<uchar>(g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y, x)[c] + g_nBrightValue);
			}
		}
	}

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "Run Time: " << time0 << "seconds" << endl;

	// 显示效果
	imshow("效果图", g_dstImage);
}