/*
	1. 计算直方图(Histogram): calcHist()
	原型: void calcHist(const Mat* image, int nimages, const int* channels, InputArray mask, OutputArray hist,
					    int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false);
		  @param images   : 输入数组(CV_8U / CV32F)
		  @param nimages  : 输入数组个数
		  @param channels : 需要统计的通道(dim)索引[第一个数组: 0~images[0].channels()-1]
		  @param mask     : 可选掩码(8位)
		  @param hist     : 输出数组
		  @param dims     : 需要计算的直方图维度, 不大于CV_MAX_DIMS(32)
		  @param histSize : 存放每个维度的直方图尺寸的数组
		  @param ranges   : 每一维度数组的取值范围
		  @param uniform  : 指示直方图是否均匀
		  @param accumulate : 累计标识符, true时直方图在配置截断不会被清零

	2. 寻找最值: minMaxLoc()
	原型: void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray());
		  @param src : 输入的单通道阵列
		  @param minVal : 返回最小值的指针
		  @param maxVal : 返回最大值的指针
		  @param minLoc : 返回最小位置的指针
		  @param maxLoc : 返回最大位置的指针
		  @param mask   : 可选掩膜
		  
	3. 术语:
		  dims : 需要统计的特征数目, 如灰度图dims = 1
		  bins : 每个特征空间子区段的数目, 即直条的数目
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. 载入原图, 转为HSV颜色模型
	Mat srcImage, hsvImage;
	srcImage = imread("..\\..\\picture\\31.jpg");
	if (!srcImage.data) return -1;

	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	// 2. 参数准备

	//    将色调量化为30个等级, 将饱和度量化为32个等级
	int hueBinNum = 30;          // 色调直方图的条数
	int staturationBinNum = 32;  // 饱和度条数
	int histSize[] = { hueBinNum, staturationBinNum };
	//    定义色调变换范围: 0-179
	float hueRanges[] {0, 180};
	//    定义饱和度变化范围0-255
	float staturationRanges[] = { 0, 255 };
	const float* ranges[] = { hueRanges, staturationRanges };
	MatND dstHist;

	//    计算第0和第1通道的直方图
	int channels[] = { 0, 1 };

	// 3. 正式调用calcHist()
	calcHist(&hsvImage,
		1,           // 数组个数为1
		channels,    // 通道索引
		Mat(),       // 不使用掩膜
		dstHist,     // 输出目标
		2,           // 需要计算的直方图的维度
		histSize,    // 存放每个维度的直方图尺寸的数组
		ranges,      // 每个维度数组的取值范围
		true,        // 均匀的直方图
		false);      // 不累计, 清零

	// 4. 为绘制直方图准备参数
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	int scale = 10;
	Mat histImg = Mat::zeros(staturationBinNum * scale, hueBinNum * 10, CV_8UC3);

	// 5. 绘制直方图
	for (int hue = 0; hue < hueBinNum; ++hue)
	{
		for (int staturation = 0; staturation < staturationBinNum; ++staturation)
		{
			float binValue = dstHist.at<float>(hue, staturation);  // 直方图条值
			int intensity = cvRound(binValue * 255 / maxValue);    // 强度

			// 正式绘制
			rectangle(histImg, Point(hue * scale, staturation * scale), Point((hue + 1) * scale - 1, (staturation + 1) * scale - 1),
				Scalar::all(intensity), FILLED);
		}
	}

	imshow("素材图", srcImage);
	imshow("H-S直方图", histImg);

	waitKey(0);
}

