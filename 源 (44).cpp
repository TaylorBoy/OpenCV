#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	非线性滤波: 中值滤波 \ 双边滤波
	中值  原型: void medianBlur(InputArray src, OutputArray dst, int ksize);
	@ksize: 孔径的线性尺寸, 必须取大于1的奇数(3, 5, 7, ...)
	基本思想: 用像素点邻域灰度值的中值来替代该像素点的灰度值. 时间 = 5 * 均值
*/

int main()
{
	Mat image = imread("..//..//picture//1.jpeg");
	if ( !image.data ) return -1;
	imshow("SrcImage", image);

	Mat out;
	
	// 中值滤波
	medianBlur(image, out, 5);

	imshow("Output", out);

	waitKey(0);

	return 0;
}