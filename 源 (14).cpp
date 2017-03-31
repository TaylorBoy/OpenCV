#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main()
{
	Mat srcImage = imread("..\\..\\picture\\19.jpg");
	if (!srcImage.data) return -1;
	imshow("Src Image", srcImage);

	// �������
	MatND dstHist;  // ��cv����CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };
	int size = 256;
	int channels = 0;

	// ����ͼ���ֱ��ͼ
	calcHist(&srcImage, 1,  &channels, Mat(), dstHist, dims, &size, ranges);
	
	int scale = 1;

	Mat  dstImage(size * scale, size, CV_8U, Scalar(0));
	// ��ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0); // ��cv��ΪcvGetMinMaxHistValue()

	// ����ֱ��ͼ
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; ++i)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}

	imshow("һάֱ��ͼ", dstImage);

	waitKey(0);

	return  0;
}