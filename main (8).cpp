#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*---------------------------*/
bool ROI_AddImage();
bool ROI_LinearBlending();
bool LinearBlending();
/*---------------------------*/

int main()
{
	system("color 5E");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	{
		cout << "Pragram run succeed !" << endl;
	}

	waitKey(0);

	return 0;
}

/*------------ ROI_LinearBlending() ------------*/
// 指定区域 线型混合, 自定义区域线型混合 cv::addWeighted()
// void addWeighted(InputArray src1, double a1, InputArray src2, double a2, double a3, OutputArray dst, int dtype=-1);
//                  img              权重1      img2             权重2      权重 (+总)  输出            可选深度,-1为两输出相同

bool ROI_LinearBlending()
{
	// 1. Load image
	Mat srcImage = imread("..\\..\\picture\\14.jpg");
	Mat logoImage = imread("..\\..\\picture\\15.jpg");
	if (!srcImage.data | !logoImage.data)
		return false;

	// 2. 定义一个Mat类型, 并设定ROI区域
	Mat imageROI;
	// 法一: Rect() 矩形选区
	imageROI = srcImage(Rect(60, 20, logoImage.cols, logoImage.rows));
	// 法二: Range() 范围选区
	//imageROI = srcImage(Range(20, 20 + logoImage.rows), Range(20, 20 + logoImage.cols));

	// 3. 混合
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	// 4. 显示
	namedWindow("<1>区域线性图像混合");
	imshow("<1>区域线性图像混合", srcImage);

	return true;
}

/*-------------- ROI_AddImage() ---------------*/
// 利用感兴趣的区域ROI实现图像叠加
bool ROI_AddImage()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\4.jpg");
	Mat logoImage = imread("..\\..\\picture\\sound.png");
	
	// 2. 定义一个Mat并设定ROI区域
	Mat imageROI = srcImage(Rect(20, 30, logoImage.cols, logoImage.rows));

	// 3. 加载掩模(注: 必须是灰度图)
	Mat mask = imread("..\\..\\picture\\sound.", 0);

	// 4. 将掩模复制到ROI
	logoImage.copyTo(imageROI, mask);

	// 5. Display
	namedWindow("<2>利用ROI实现图像叠加示例窗口");
	imshow("<2>利用ROI实现图像叠加示例窗口", srcImage);

	return true;
}

/*------------ LinearBlending() -------------*/
// 利用cv::addWdighted()实现图像线性混合

bool LinearBlending()
{
	// 参数设置
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage1, srcImage2, dstImage;

	// 1. Load image (注: 两图片必须同类型, 同尺寸)
	srcImage1 = imread("F:\\壁纸\\benbenla-06c.jpg");
	srcImage2 = imread("F:\\壁纸\\background.jpg");
	if (!srcImage1.data | !srcImage2.data)
		return -1;

	// 2. 进行图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0.0, dstImage);
	
	// 3. 显示
	//namedWindow("<3.0>原图");
	//imshow("<3.0>原图", srcImage1);

	namedWindow("<3.1>线性混合");
	imshow("<3.1>线性混合", dstImage);

	return true;
}