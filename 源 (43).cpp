#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
	形态学(Morphology)滤波(1): 腐蚀 \ 膨胀
	void erode(
		InputArray src,
		OutputArray dst,
		InputArray kernel,  // 核, NULL时默认为3x3, 一般使用getStructuringElement()
		Point anchor=Point(-1,-1),
		int iterations=1;   // 迭代使用erode的次数
		int borderType=BORDER_DEFAULT,
		const Scalar& borderValue=morphologyDefaultBorderValue()
	);
	void dilate(
		InputArray src,
		OutputArray dst,
		InputArray kernel,
		Point anchor=Point(-1,-1),
		int iterations=1;
		int borderType=BORDER_CONSTANT,
		const Scalar& borderValue=morphologyDefaultBorderValue()
	);
*/

/* 全局变量 */
Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0;   // 0: erode, 1: dilate;
int g_nStructElementSize = 3;  // 内核矩阵尺寸

/* 全局函数 */
void Process();  // 膨胀和腐蚀的处理函数
static void on_TrackbarNumChange(int, void *);
static void on_ElementSizeChange(int, void *);

/*-------------------- main -------------------*/

int main()
{
	system("color 5E");
	g_srcImage = imread("..\\..\\picture\\1.jpeg");
	if (!g_srcImage.data) return -1;
	imshow("g_srcImage", g_srcImage);

	// 初次腐蚀并显示效果
	namedWindow("Result");

	// 获取自定义核
	Mat element = getStructuringElement(MORPH_RECT,  // 矩形: RECT, 交叉形: CROSS, 椭圆: ELLIPSE
		Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize));
	// 初次腐蚀
	erode(g_srcImage, g_dstImage, element);
	imshow("Result", g_dstImage);

	// 创建轨迹条
	createTrackbar("腐蚀/膨胀", "Result", &g_nTrackbarNumber, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "Result", &g_nStructElementSize, 21, on_ElementSizeChange);

	while (char(waitKey(10)) != 'q'){}

	cout << "Quit successfully !" << endl;

	return 0;
}

//----------------- 腐蚀 \ 膨胀 处理函数 -------------------
void Process()
{
	// 获取自定义核
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize));

	// 进行腐蚀或膨胀操作
	if (0 == g_nTrackbarNumber)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);

	// Display
	imshow("Result", g_dstImage);
}

//----------------- 腐蚀 \ 膨胀 切换 ------------------
static void on_TrackbarNumChange(int, void *)
{
	// 状态改变, 调用Process()函数即可
	if (0 == g_nTrackbarNumber)
		cout << "正在进行腐蚀操作..." << endl;
	else
		cout << "正在进行膨胀操作..." << endl;
	Process();
}

//----------------- 腐蚀 \ 膨胀 值改变 ------------------
static void on_ElementSizeChange(int, void *)
{
	// 状态改变, 调用Process()函数即可
	Process();
}

