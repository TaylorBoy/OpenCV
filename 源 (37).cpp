#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

//------------------ �궨�� -------------------
#define WINDOW_NAME "ͼ������"

//----------------- ȫ�ֱ��� ------------------
Mat g_srcImage, g_dstImage, g_tmpImage;

//------------------ ������ -------------------
int main()
{
	// 1. ����ԭͼ
	g_srcImage = imread("..\\..\\picture\\15.jpg");
	if (!g_srcImage.data) return -1;

	// 2. ������ʾ����
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	// 3. ������ֵ
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key = 0;
	// 4. ��ѯ
	for (;;)
	{
		key = waitKey(1000);  // ��ȡ����ֵ

		switch (key)
		{
			//=============== �˳� =================
			case 27:
				return 0;
				break;
			case 'q':
				return 0;
				break;

			//=============== �Ŵ� =================
			case 'a':  // A����, ����pyrUp()
				pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
				printf("> [A], ִ��pryUp(). X2\n");
				break; 

			case 'w': // W, resize()
				resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
				printf("> [W], ִ��resize(). X2\n");
				break;

			//=============== ��С =================
			case 'd': // D����, ����pyrDown()
				pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
				printf("> [D], ִ��pryDown(). /2\n");
				break;

			case 's': // S, resize()
				resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
				printf("> [S], ִ��resize(). /2\n");
				break;

			default:
				continue;
				break;
		}

		// Display
		imshow(WINDOW_NAME, g_dstImage);

		// ��g_dstImage����g_tmpImage, ������һ��ѭ��
		g_tmpImage = g_dstImage;
	}

	return 0;
}
