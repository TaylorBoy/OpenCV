#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*-------------------- ȫ�ֱ��� --------------------*/

// ԭͼ, ԭͼ�ĻҶ�ͼ, Ŀ��ͼ
Mat g_srcImage, g_srcGrayImage, g_dstImage;

// Canny
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;    // Trackbar Value

// Sobel
Mat g_sobelGradient_x, g_sobelGradient_y;
Mat g_sobelAbsGradient_x, g_sobelAbsGradient_y;
int g_sobelKernelSize = 1;		// Trackbar Value

// Scharr
Mat g_scharrGradient_x, g_scharrGradient_y;
Mat g_scharrAbsGradient_x, g_scharrAbsGradient_y;

/*-------------------- ȫ�ֺ��� --------------------*/

static void on_Canny(int, void *);
static void on_Sobel(int, void *);
void Scharr();  // ��װ��Scharr��Ե�����ش���ĺ���

/*--------------------- ������ ---------------------*/

int main()
{
	system("color 2F");

	// Load image
	g_srcImage = imread("..\\..\\picture\\20.jpg");
	if (!g_srcImage.data) return -1;

	// Display src image
	imshow("Src Image", g_srcImage);

	// ������srcͬ����ͬ��С�ľ���dst
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// ��ԭͼתΪ�Ҷ�ͼ
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);

	// ������ʾ����
	namedWindow("Canny", WINDOW_AUTOSIZE);
	namedWindow("Sobel", WINDOW_AUTOSIZE);

	// ����Trackbar
	createTrackbar("Value1", "Canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("Value2", "Sobel", &g_sobelKernelSize, 3, on_Sobel);

	// ���ûص�����
	on_Canny(0, 0);
	on_Sobel(0, 0);

	// Scharr ��Ե���
	Scharr();

	while (char(waitKey(9)) != 'q') {}

	return 0;
}


/*---------------------- on_Canny() ----------------------*/
static void on_Canny(int, void *)
{
	// 1. 3x3�ں˽���
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));

	// 2. ����Canny����
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	// 3. ��g_dstImage����Ԫ����0
	g_dstImage = Scalar::all(0);

	// 4. ��Canny����ı�Եͼ��Ϊ����, ��ԭͼsrc����Ŀ��ͼdst
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	// Display
	imshow("Canny", g_dstImage);
}

/*---------------------- on_Sobel() ----------------------*/
static void on_Sobel(int, void *)
{
	// 1. ��X�����ݶ�
	Sobel(g_srcImage, g_sobelGradient_x, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_x, g_sobelAbsGradient_x);

	// 2. ��Y�����ݶ�
	Sobel(g_srcImage, g_sobelGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_y, g_sobelAbsGradient_y);

	// 3. �ϲ��ݶ�
	addWeighted(g_sobelAbsGradient_x, 0.5, g_sobelAbsGradient_y, 0.5, 0., g_dstImage);

	// Display
	imshow("Sobel", g_dstImage);
}

/*---------------------- Scharr() ----------------------*/
void Scharr()
{
	// 1. ��X�����ݶ�
	Scharr(g_srcImage, g_scharrGradient_x, CV_16S, 1, 0, 1, 0);
	convertScaleAbs(g_scharrGradient_x, g_scharrAbsGradient_x);  // �������ֵ, �������ת��8λ

	// 2. ��Y�����ݶ�
	Scharr(g_srcImage, g_scharrGradient_y, CV_16S, 0, 1, 1, 0);
	convertScaleAbs(g_scharrGradient_y, g_scharrAbsGradient_y);

	// 3. �ϲ��ݶ�
	addWeighted(g_scharrAbsGradient_x, 0.5, g_scharrAbsGradient_y, 0.5, 0, g_dstImage);

	// Display
	imshow("Scharr", g_dstImage);
}