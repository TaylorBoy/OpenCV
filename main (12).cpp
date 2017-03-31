#include <opencv2/opencv.hpp>
using namespace cv;

#define WINDOW_NAME "Window"

/* [全局函数声明] */
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

/* [全局变量声明] */
Rect g_rectangle;
bool g_bDrawingBox = false;  // 是否进行绘制
RNG  g_rng(123456);		// RNG() 初始化随机数状态的生成器

/*------------------- main -------------------*/
int main(int argc, char** argv)
{
	/* 1. 参数准备 */
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);  // scalar: 数量, 标量

	/* 2. 设置鼠标操作回调函数 */
	namedWindow(WINDOW_NAME);
	// void setMouseCallback(const string& winname, MouseCallback onMouse, void* userdata=0);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	/* 3. 主循环, 检测回调 */
	for (;;)
	{
		srcImage.copyTo(tempImage);  // 复制原图到临时变量
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);

		if (27 == waitKey(10))
			break;  // 按ESC退出
	}


	return 0;
}

/*---------------- 鼠标回调函数 --------------*/
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
		// 鼠标移动
	case EVENT_MOUSEMOVE:
		if (g_bDrawingBox)
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
		break;

		// 左键按下
	case EVENT_LBUTTONDOWN:
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);  // 记录起始点
		break;

		// 左键松开
	case EVENT_LBUTTONUP:
		g_bDrawingBox = false;
		// 对宽和高小于0的处理
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}

		// 调用绘制函数
		DrawRectangle(image, g_rectangle);

		break;

	default:
		break;
	}
}


/*---------------- 矩形绘制函数 --------------*/
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	// 随机颜色
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
