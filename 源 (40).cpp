#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
漫水填充(floodFill): 两个版本.
int floodFill(InputOutputArray image, Point seedPoint, Scalar newValue, Rect* rect=0, Scalar loDiff=Scalar(), Scalar upDiff=Scalar(), int flags=4);
int floodFill(InputOutputArray image, InputOutputArray mask, Point seedPoint, Scalar newValue, Rect* rect=0, Scalar loDiff=Scalar(), Scalar upDiff=Scalar(), int flags=4);

@image: 输入/输出1通道或3通道, 8位或浮点图像
@mask : 单通道, 3位, 长和宽都比输入图像image大两个像素点. [漫水填充不会填充掩模mask的非零像素区域]
@seedPoint: 漫水填充算法的起始点
@newValue : 重绘区域像素的新值, 像素点被染色的值
@loDiff	  : 当前观察像素值与其部件邻域像素值或者待加入该部件的种子像素之间的亮度或颜色之负差(lower brightness/color difference)的最大值
@upDiff   : 正差
*/

int main()
{
	// Load image
	Mat src = imread("..\\..\\picture\\1.jpeg");k
	imshow("Src Image", src);

	// Flood Fill
	Rect ccomp;
	floodFill(src, Point(0, 0), Scalar(0, 0, 0), &ccomp, Scalar(20, 20, 4), Scalar(10, 10, 10));

	// Display Result
	imshow("Result", src);

	waitKey(0);

	return 0;
}