#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
	std::string jpg = "E:\\Code\\OpenCV\\test4\\Debug\\1.jpg";

	// Mat imread(const string &filename, intflags=1); 
	// 1: 默认为1, 转为彩色再返回, BGR (blue, green, red)
	Mat img = imread(jpg);

	// 创建窗口, 默认为WINGDOW_AUTOSIZE, 不能改变大小
	namedWindow("Picture", WINDOW_NORMAL);   // 可改变大小

	if (!img.empty()){
		imshow("Picture", img);
	}

	// 0: 转为灰色再返回
	Mat img2 = imread(jpg, 0);
	imshow("Picture2", img2);

	// 2: ANYDEPTH, 颜色深度
	// 4: ANYCOLOR
	// 2 | 4: 无损原图
	Mat img3 = imread(jpg, 2 | 4);
	imshow("Picture3", img3);

	// flag > 0: 载入三通道彩色图像
	Mat img4 = imread(jpg, 1999);
	imshow("Picture4", img4);

	waitKey(0);

	return 0;
}