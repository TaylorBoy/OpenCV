/*
	ģ��ƥ��: matchTemplate()
	void matchTemplate(InputArray image, InputArray temp1, OutputArray result, int method)
		@param image : ������ͼ��
		@param temp1 : ����ģ��, �ߴ粻����ԭͼ
		@param result : �ȽϽ����ӳ��ͼ
		@param method : ƥ�䷽��
		       1. ƽ���� method = TM_SQDIFF
			   2. ��һ��ƽ���� method = TM_SQDIFF_NORMED
			   3. ���ƥ�� method = TM_CCORR
			   4. ��һ�����ƥ�� method = TM_CCORR_NORMED
			   5. ϵ��ƥ�� method = TM_CCOEFF
			   6. �����ϵ��ƥ�� method = TM_CCOEFF_NORMED
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "SRC IMAGE"
#define WINDOW_NAME2 "RESTULT"

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatChMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void *);

int main()
{
	g_srcImage = imread("..\\..\\picture\\12.jpg");
	g_templateImage = imread("..\\..\\picture\\template1.jpg");
	if (!g_srcImage.data || !g_templateImage.data) return -1;

	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, CV_WINDOW_AUTOSIZE);

	createTrackbar("����", WINDOW_NAME1, &g_nMatChMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

	while ((char)waitKey() != 'q') {}

	return 0; 
}

void on_Matching(int, void *)
{
	Mat srcImage;
	g_srcImage.copyTo(srcImage);

	// ��ʼ�����ڽ������ľ���
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int retultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, retultImage_rows, CV_32FC1);

	// ����ƥ��ͱ�׼��
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatChMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	// ͨ������minMaxLoc()��λ��ƥ���λ��
	double minValue, maxValue;
	Point minLocation, maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	// ����SQDIFF��SQDIFF_NORMED, ԽС��ֵƥ��������, ������ķ���, ��ֵԽ��ƥ����Խ��
	if (g_nMatChMethod == TM_SQDIFF || g_nMatChMethod == TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	// ���Ƴ�����, ����ʾ���
	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), 
		Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);
}
