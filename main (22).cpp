#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture(0);  // ������ͷ������Ƶ
	Mat edges;

	while (1)
	{
		// Load video
		Mat frame;
		capture >> frame;

		// Change for gray
		cvtColor(frame, edges, CV_BGR2GRAY);  // תBGR��ɫͼΪ�Ҷ�ͼ

		// 3x3�ں˽���(2x3+1=7)
		blur(edges, edges, Size(7, 7));  // ģ��

		// Canny
		Canny(edges, edges, 0, 30, 3);
		imshow("����ͷ", edges);
		if (waitKey(30) >= 0)
			break;  // Delay 30ms
	}

	return 0;
}