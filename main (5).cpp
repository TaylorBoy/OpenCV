#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/* �ص����� */
static void on_ContrastAndBirght(int, void *);

/* ȫ�ֱ��� */
int g_nContrastValue;	// �Աȶ�
int g_nBrightValue;		// ����
Mat g_srcImage, g_dstImage;

////////////////////////////////////////
int main()
{
	// 1. Read in image
	g_srcImage = imread("..\\..\\picture\\6.jpg");
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	// 2. �趨�ԱȶȺ����ȳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	// 3. ����Ч������
	namedWindow("Ч��ͼ");

	// 4. �����켣��
	createTrackbar("�Աȶ�: ", "Ч��ͼ", &g_nContrastValue, 300, on_ContrastAndBirght);
	createTrackbar("��  ��: ", "Ч��ͼ", &g_nBrightValue, 200, on_ContrastAndBirght);

	// 5. �ص�������ʼ��
	on_ContrastAndBirght(g_nContrastValue, 0);
	on_ContrastAndBirght(g_nBrightValue, 0);

	//while (char(waitKey(100)) != 'q'){}
	waitKey(0);

	return 0;
}

/* �ص����� */
static void on_ContrastAndBirght(int, void *)
{
	double time0 = saturate_cast<double>(getTickCount());
	// ����: g_dstImage(i, j) = a * g_srcImage(i, j) + b
	//       ��� = �Աȶ�a * ���� + ����b
	for (int y = 0; y < g_srcImage.rows; ++y)
	{
		for (int x = 0; x < g_srcImage.cols; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = 
					saturate_cast<uchar>(g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y, x)[c] + g_nBrightValue);
			}
		}
	}

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "Run Time: " << time0 << "seconds" << endl;

	// ��ʾЧ��
	imshow("Ч��ͼ", g_dstImage);
}