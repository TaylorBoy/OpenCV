#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#define WINDOW_NAME "[���Ի��ʾ��]"

/* [ȫ�ֱ�������] */
const int g_nMaxAlphaValue = 100;	// Alpha ֵ�����ֵ
int g_nAlphaValueSlider;			// �������ı���
double g_dAlphaValue;
double g_dBetaValue;

// �����洢ͼ��ı���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

/* [��Ӧ�������Ļص�����] */
void on_Trackbar(int, void *)
{
	// ��ǰalphaֵ��������ֵ�ı���
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = 1.0 - g_dAlphaValue;

	// ����alpha��betaֵ�������Ի��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	// ��ʾЧ��ͼ
	imshow(WINDOW_NAME, g_dstImage);

	// ��ȡ��ǰ�켣����λ��, track: ���, �ټ�
	// int getTrackbarPos(const string& trackbarname, const string& winname);
	printf("��ǰ�켣��λ��: %d\n", getTrackbarPos("͸���� 100", WINDOW_NAME));
}

int main(int argc, char** argv)
{
	// Loading image
	// ����ͼ�ĳߴ�Ҫ��ͬ
	g_srcImage1 = imread("F:\\��ֽ\\background.jpg");
	g_srcImage2 = imread("F:\\��ֽ\\benbenla-06c.jpg");
	if (!g_srcImage1.data | !g_srcImage2.data)
	{
		printf("Loading image error !\n");
		return -1;
	}

	// ���û�������ֵ
	g_nAlphaValueSlider = 70;

	// ��������
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	// �ڴ����д���������
	char TrackbarName[50];
	sprintf(TrackbarName, "͸���� %d", g_nMaxAlphaValue);

	// int createTrackbar(const string& trackbarName, const string& winName, int* value, int count, 
	// TrackbarCallback onChange = 0, void* userdata = 0)
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	// ����ڻص���������ʾ
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);

	return 0;
}