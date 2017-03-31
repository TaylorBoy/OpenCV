#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main()
{
	Mat srcImage = imread("..\\..\\picture\\19.jpg");
	if (!srcImage.data) return -1;
	imshow("Src Image", srcImage);

	// 定义变量
	MatND dstHist;  // 在cv中用CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };
	int size = 256;
	int channels = 0;

	// 计算图像的直方图
	calcHist(&srcImage, 1,  &channels, Mat(), dstHist, dims, &size, ranges);
	
	int scale = 1;

	Mat  dstImage(size * scale, size, CV_8U, Scalar(0));
	// 获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0); // 在cv中为cvGetMinMaxHistValue()

	// 绘制直方图
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; ++i)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}

	imshow("一维直方图", dstImage);

	waitKey(0);

	return  0;
}