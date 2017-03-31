#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#define WINDOW_NAME "[线性混合示例]"

/* [全局变量声明] */
const int g_nMaxAlphaValue = 100;	// Alpha 值的最大值
int g_nAlphaValueSlider;			// 滑动条的变量
double g_dAlphaValue;
double g_dBetaValue;

// 声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

/* [响应滑动条的回调函数] */
void on_Trackbar(int, void *)
{
	// 求当前alpha值相对于最大值的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = 1.0 - g_dAlphaValue;

	// 根据alpha和beta值进行线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	// 显示效果图
	imshow(WINDOW_NAME, g_dstImage);

	// 获取当前轨迹条的位置, track: 轨道, 踪迹
	// int getTrackbarPos(const string& trackbarname, const string& winname);
	printf("当前轨迹条位置: %d\n", getTrackbarPos("透明度 100", WINDOW_NAME));
}

int main(int argc, char** argv)
{
	// Loading image
	// 两张图的尺寸要相同
	g_srcImage1 = imread("F:\\壁纸\\background.jpg");
	g_srcImage2 = imread("F:\\壁纸\\benbenla-06c.jpg");
	if (!g_srcImage1.data | !g_srcImage2.data)
	{
		printf("Loading image error !\n");
		return -1;
	}

	// 设置滑动条初值
	g_nAlphaValueSlider = 70;

	// 创建窗体
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	// 在窗体中创建滑动条
	char TrackbarName[50];
	sprintf(TrackbarName, "透明度 %d", g_nMaxAlphaValue);

	// int createTrackbar(const string& trackbarName, const string& winName, int* value, int count, 
	// TrackbarCallback onChange = 0, void* userdata = 0)
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	// 结果在回调函数中显示
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);

	return 0;
}