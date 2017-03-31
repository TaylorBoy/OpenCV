/*
	Shi-Tomasi�ǵ���: goodFeaturesToTrack()
	void goodFeaturesToTrack(
		InputArray image,              // 8λ�򸡵���32λ��ͨ��ͼ��
		OutputArray corners,           // ���
		int maxCorners,                // �ǵ���������
		double qualityLevel,           // �ǵ���ɽ��ܵ���С����ֵ, ͨ��������1
		double minDistances,           // �ǵ�֮�����С����
		InputArray mask=noArray(),     // ����Ȥ����
		int blockSize=3,               // ���㵼������ؾ���ָ��������Χ
		bool useHarrisDetector=false,  // �Ƿ�ʹ��Harris�ǵ���
		double k=0.04                  // ��������Harris����ؾ�������ʽ�����Ȩ�ص�Ȩ��ϵ��
	);
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi�ǵ���"

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
	createTrackbar("���ǵ���", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaduresToTrack);
	on_GoodFeaduresToTrack(0, 0);

	while ((char)waitKey(0) != 'q'){}

	return 0;
}

void on_GoodFeaduresToTrack(int, void *)
{
	// 1. ���ڱ���С��1ʱ����
	if (g_maxCornerNumber <= 1)	{ g_maxCornerNumber = 1; }

	// 2. Shi-Tomasi�㷨�Ĳ���׼��
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	Mat copy = g_srcImage.clone();

	// 3. ����Shi-Tomasi�ǵ���
	goodFeaturesToTrack(g_grayImage,
		corners,
		g_maxCornerNumber,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		false,
		k);

	cout << "> �˴μ�⵽�Ľǵ�����: " << corners.size() << endl;

	// 5. ���Ƽ�⵽�Ľǵ�
	int r = 4;
	for (unsigned int i = 0; i < corners.size(); ++i)
	{
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8, 0);
	}

	imshow(WINDOW_NAME, copy);




}
