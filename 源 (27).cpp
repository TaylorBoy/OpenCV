/*
	重映射: 
	void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interprolation, int borderType=BORDER_CONSTANT, const Scalar& borderValue=Scalar());
	     @src : 单通道8位或者浮点型图像
		 @map1 : 1) 点(x,y)的第一个映射; 2) 表示CV_16C2, CV_32FC1, CV_32FC2类型的X值
		 @map2 : 1) map表示(1)时map2不代表任何值; 2) 表示CV_16UC1, CV32FC1类型的Y值(第二个值)
		 @interpolation : 插值方式
			INTER_NEAREST  -- 最近邻插值
			INTER_LINEAR   -- 双线性插值(默认)
			INTER_CUBLIC   -- 双三次样条插值(逾4x4像素邻域内的双三次插值)
			INTER_LANCZOS4 -- Lanczos插值(逾8x8像素邻域的Lanczos插值)
		@
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread("..\\..\\picture\\9.jpg");
	imshow("Src Image", srcImage);

	// 创建和原始图一样的效果图, x重映射图, y重映射图
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	// 遍历像素点, 改变map_x & map_y的值
	for (int j = 0; j < srcImage.rows; ++j)
	{
		for (int i = 0; i < srcImage.cols; ++i)
		{
			// 改变map_x&map_y值
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	// 进行重映射
	// OpenCV2
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	// OpenCV3
	//remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}