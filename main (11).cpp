#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "绘图1"
#define WINDOW_NAME2 "绘图2"
#define WINDOW_WIDTH 600  // 定义窗口大小

/*--------------- 绘制椭圆 ---------------*/
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;   // 线宽
	int lineType = 8;    // 线型--8联通型

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),	// 中心
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),	// 大小位于矩形内
		angle,			// 旋转角度
		0,				// 扩展弧度 0-360
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType);
}

/*--------------- 绘制实心圆 -------------*/
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;		// 线粗 -- 实心
	int lineType = 8;

	circle(img,
		center,				 // 圆心
		WINDOW_WIDTH / 32,   // 半径
		Scalar(125, 56, 23),
		thickness,
		lineType);
}

/*--------------- 绘制凹多边形 ------------*/
void DrawPolygon(Mat img)
{

}

/*--------------- 绘制直线 ----------------*/
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;

	line(img,
		start,
		end,
		Scalar(128, 255, 33),
		thickness,
		lineType);
}

//////////////////////////////////////////////

int main()
{
	// 创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// 1.1 绘制4个椭圆
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	// 1.2 绘制圆心
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));


	// 显示绘制效果图
	imshow(WINDOW_NAME1, atomImage);

	waitKey(0);

	return 0;
}