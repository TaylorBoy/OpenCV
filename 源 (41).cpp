#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// ������ = ��ʴ �� ����, ����С����
// ��ѧ���ʽ: dstImage = open(src, element) = dilate(erode(src, element));
// ������ = ���� �� ��ʴ, �ų�С�ͺڶ�(��ɫ����)
// ��ѧ���ʽ: dstImage = close(src, element) =  erode(dilate(src, element));
// ��̬ѧ�ݶ� = ���� - ��ʴ, ���ſ�ı�Եͻ��, ������Ե����
// ��ѧ���ʽ: dstImage = morph - grad(src, element) = dilate(src, element) - erode(src, element);
// ��ñ = ԭͼ - ������, ������ڽ������İ߿�
// ��ѧ���ʽ: dstImage = tophat(src, element) = src - open(src, element);
// ��ñ = ������ - ԭͼ, ������ڽ��㰵�İ߿�, ��������

/*
void morphologyEx(
InputArray src,
OutputArray dst,
int op,
InputArray kernel,
Point anchor=Point(-1, -1),
int iterations=1;
int borderType=BORDER_DEFAULT,
const Scalar& borderValue=morphologyDefaultBorderValue()
);

@op: ��̬ѧ���ͱ�־(OPEN, COLSE, GRADIENT, TOPHAT, BLACKHAT, ERODE, DILATE)
@kernel: �ں�, һ��ʹ��getStructuringElement()
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");
	imshow("Src Image", image);

	// �����
	Mat element = getStructuringElement(MORPH_RECT, Size(6, 6));

	// ������̬ѧ����, ���Ĳ������ͼ���
	morphologyEx(image, image, MORPH_BLACKHAT, element);

	// Display
	imshow("Result", image);

	waitKey(0);

	return 0;
}