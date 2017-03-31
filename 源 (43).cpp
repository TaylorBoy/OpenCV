#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
	��̬ѧ(Morphology)�˲�(1): ��ʴ \ ����
	void erode(
		InputArray src,
		OutputArray dst,
		InputArray kernel,  // ��, NULLʱĬ��Ϊ3x3, һ��ʹ��getStructuringElement()
		Point anchor=Point(-1,-1),
		int iterations=1;   // ����ʹ��erode�Ĵ���
		int borderType=BORDER_DEFAULT,
		const Scalar& borderValue=morphologyDefaultBorderValue()
	);
	void dilate(
		InputArray src,
		OutputArray dst,
		InputArray kernel,
		Point anchor=Point(-1,-1),
		int iterations=1;
		int borderType=BORDER_CONSTANT,
		const Scalar& borderValue=morphologyDefaultBorderValue()
	);
*/

/* ȫ�ֱ��� */
Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0;   // 0: erode, 1: dilate;
int g_nStructElementSize = 3;  // �ں˾���ߴ�

/* ȫ�ֺ��� */
void Process();  // ���ͺ͸�ʴ�Ĵ�����
static void on_TrackbarNumChange(int, void *);
static void on_ElementSizeChange(int, void *);

/*-------------------- main -------------------*/

int main()
{
	system("color 5E");
	g_srcImage = imread("..\\..\\picture\\1.jpeg");
	if (!g_srcImage.data) return -1;
	imshow("g_srcImage", g_srcImage);

	// ���θ�ʴ����ʾЧ��
	namedWindow("Result");

	// ��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT,  // ����: RECT, ������: CROSS, ��Բ: ELLIPSE
		Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize));
	// ���θ�ʴ
	erode(g_srcImage, g_dstImage, element);
	imshow("Result", g_dstImage);

	// �����켣��
	createTrackbar("��ʴ/����", "Result", &g_nTrackbarNumber, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "Result", &g_nStructElementSize, 21, on_ElementSizeChange);

	while (char(waitKey(10)) != 'q'){}

	cout << "Quit successfully !" << endl;

	return 0;
}

//----------------- ��ʴ \ ���� ������ -------------------
void Process()
{
	// ��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize));

	// ���и�ʴ�����Ͳ���
	if (0 == g_nTrackbarNumber)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);

	// Display
	imshow("Result", g_dstImage);
}

//----------------- ��ʴ \ ���� �л� ------------------
static void on_TrackbarNumChange(int, void *)
{
	// ״̬�ı�, ����Process()��������
	if (0 == g_nTrackbarNumber)
		cout << "���ڽ��и�ʴ����..." << endl;
	else
		cout << "���ڽ������Ͳ���..." << endl;
	Process();
}

//----------------- ��ʴ \ ���� ֵ�ı� ------------------
static void on_ElementSizeChange(int, void *)
{
	// ״̬�ı�, ����Process()��������
	Process();
}

