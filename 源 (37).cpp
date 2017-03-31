#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

//------------------ 宏定义 -------------------
#define WINDOW_NAME "图像缩放"

//----------------- 全局变量 ------------------
Mat g_srcImage, g_dstImage, g_tmpImage;

//------------------ 主函数 -------------------
int main()
{
	// 1. 载入原图
	g_srcImage = imread("..\\..\\picture\\15.jpg");
	if (!g_srcImage.data) return -1;

	// 2. 创建显示窗口
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	// 3. 参数赋值
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key = 0;
	// 4. 轮询
	for (;;)
	{
		key = waitKey(1000);  // 获取按键值

		switch (key)
		{
			//=============== 退出 =================
			case 27:
				return 0;
				break;
			case 'q':
				return 0;
				break;

			//=============== 放大 =================
			case 'a':  // A按下, 调用pyrUp()
				pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
				printf("> [A], 执行pryUp(). X2\n");
				break; 

			case 'w': // W, resize()
				resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
				printf("> [W], 执行resize(). X2\n");
				break;

			//=============== 缩小 =================
			case 'd': // D按下, 调用pyrDown()
				pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
				printf("> [D], 执行pryDown(). /2\n");
				break;

			case 's': // S, resize()
				resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
				printf("> [S], 执行resize(). /2\n");
				break;

			default:
				continue;
				break;
		}

		// Display
		imshow(WINDOW_NAME, g_dstImage);

		// 将g_dstImage赋给g_tmpImage, 进行下一次循环
		g_tmpImage = g_dstImage;
	}

	return 0;
}
