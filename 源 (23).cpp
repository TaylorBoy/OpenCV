/*
	1. 寻找轮廓: findContours()
	   void findContours(InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point());
	   @param image : 二进制 8位 单通道图像
	   @param contours : 检测到的轮廓, 每个轮廓储存为一个向量vector<Point>
	   @param hierarchy : 可选输出向量, 包含拓扑信息
	   @param mode : 轮廓检索模式
		      RETR_EXTERNAL
			  RETR_LIST
			  RETR_CCOMP
			  RETR_TREE
	   @param method : 轮廓的近似办法
			  CHAIN_APPROX_NONE
			  CHAIN_APPROX_SIMPLE
			  CHAIN_APPROX_TC89_L1
			  CHAIN_APPROX_TC89_KCOS
	   @param offset : 每个轮廓点的可选偏移量

	2. 绘制轮廓: drawContours()
	   void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8,
	                     InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point());
	   @param contourIdx : 轮廓绘制的指示变量, 若为负值, 则绘制所有轮廓
	   @param color : 轮廓的颜色
	   @param thickness : 轮廓线条的粗细度
	   @param hierarchy : 可选的层次结构信息
	   @param maxLevel  : 轮廓绘制的最大等级
*/

#include <opencv2/opencv.hpp>	
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. 以二值模式载入原始图
	Mat srcImage = imread("..\\..\\picture\\19.jpg", 0);
	if (!srcImage.data) return -1;
	imshow("原始图", srcImage);

	// 2. 初始化结果图
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	// 3. srcImage取大于阈值119的那部分
	srcImage = srcImage > 119;
	imshow("取阈值后的原始图", srcImage);

	// 4. 定义轮廓和层次
	std::vector<std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	// 5. 查找轮廓
	
	// OpenCV2
	// findContours(srcImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	// OpenCV3
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	// 6. 遍历所有顶层的轮廓, 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		// OpenCV2
		// drawContours(dstImage, contours, index, color, CV_FILLED, 8, hierarchy);
		// OpenCV3
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}

	imshow("轮廓图", dstImage);

	waitKey(0);

	return 0;
}