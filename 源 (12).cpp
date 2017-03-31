#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>	
using namespace cv;

int main()
{
	Mat srcImage = imread("..\\..\\picture\\16.jpg");
	if (!srcImage.data) return -1;
	imshow("Src Image", srcImage);

	// 参数准备
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	MatND redHist, greenHist, blueHist;

	// R: 进行直方图计算
	int channels_r[] = { 0 };
	calcHist(&srcImage, 1, channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);

	// G
	int channels_g[] = { 1 };
	calcHist(&srcImage, 1, channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);

	// B
	int channels_b[] = { 2 };
	calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);

	//--------------- 绘制出三色直方图 ----------------
	// 参数准备
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight = 255;
	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

	// 开始绘制
	for (int i = 0; i < bins; ++i)
	{
		// 参数准备
		float binValue_red = redHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		
		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);  // 要绘制的高度, intensity 强度
		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);

		// Red
		rectangle(histImage, Point(i * scale, histHeight - 1), Point((i + 1) * scale - 1, histHeight - intensity_red), Scalar(255, 0, 0));
		// Green
		rectangle(histImage, Point((i + bins) * scale, histHeight - 1), Point((i + bins + 1) * scale - 1, histHeight - intensity_green), Scalar(0, 255, 0));
		// Blue
		rectangle(histImage, Point((i + bins * 2) * scale, histHeight), Point(i + bins * 2 + 1, histHeight - intensity_blue), Scalar(0, 0, 255));
	}

	imshow("RGB Histogram", histImage);
	waitKey(0);

	return 0;
}
