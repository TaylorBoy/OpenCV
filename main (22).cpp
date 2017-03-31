#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture(0);  // 从摄像头读入视频
	Mat edges;

	while (1)
	{
		// Load video
		Mat frame;
		capture >> frame;

		// Change for gray
		cvtColor(frame, edges, CV_BGR2GRAY);  // 转BGR彩色图为灰度图

		// 3x3内核降噪(2x3+1=7)
		blur(edges, edges, Size(7, 7));  // 模糊

		// Canny
		Canny(edges, edges, 0, 30, 3);
		imshow("摄像头", edges);
		if (waitKey(30) >= 0)
			break;  // Delay 30ms
	}

	return 0;
}