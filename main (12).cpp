#include <opencv2/opencv.hpp>
using namespace cv;

#define WINDOW_NAME "Window"

/* [ȫ�ֺ�������] */
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

/* [ȫ�ֱ�������] */
Rect g_rectangle;
bool g_bDrawingBox = false;  // �Ƿ���л���
RNG  g_rng(123456);		// RNG() ��ʼ�������״̬��������

/*------------------- main -------------------*/
int main(int argc, char** argv)
{
	/* 1. ����׼�� */
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);  // scalar: ����, ����

	/* 2. �����������ص����� */
	namedWindow(WINDOW_NAME);
	// void setMouseCallback(const string& winname, MouseCallback onMouse, void* userdata=0);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	/* 3. ��ѭ��, ���ص� */
	for (;;)
	{
		srcImage.copyTo(tempImage);  // ����ԭͼ����ʱ����
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);

		if (27 == waitKey(10))
			break;  // ��ESC�˳�
	}


	return 0;
}

/*---------------- ���ص����� --------------*/
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
		// ����ƶ�
	case EVENT_MOUSEMOVE:
		if (g_bDrawingBox)
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
		break;

		// �������
	case EVENT_LBUTTONDOWN:
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);  // ��¼��ʼ��
		break;

		// ����ɿ�
	case EVENT_LBUTTONUP:
		g_bDrawingBox = false;
		// �Կ�͸�С��0�Ĵ���
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}

		// ���û��ƺ���
		DrawRectangle(image, g_rectangle);

		break;

	default:
		break;
	}
}


/*---------------- ���λ��ƺ��� --------------*/
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	// �����ɫ
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
