#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*---------------- ȫ�ֱ��� ----------------*/
Mat g_srcImage, g_dstImage, g_midImage;
std::vector<Vec4i> g_lines;  // ����һ��ʸ���ṹ���ڴ���߶�
int g_nThreshold = 100;      // �������յ�Trackbarλ�ò���

/*---------------- ȫ�ֺ��� ----------------*/
static void on_HoughLines(int, void *);

/*---------------- main���� ----------------*/
int main()
{
	system("color 3F");

	g_srcImage = imread("..\\..\\picture\\21.jpg");
	imshow("Src Image", g_srcImage);

	// ����������
	namedWindow("Result Image", WINDOW_AUTOSIZE);
	createTrackbar("Value", "Result Image", &g_nThreshold, 200, on_HoughLines);

	// ��Ե���, ת�Ҷ�ͼ
	Canny(g_srcImage, g_midImage, 50, 200, 3);
	cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR);

	// ����һ�λص�����, ��һ��HoughLinesP����
	on_HoughLines(g_nThreshold, 0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);

	// Display
	imshow("Result Image", g_dstImage);

	waitKey(0);

	return 0;
}

/*---------------- �ص����� ----------------*/
static void on_HoughLines(int, void *)
{
	// �ֲ�����
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();

	//dstImage = Scalar::all(0);

	// ����HoughLinesP()
	std::vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nThreshold + 1, 50, 10);

	// �����߶�
	for (size_t i = 0; i < mylines.size(); ++i)
	{
		Vec4i ln = mylines[i];
		line(dstImage, Point(ln[0], ln[1]), Point(ln[2], ln[3]), Scalar(23, 180, 55), 1, LINE_AA);
	}

	// Display
	imshow("Result Image", dstImage);
}