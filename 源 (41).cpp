#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// 开运算 = 腐蚀 → 膨胀, 消除小物体
// 数学表达式: dstImage = open(src, element) = dilate(erode(src, element));
// 闭运算 = 膨胀 → 腐蚀, 排除小型黑洞(黑色区域)
// 数学表达式: dstImage = close(src, element) =  erode(dilate(src, element));
// 形态学梯度 = 膨胀 - 腐蚀, 将团块的边缘突出, 保留边缘轮廓
// 数学表达式: dstImage = morph - grad(src, element) = dilate(src, element) - erode(src, element);
// 顶帽 = 原图 - 开运算, 分离比邻近点亮的斑块
// 数学表达式: dstImage = tophat(src, element) = src - open(src, element);
// 黑帽 = 闭运算 - 原图, 分离比邻近点暗的斑块, 完美轮廓

/*
void morphologyEx(
InputArray src,
OutputArray dst,
int op,
InputArray kernel,
Point anchor=Point(-1, -1),
int iterations=1;
int borderType=BORDER_DEFAULT,
const Scalar& borderValue=morphologyDefaultBorderValue()
);

@op: 形态学类型标志(OPEN, COLSE, GRADIENT, TOPHAT, BLACKHAT, ERODE, DILATE)
@kernel: 内核, 一般使用getStructuringElement()
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");
	imshow("Src Image", image);

	// 定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(6, 6));

	// 进行形态学操作, 更改操作类型即可
	morphologyEx(image, image, MORPH_BLACKHAT, element);

	// Display
	imshow("Result", image);

	waitKey(0);

	return 0;
}