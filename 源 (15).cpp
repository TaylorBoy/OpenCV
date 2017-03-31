/*
	实现图像修补: inpaint()
	原型: void inpaint(InputArray src, InputArray inpaintMask, OutputArray dst, double inpaintRadius, int flags);
		  @param inpaintMask : 修复掩膜, 8位单通道图像, 其中非零像素表示需要修补的区域
		  @param inpaintRadius : 需要修补的每个点的圆形邻域, 为修复算法的参考半径
		  @param flags : 修补标识符
		                 INPAINT_NS    -- 基于Navier-Stokes方程的方法
						 INPAINT_TELEA -- Alexandru Telea方法
*/

#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>	
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "SRC IMAGE"
#define WINDOW_NAME2 "DST IMAGE"

Mat g_srcImage, inpaintMask;
Point previousPoint(-1, -1);  // 原来的点的坐标

static void on_Mouse(int event, int x, int y, int flags, void *)
{
	// 鼠标左键弹起
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	// 鼠标左键按下
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	// 鼠标移动
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		// 绘制白色线条
		line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, previousPoint, pt, Scalar(0, 0, 255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, g_srcImage);
	}
}

int main()
{
	// 载入原图并进行掩膜的初始化
	Mat srcImage = imread("..\\..\\picture\\9.jpg");
	if (!srcImage.data) return -1;

	g_srcImage = srcImage.clone();
	inpaintMask = Mat::zeros(g_srcImage.size(), CV_8U);

	imshow(WINDOW_NAME1, g_srcImage);

	// 设置鼠标回调消息
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);

	// 按键轮询
	while (true)
	{
		char c = (char)waitKey(0);

		if (27 == c)
			break;

		// 2 : 恢复原图
		if ('2' == c)
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow(WINDOW_NAME1, g_srcImage);
		}

		// 1/空格 : 图像修补
		if ('1' == c || ' ' == c)
		{
			Mat inpaintedImage;
			inpaint(g_srcImage, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}