/*
	分水岭:
		void watershed(InputArray image, InputOutputArray markers);
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME "PROC"

Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void *);

int main()
{
	// 1. 载入原图并显示, 初始化掩模和灰度图
	g_srcImage = imread("..\\..\\picture\\9.jpg");
	if (!g_srcImage.data) return -1;
	imshow(WINDOW_NAME, g_srcImage);

	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);

	// 2. 设置鼠标回调函数
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	// 3. 轮询处理
	while (true)
	{
		int c = waitKey(0);

		if (27 == char(c))
			break;

		// 按键为2, 恢复原图
		if ('2' == char(c))
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow(WINDOW_NAME, g_srcImage);
		}

		// 按键为1或空格, 图像处理
		if ('1' == char(c) || ' ' == char(c))
		{
			// 定义一些参数
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			// 寻找轮廓
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

			// 轮廓为空时
			if (contours.empty())
				continue;

			// 复制掩模
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			// 循环绘制轮廓
			for (int index = 0; index >= 0; index = hierarchy[index][0], ++compCount)
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);

			// compCount为零时的处理
			if (0 == compCount)
				continue;

			// 生成随机颜色
			vector<Vec3b> colorTab;
			for (int i = 0; i < compCount; ++i)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back( Vec3b((uchar)b, (uchar)g, (uchar)r) );
			}

			// 计算分水岭处理时间并输出
			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t处理时间 = %gms\n", dTime*1000. / getTickFrequency());

			// 将分水岭图像遍历存入watershedImage中
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i < maskImage.rows; ++i)
			{
				for (j = 0; j < maskImage.cols; ++j)
				{
					int index = maskImage.at<int>(i, j);
					if (-1 == index)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0 || index > compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			}

			// 混合灰度图和分水岭效果图并显示
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow(WINDOW_NAME, watershedImage);
		}
	}

	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void *)
{
	// 处理鼠标不在窗口的情况
	if (x < 0 || x > g_srcImage.cols || y < 0 || y > g_srcImage.rows)
		return;

	// 处理鼠标左键消息
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);

	// 鼠标左键按下并移动, 绘制白条
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);
	}
}
