#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // OpenCV 图像处理头文件
using namespace cv;

int main()
{
	// 载入原图
	Mat srcImage = imread("..\\1.jpg");
	// 显示原图
	if (!srcImage.empty())
		imshow("SRC_photo", srcImage);
	
	// 进行腐蚀操作
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat desImage;
	erode(srcImage, desImage, element);  // erode: 腐蚀

	// 显示效果图
	imshow("DES_photo", desImage);



	waitKey(0);

	return 0;

}