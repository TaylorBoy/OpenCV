#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// void namedWindow(const string& winname, int flag = WINDWO_AUTOSIZE);
// 0@WINDOW_NORMAL  : 可改变大小
// 1@WINDOW_AUTOSIZE: 窗口大小自动适应, 不可改变窗口大小
// 8@WINDOW_OPENGL  : 支持OPENGL


int main()
{
	// 腐蚀

	Mat image = imread("..\\..\\picture\\1.jpeg");

	imshow("Src Image", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

	Mat out;
	erode(image, out, element);

	imshow("Result", out);

	waitKey(0);

	return 0;
}