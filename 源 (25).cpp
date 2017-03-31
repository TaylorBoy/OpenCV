#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME "PROCESS"

int update_map(int key);
static void ShowHelpText();

Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;

int main()
{
	system("color 2F");
	ShowHelpText();

	// 1. Load image
	g_srcImage = imread("..\\..\\picture\\15.jpg");
	if (!g_srcImage.data) return -1;
	imshow("Src Image", g_srcImage);

	// 2. 创建和原始图一样的效果图, x重映射图, y重映射图
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_map_x.create(g_srcImage.size(), CV_32FC1);
	g_map_y.create(g_srcImage.size(), CV_32FC1);

	// 3. 创建窗口并显示
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	// 4. 更新map_x和map_y的值, 进行重映射操作
	for (;;)
	{
		// Get Key Value
		int key = waitKey(0);

		// Check Quit?
		if (((key & 255)) == 27)
		{
			cout << "Exit successfully !";
			break;
		}

		// 更新map值, 进行remap重映射
		update_map(key);
		// OpenCV2
		//remap(g_srcImage, g_dstImage, g_map_x, g_map_y, CV_INTER_LINEAR, BORDER_DEFAULT, Scalar(0, 0, 0));
		// OpenCV3
		remap(g_srcImage, g_dstImage, g_map_x, g_map_y, INTER_LINEAR, BORDER_DEFAULT, Scalar(0, 0, 0));
		imshow(WINDOW_NAME, g_dstImage);
	}

	return 0;
}

/*------------------ update_map() ------------------*/
int update_map(int key)
{
	for (int j = 0; j < g_srcImage.rows; ++j)
	{
		for (int i = 0; i < g_srcImage.cols; ++i)
		{
			switch (key)
			{
				case '1':  // 第一种映射
					if (i > g_srcImage.cols*0.25 && i < g_srcImage.cols*0.75 &&
						j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75)
					{
						g_map_x.at<float>(j, i) = static_cast<float>(2 * (i - g_srcImage.cols*0.25) + 0.5);
						g_map_y.at<float>(j, i) = static_cast<float>(2 * (j - g_srcImage.rows*0.25) + 0.5);
					}
					else
					{
						g_map_x.at<float>(j, i) = 0;
						g_map_y.at<float>(j, i) = 0;
					}
					break;

				case '2':  // 第二种映射
					g_map_x.at<float>(j, i) = static_cast<float>(i);
					g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
					break;

				case '3':  // 第三种映射
					g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
					g_map_y.at<float>(j, i) = static_cast<float>(j);
					break;

				case '4':  // 第四种映射
					g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
					g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
					break;

				default:
					break;
			}
		}
	}
	return 1;
}

/*----------------- ShowHelpText() -----------------*/
static void ShowHelpText()
{
	printf("\n\n\n\tWelcome to OpenCV World ~\n\n");
	printf("\tVersion: "CV_VERSION);
	printf("\n\n\tPlease Entered: \n\n"
		"\t\t[ESC] to Quit!\n"
		"\t\t[ 1 ] to First remap\n"
		"\t\t[ 2 ] to Second remap\n"
		"\t\t[ 3 ] to Third remap\n"
		"\t\t[ 4 ] to Fouth remap\n");
}