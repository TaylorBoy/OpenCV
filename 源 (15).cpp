/*
	ʵ��ͼ���޲�: inpaint()
	ԭ��: void inpaint(InputArray src, InputArray inpaintMask, OutputArray dst, double inpaintRadius, int flags);
		  @param inpaintMask : �޸���Ĥ, 8λ��ͨ��ͼ��, ���з������ر�ʾ��Ҫ�޲�������
		  @param inpaintRadius : ��Ҫ�޲���ÿ�����Բ������, Ϊ�޸��㷨�Ĳο��뾶
		  @param flags : �޲���ʶ��
		                 INPAINT_NS    -- ����Navier-Stokes���̵ķ���
						 INPAINT_TELEA -- Alexandru Telea����
*/

#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>	
#include <iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "SRC IMAGE"
#define WINDOW_NAME2 "DST IMAGE"

Mat g_srcImage, inpaintMask;
Point previousPoint(-1, -1);  // ԭ���ĵ������

static void on_Mouse(int event, int x, int y, int flags, void *)
{
	// ����������
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	// ����������
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	// ����ƶ�
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		// ���ư�ɫ����
		line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, previousPoint, pt, Scalar(0, 0, 255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, g_srcImage);
	}
}

int main()
{
	// ����ԭͼ��������Ĥ�ĳ�ʼ��
	Mat srcImage = imread("..\\..\\picture\\9.jpg");
	if (!srcImage.data) return -1;

	g_srcImage = srcImage.clone();
	inpaintMask = Mat::zeros(g_srcImage.size(), CV_8U);

	imshow(WINDOW_NAME1, g_srcImage);

	// �������ص���Ϣ
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);

	// ������ѯ
	while (true)
	{
		char c = (char)waitKey(0);

		if (27 == c)
			break;

		// 2 : �ָ�ԭͼ
		if ('2' == c)
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow(WINDOW_NAME1, g_srcImage);
		}

		// 1/�ո� : ͼ���޲�
		if ('1' == c || ' ' == c)
		{
			Mat inpaintedImage;
			inpaint(g_srcImage, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}