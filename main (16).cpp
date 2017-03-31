#include <opencv2/opencv.hpp>
#include <String>
using namespace cv;
// ROI: region of interest 感兴趣的区域

int main()
{
	std::string mp4 = "F:\\傻孩子\\QT\\01\\QT0718\\1.基础.wmv";

	// 读取视频文件
	VideoCapture capture;	// capture: 捕获
	// VideoCapture capture("视频地址"); 视频地址为0则调用摄像头
	
	capture.open(0);

	while (1)
	{
		Mat frame;	// 定义一个Mat变量, 用于存储每一帧图像
		capture >> frame;
		imshow("001我和Python的第一次亲密接触.mp4", frame);
		if (27 == waitKey(30))	// 30ms
			break;
	}


	waitKey(0);

	return 0;
}