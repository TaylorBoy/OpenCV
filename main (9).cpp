#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv)
{
	// 1. Read images
	Mat srcImage = imread("..\\..\\Picture\\opencv3\\ͼ3.3 dota2 ԭ��ͼ����.jpg");
	Mat logoImage = imread("..\\..\\Picture\\10.jpg");
	if (srcImage.empty()) return -1;
	if (logoImage.empty()) return -2;

	// 2. Define a Mat class, and set the ROI
	Mat imageROI = srcImage(Rect(10, 30, logoImage.cols, logoImage.rows));

	// 3. Loading Mask (It must be a gray image)
	Mat mask = imread("..\\..\\Picture\\10.jpg", 0);

	imshow("Logo mask", mask);  // �Ҷ�ͼ

	// 4. Copy mask to ROI
	logoImage.copyTo(imageROI, mask);   

	// 5. Display the result
	namedWindow("����ROIʵ��ͼ�����");
	imshow("����ROIʵ��ͼ�����", srcImage);

	waitKey(0);

	return 0;
}