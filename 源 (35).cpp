/*
	Canny算子:
	1) 消除噪声: 使用高斯平滑滤波器卷积降噪
	2) 计算梯度幅值和方向(0,45,90,135), 按照Sobel滤波器
	3) 非极大值抑制: 保留候选边缘
	4) 滞后阈值: 高阈值和低阈值, 高低阈值比推荐在2:1到3:1之间
	原型: void Canny(InputArray src, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false);
	      @apertureSize: 应用Sobel算子的孔径大小
		  @L2gradient  : 计算图像梯度幅值的标志
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>	
using namespace cv;

int main()
{
	// Load image
	Mat src = imread("..\\..\\picture\\1.jpg");
	Mat src1 = src.clone();

	// Display src image
	imshow("Src Image", src);

	//----------------------------------------------------------------------------------------------------------
	// 高阶Canny用法: 转成灰度图 → 降噪 → Canny → 等到边缘, 作为掩码, Copy原图到效果图上 → 得到彩色的边缘图
	//----------------------------------------------------------------------------------------------------------
	Mat dst, edge, gray;

	// 1. 创建于src同类型和大小的矩阵dst
	dst.create(src1.size(), src1.type());

	// 2. 将原图转换为灰度图
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	// 3. 降噪: 3x3
	blur(gray, edge, Size(3, 3));

	// 4. 运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	imshow("Canny edge", edge);

	// 5. 将dst内所有元素置0
	dst = Scalar::all(0);

	// 6. 使用Canny算子输出的边缘图edge作为掩码, 将原图copy到目标图dst中
	src1.copyTo(dst, edge);

	// Display
	imshow("Result", dst);

	waitKey(0);

	return 0;
}