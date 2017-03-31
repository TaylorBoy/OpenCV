#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	/* 1. 图像的载入和显示 */
	Mat img1 = imread("E:\\Code\\OpenCV\\Picture\\9.jpg");
	namedWindow("1. 像的载入和显示", WINDOW_AUTOSIZE);
	imshow("1. 像的载入和显示", img1);
	
	// Mat imread(const string& filename, int flags=1);
	// flags : 0--灰度, 1--转到彩色再返回, 2--深度 ANYDEPTH, 4--颜色 ANYCOLOR


	/* 2. 初级图像混合 */
	Mat logo = imread("..\\..\\picture\\sound.png");
	Mat img2 = imread("..\\..\\picture\\12.jpg");

	namedWindow("2. Logo");
	imshow("2. Logo", logo);

	namedWindow("3. 原图");
	imshow("3. 原图", img2);

	// 定义一个Mat类型, 用于存放,图像的ROI
	Mat imageROI;
	// 方案一:
	// imageROI = img2(Rect(300, 200, logo.cols, logo.rows));
	// 方案二:
	imageROI = img2(Range(150, 150 + logo.rows), Range(400, 400 + logo.cols));

	// 将logo加到原图上
	addWeighted(imageROI, 0.5, logo, 0.5, 0., imageROI);

	// 显示结果
	namedWindow("4. 原图 + Logo");
	imshow("4. 原图 + Logo", img2);

	/* 3. 图像的输出 */
	imwrite("Output_picture.png", img2);

	waitKey(0);

	return 0;
}