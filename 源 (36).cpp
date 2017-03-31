
/*
	<< ��(y��)ֵ�� >>

	1. �̶���ֵ����: threshold()
	void threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);
	@thresh: ��ֵ����ֵ
	@maxval: ��typeȡCV_THRESH_BINARY / CV_THRESH_BINARY_INV��ֵ����ʱ�����ֵ
	@type  : ��ֵ����(
		0, THRESH_BINARY,     dst(x, y) = maxval [src(x,y) > thresh] ORTHERWISE = 0
		1, THRESH_BINARY_INV, �෴ ��
		2, THRESH_THUNC,      dst(x, y) = 0 [src(x,y) > thresh] OTHERWISE = src(x, y)
		3, THRESH_TOZERO,	  dst(x, y) = src(x, y) [src(x,y) > thresh] OTHERWISE = 0
		4, THRESH_TOZERO_INV, �෴ ��
	)

	2. ����Ӧ��ֵ����: adaptiveThreshold()
	void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C);
	@adaptiveMethod: ָ������Ӧ��ֵ�㷨(
		ADAPTIVE_THRESH_MEAN_C,    : T(x, y) = blockSize * blockSize������(x,y)��ȥ����C��ƽ��ֵ // mean: ƽ��
		ADAPTIVE_THRESH_GAUSSIAN_C : T(x, y) = blockSize * blockSize������(x,y)��ȥC���˹��������صļ�Ȩ�ܺ�.
		)  
	@thresholdType : ��ֵ����, ����ȡ
		THRESH_BINARY      : dst(x, y) = maxValue [src(x,y) > T(x,y)] otherwise 0
		THRESH_BINARY_INV  : �෴ ��
	@blockSize: ������ֵ��С��һ�����ص�����ߴ�, ȡ3, 5, 7��
	@C: ��ȥƽ�����Ȩֵ��ĳ���, һ��Ϊ����(��<=0)
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-------------- �� ---------------
#define WINDOW_NAME "��ֵ��"

//----------- ȫ�ֱ��� ------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_dstImage, g_grayImage;

//----------- ȫ�ֺ��� ------------
static void on_Threshold(int, void *);

int main()
{
	// Load Image
	g_srcImage = imread("..\\..\\picture\\18.jpg");
	if (!g_srcImage.data) return -1;

	// ����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	// �������ڲ���ʾԭͼ
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow("ԭͼ", g_srcImage);

	// ����������
	createTrackbar("ģʽ", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	createTrackbar("����", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);

	// ��ʼ���ص�����
	on_Threshold(0, 0);

	while (char(waitKey(9)) != 'q'){}

	waitKey(0);

	return 0;
}

//----------- �ص����� -----------
static void on_Threshold(int, void *)
{
	// ������ֵ����
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	// Display
	imshow(WINDOW_NAME, g_dstImage);
}