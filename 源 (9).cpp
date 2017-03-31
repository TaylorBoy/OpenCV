/*
	模板匹配: matchTemplate()
	void matchTemplate(InputArray image, InputArray temp1, OutputArray result, int method)
		@param image : 待搜索图像
		@param temp1 : 搜索模板, 尺寸不大于原图
		@param result : 比较结果的映射图
		@param method : 匹配方法
		       1. 平方差 method = TM_SQDIFF
			   2. 归一化平方差 method = TM_SQDIFF_NORMED
			   3. 相关匹配 method = TM_CCORR
			   4. 归一化相关匹配 method = TM_CCORR_NORMED
			   5. 系数匹配 method = TM_CCOEFF
			   6. 化相关系数匹配 method = TM_CCOEFF_NORMED
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "SRC IMAGE"
#define WINDOW_NAME2 "RESTULT"

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatChMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void *);

int main()
{
	g_srcImage = imread("..\\..\\picture\\12.jpg");
	g_templateImage = imread("..\\..\\picture\\template1.jpg");
	if (!g_srcImage.data || !g_templateImage.data) return -1;

	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, CV_WINDOW_AUTOSIZE);

	createTrackbar("方法", WINDOW_NAME1, &g_nMatChMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

	while ((char)waitKey() != 'q') {}

	return 0; 
}

void on_Matching(int, void *)
{
	Mat srcImage;
	g_srcImage.copyTo(srcImage);

	// 初始化用于结果输出的矩阵
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int retultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, retultImage_rows, CV_32FC1);

	// 进行匹配和标准化
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatChMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	// 通过函数minMaxLoc()定位最匹配的位置
	double minValue, maxValue;
	Point minLocation, maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	// 对于SQDIFF和SQDIFF_NORMED, 越小的值匹配结果更高, 而其余的方法, 数值越大匹配结果越好
	if (g_nMatChMethod == TM_SQDIFF || g_nMatChMethod == TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	// 绘制出矩形, 并显示结果
	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), 
		Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);
}
