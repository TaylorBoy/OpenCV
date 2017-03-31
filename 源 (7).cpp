/*
	Shi-Tomasi角点检测: goodFeaturesToTrack()
	void goodFeaturesToTrack(
		InputArray image,              // 8位或浮点型32位单通道图像
		OutputArray corners,           // 输出
		int maxCorners,                // 角点的最大数量
		double qualityLevel,           // 角点检测可接受的最小特征值, 通常不超过1
		double minDistances,           // 角点之间的最小距离
		InputArray mask=noArray(),     // 感兴趣区域
		int blockSize=3,               // 计算导数自相关矩阵指定的邻域范围
		bool useHarrisDetector=false,  // 是否使用Harris角点检测
		double k=0.04                  // 用于设置Harris自相关矩阵行列式的相对权重的权重系数
	);
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi角点检测"

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaduresToTrack(int, void *);

int main()
{
	g_srcImage = imread("..\\..\\picture\\33.jpg");
	if (!g_srcImage.data) return -1;
	
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("最大角点数", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaduresToTrack);
	on_GoodFeaduresToTrack(0, 0);

	while ((char)waitKey(0) != 'q'){}

	return 0;
}

void on_GoodFeaduresToTrack(int, void *)
{
	// 1. 对于变量小于1时处理
	if (g_maxCornerNumber <= 1)	{ g_maxCornerNumber = 1; }

	// 2. Shi-Tomasi算法的参数准备
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	Mat copy = g_srcImage.clone();

	// 3. 进行Shi-Tomasi角点检测
	goodFeaturesToTrack(g_grayImage,
		corners,
		g_maxCornerNumber,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		false,
		k);

	cout << "> 此次检测到的角点数量: " << corners.size() << endl;

	// 5. 绘制检测到的角点
	int r = 4;
	for (unsigned int i = 0; i < corners.size(); ++i)
	{
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8, 0);
	}

	imshow(WINDOW_NAME, copy);




}
