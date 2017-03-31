/*
	霍夫变换 Huogh Transform:
	HoughLines() : 标准霍夫变换, StandardHough Transform, SHT.
	               多尺度霍夫变换, Multi-ScaleHough Transform, MSHT.
	HoughLinesP(): 累计概率霍夫变换, ProgressiveProbabilistic Hough Transform, PPHT

	输入: 霍夫线变换的直接输入只能是边缘二值图像.

	标准霍夫原型: void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0);
	      @image : 8位单通道二进制图像.
		  @lines : 每条线有两个矢量(ρ, θ)(极坐标)
		  @rho   : 以像素为单位的距离精度(ρ)
		  @theta : 以弧度为单位的角度精度
		  @threshold: 累加平面的阈值参数, 大于阈值的线才能为结果.
		  @srn : 对于多尺度霍夫变换, 为rho的除数距离(粗略的累加进步尺寸为rho, 精确为rho/srn)
		  @stn : 对于多尺度霍夫变换, 为theta的除数距离. 若srn=stn=0, 则使用经典霍夫变换, 否则srn和stn为正数.

	概率霍夫原型: void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0);
	      @lines : 存储检测到的线, 每条有4个矢量, (x_1,y_1)和(x_2,y_2)为线段的结束点.
		  @minLineLength : 最低线段的长度
		  @maxLineGap    : 允许将同一行点与点之间连接起来的最大距离
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

#if (1)
int main()
{
	Mat srcImage = imread("..\\..\\picture\\22.jpg");
	Mat midImage, dstImage;

	// 边缘检测, 转灰度图
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	// 进行霍夫线变换
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	
	// 绘制线段
	for (size_t i = 0; i < lines.size(); ++i)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		// OpenCV2
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}

	// 显示原图 \ 边缘检测图 \ 效果图
	imshow("Src Image", srcImage);
	imshow("Canny", midImage);
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}
#endif

// HoughLinesP() 累计概率霍夫变换
#if (0)
int main()
{
	Mat srcImage = imread("..\\..\\picture\\21.jpg");
	Mat midImage, dstImage;

	// 进行边缘检测, 转为灰度图
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	// 进行霍夫线变换
	vector<Vec4i> lines;   // 定义一个lines存放得到的线段矢量集合
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	// 依次在途中会出每条线段
	for (size_t i = 0; i < lines.size(); ++i)
	{
		Vec4i l = lines[i];

		// OpenCV2
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 15, 153), 1, CV_AA);

		// OpenCV3
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);		
	}

	// 显示原图 \ 边缘检测图 \ 效果图
	imshow("Src Image", srcImage);
	imshow("Canny", midImage);
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}

#endif
