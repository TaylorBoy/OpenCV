#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//------------- �궨�� --------------
#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "����ͼ"

//------------ ȫ�ֱ��� -------------
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

//------------ ȫ�ֺ��� -------------
static void on_ThreshChange(int, void *);

//------------ main���� -------------
int main()
{
	system("color 1F");

	g_srcImage = imread("..\\..\\picture\\27.jpg");
	if (!g_srcImage.data) return -1;

	// 1. ת�ɻҶ�ͼ��ģ������
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 2. ��������
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	// 3. ��������������ʼ��
	createTrackbar("Canny��ֵ", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	while (char(waitKey(9)) != 'q'){}

	return 0;
}

//---------------- on_ThreshChange() -----------------
static void on_ThreshChange(int, void *)
{
	// ��Canny���Ӽ���Ե
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	// Ѱ������
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// ��������
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); ++i)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}
