/*
	仿射: warpAffine(), 一个线性变换 + 一个平移.(* 一个矩阵 + 一个向量)
	原型: void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize; int flags=INTER_LINEAR, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())
	@param M : 2x3的变换矩阵
	@param dsize : 输出图像的尺寸
	@param flags : 插值方式

	计算二维旋转变换矩阵: getRotationMatrix2D()
	原型: void getRatationMatrix2D(Point2f center, double angle, double scale);
	@param center : 旋转中心
	@param angle  : 旋转角度, 逆时针为正
	@param scale  : 缩放系数
*/

//------------------ 头文件 ---------------------
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//------------------ 宏定义 ---------------------
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "经过Warp后的图像"
#define WINDOW_NAME3 "经过Warp和Rotate后的图像"

//------------------ 主函数 ---------------------
int main()
{
	system("color 1A");

	// 1. 参数准备
	
	// 1.1 定义两组点, 代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	
	// 1.2 定义Mat变量
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	// 2. Load src image
	srcImage = imread("..\\..\\picture\\9.jpg");
	if (!srcImage.data) return -1;

	//    设置目标图像的大小和类型与原图像一直
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	// 3. 设置原图像和目标图像上的三组点以计算仿射变换
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0), static_cast<float>(srcImage.rows * 0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65), static_cast<float>(srcImage.rows * 0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15), static_cast<float>(srcImage.rows * 0.6));

	// 4. 求得仿射变换
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	// 5. 对源图像应用刚得到的仿射变换warpMat
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	// 6.  对图像进行缩放, 再旋转
	// 6.1 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -30.0;
	double scale = 0.8;
	// 6.2 求旋转矩阵
	rotMat = getRotationMatrix2D(center, angle, scale);
	// 6.3 旋转已缩放的图像
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

	// Display
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	waitKey(0);

	return 0;
}

//---------------------------------------