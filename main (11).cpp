#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "��ͼ1"
#define WINDOW_NAME2 "��ͼ2"
#define WINDOW_WIDTH 600  // ���崰�ڴ�С

/*--------------- ������Բ ---------------*/
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;   // �߿�
	int lineType = 8;    // ����--8��ͨ��

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),	// ����
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),	// ��Сλ�ھ�����
		angle,			// ��ת�Ƕ�
		0,				// ��չ���� 0-360
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType);
}

/*--------------- ����ʵ��Բ -------------*/
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;		// �ߴ� -- ʵ��
	int lineType = 8;

	circle(img,
		center,				 // Բ��
		WINDOW_WIDTH / 32,   // �뾶
		Scalar(125, 56, 23),
		thickness,
		lineType);
}

/*--------------- ���ư������ ------------*/
void DrawPolygon(Mat img)
{

}

/*--------------- ����ֱ�� ----------------*/
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;

	line(img,
		start,
		end,
		Scalar(128, 255, 33),
		thickness,
		lineType);
}

//////////////////////////////////////////////

int main()
{
	// �����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// 1.1 ����4����Բ
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	// 1.2 ����Բ��
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));


	// ��ʾ����Ч��ͼ
	imshow(WINDOW_NAME1, atomImage);

	waitKey(0);

	return 0;
}