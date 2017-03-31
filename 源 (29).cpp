/*
	霍夫圆变换: HuoghCircles()
	输入: 不需要二值图像.
	函数原型: void HoughCircles(InputArray image, OutputArray circles, int method, double dp, 
	               double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0);
			  @image   : 8位 灰度 单通道
	          @circles : 圆的输出矢量, 每个矢量包含3个浮点矢量(x,y,radius)
			  @method  : 检测方法, HOUGH_GADIENT (OpenCV2: CV_HOUGH_GRADIENT)
			  @dp      : 检测圆心的累加器图像的分辨率与输入图像之比的倒数, 允许创建一个比输入图像分辨率低的累加器
			  @minDist : 圆与圆心之间的最小距离, 即区分不同圆之间的最小距离
			  @param1  : method设置检测方法对应的参数(传递给Canny的高阈值, 低阈值为高阈值的一半)
			  @param2  : method对应参数, 表示在检测阶段圆心的累加器阈值. 影响圆的检测, 越小越能检测更多圆, 越大圆更接近完美圆形
			  @minRadius : 最小半径 
			  @maxRadius : 最大半径
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\24.jpg");
	Mat midImage, dstImage;

	srcImage.copyTo(dstImage);
	dstImage = Scalar::all(0);

	imshow("Src Image", srcImage);

	// 转灰度图 → 图像平滑
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	imshow("mid Image", midImage);

	// 进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 100, 10, 0, 10);

	cout << "Circles' size is : " << circles.size() << endl;

	// 依次绘制
	for (size_t i = 0; i < circles.size(); ++i)
	{
		// 圆心
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		// 半径
		int radius = cvRound(circles[i][2]);
		// 绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 20, 255), 3, 8, 0);
		//cout << "i = " << i << endl;
	}

	imshow("Dst Image", srcImage);

	waitKey(0);

	return 0;
}