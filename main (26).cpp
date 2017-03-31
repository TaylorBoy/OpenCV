#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img = imread("1.jpg");
	imshow("Picture", img);
	waitKey(6000);
}