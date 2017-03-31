/*
	反向投影: calcBackProject()
	void calcBackProject(
		const Mat* images,       // 深度为CV_8U/CV_32F
		int nimages,             // 输入数组个数
		const int* channels,     // 通道数
		InputArray hist,         // 输入的直方图
		OutputArray backProject, // 输出反向投影阵列
		const float** ranges,    // 每一维度数组的取值范围
		double scale=1,          // 缩放因子
		bool uniform=true        // 是否均匀
	);

	通道复制: mixChannels()
	void mixChannels(
		const Mat* src,          // 输入数组
		size_t nsrcs,            // 输入数组src的矩阵数
		Mat* dst,                // 输出数组
		size_t ndsts,            // 输出数组dst的矩阵数
		const int* fromTo,       // 对指定的通道进行复制的数组索引
		size_t npairs            // 第5个参数fromTo的索引数
	);

	void mixChannels(
		const vector<Mat>& src,
		vector<Mat>& dst,
		const int* fromTo,
		size_t npairs
	);
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>	
#include <iostream>
using namespace cv;

#define WINDOW_NAME "SRC IMAGE"

Mat g_srcImage, g_hsvImage, g_hueImage;
int g_bins = 30;  // 直方图组距

void on_BinChange(int, void *);

int main()
{
	// 1. 读取原图, 并转换到HSV空间
	g_srcImage = imread("..\\..\\picture\\32.jpg");
	if (!g_srcImage.data) return -1;

	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
	9
	// 2. 分离hue色调通道
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	// 3. 抽奖Trackbar来输入bin的数目
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("色调组距", WINDOW_NAME, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	// 4. 显示效果图
	imshow(WINDOW_NAME, g_srcImage);

	while ((char)waitKey(0) != 'q'){}

	waitKey(0);

	return 0;
}

void on_BinChange(int, void *)
{
	// 1. 参数准备
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	// 2. 计算直方图并归一化
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	// 3. 计算反向投影
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	// 4. 显示反向投影
	imshow("Back Project", backproj);

	// 5. 绘制直方图参数准备
	int w = 400, h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	// 6. 绘制直方图
	for (int i = 0; i < g_bins; ++i)
	{
		rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
	}

	// 7. 显示直方图
	imshow("直方图", histImg);
}

