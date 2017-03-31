#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	载入图像 → 转成灰度图 → blur模糊降噪 → canny边缘检测
*/

int main()
{
	Mat srcImage = imread("..\\1.jpg");

	if (!srcImage.empty())
		imshow("原图", srcImage);

	Mat dstImage, edge, grayImage;  // 参数定义

	// 1. 创建于src同类型和大小的矩阵(dst)
	dstImage.create(srcImage.size(), srcImage.type());

	// 2. 将原图转为灰度图
	// OpenCV2:
	// cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	// OpenCV3:
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); 

	//imshow("gray Image", grayImage);

	// 3. 使用3x3内核降噪
	blur(grayImage, edge, Size(3, 3));

	//imshow("降噪", edge);

	// 4. 运行Canny算子
	Canny(edge, edge, 3, 9, 3);

	imshow("效果图", edge);


	waitKey(0);

	return 0;
}