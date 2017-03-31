/*
	直方图对比: compareHist()
	原型: double compareHist(InputArray H1, InputArray H2, int method);
		  double compareHist(const SparseMat& H1, const SparseMat& H2, int method)
	四种方法:
		  1. 相关: Correlation(method = CV_COMP_CORREL)
		  2. 卡方: Chi-Square(method = CV_COMP_CHISQR)
		  3. 直方图相交: Intersection(method = CV_COMP_INTERSERT)
		  4. Bhattacharyya距离: method = CV_OMP_BHATTACHARYYA
*/
#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	// 1. 声明储存基准图像和另外两张对比图像的矩阵(RGB和HVS)
	Mat srcImage_base, hsvImage_base;
	Mat srcImage_test1, hsvImage_test1;
	Mat srcImage_test2, hsvImage_test2;
	Mat hsvImage_halfDown;

	// 2. 载入基准图像和两张测试图像, 并显示
	srcImage_base  = imread("1.jpg", IMREAD_COLOR);
	srcImage_test1 = imread("2.jpg", IMREAD_COLOR);
	srcImage_test2 = imread("3.jpg", IMREAD_COLOR);
	if (!srcImage_base.data || !srcImage_test1.data || !srcImage_test2.data)
		return -1;
	imshow("基准图像", srcImage_base);
	imshow("测试图 1", srcImage_test1);
	imshow("测试图 2", srcImage_test2);

	// 3. 将图像由BGR转换到HSV色彩空间
	cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
	cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
	cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);

	// 4. 创建包含基准图像下半部的半身图像(HSV)
	hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows / 2, hsvImage_base.rows - 1), Range(0, hsvImage_base.cols - 1));

	// 5. 初始化计算直方图需要的参数

	// 对hue(色度)通道使用30个bin, 对staturation(饱和度)通道使用32个bin
	int h_bins = 50, s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	// hue的取值范围: 0-255, staturation的取值范围: 0-179
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// 使用第0和第1通道
	int channels[] = { 0, 1 };

	// 6. 创建存储直方图的MatND类实例
	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

	// 7. 计算基准图像, 两张测试图像, 半身基准图像的HSV直方图
	calcHist(&hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false);
	normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
	normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());

	// 8. 按顺序使用4种对比标准将基准图像的直方图与其余各直方图进行对比
	for (int i = 0; i < 4; ++i)
	{
		// 进行图像直方图的对比
		int compare_method = i;
		double base_base = compareHist(baseHist, baseHist, compare_method);
		double base_half = compareHist(baseHist, halfDownHist, compare_method);
		double base_test1 = compareHist(baseHist, testHist1, compare_method);
		double base_test2 = compareHist(baseHist, testHist2, compare_method);

		// 输出结果
		printf("方法 [%d] 匹配结果如下: \n\n[基准图-基准图]: %f, [基准图-半身图]: %f, [基准图-测试图1]: %f, [基准图-测试图2]: %f\n\
-------------------------------------------------------\n", i, base_base, base_half, base_test1, base_test2);
	}

	printf("Successfully!\n");

	
	waitKey(0);

	return 0;
}