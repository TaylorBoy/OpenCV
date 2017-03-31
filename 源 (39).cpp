/*
	<< 尺寸调整: resize() >>
	void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR);
	@fx: 水平轴缩放系数, 默认0时, fx=(double)dsize.width/src.cols
	@fy: 垂直轴缩放系数, 默认0时, fy=(double)dsize.height/src.rows
	@interpolation: 插入, 指定插值方式
		0 INTER_NEAREST -- 最近邻插值
		1 INTER_LINEAR  -- 线性插值(默认)
		2 INTER_CUBIC   -- 三次样条插值(超过4x4像素邻域内的双三次插值)
		3 INTER_AREA	-- 区域插值(利用像素区域关系的重采样插值)
		4 INTER_LANCZOS4   -- Lanczos插值(超过8x8像素邻域的Lanczos插值)
		※ 缩小: 推荐 CV_INTER_AREA
		※ 放大: 推荐 CV_INTER_LINEAR,  效率高, 速度快
				 不推荐 CV_INTER_CUBIC, 效率低, 速度慢

*/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\9.jpg");
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = srcImage; 

	// 进行尺寸调整
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0.0), (0.0), CV_INTER_AREA);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0.0), (0.0), CV_INTER_LINEAR);

	// Display
	imshow("Src Image", srcImage);
	imshow("dstImage 1", dstImage1);
	imshow("dstImage 2", dstImage2);

	waitKey(0);

	return 0;
}