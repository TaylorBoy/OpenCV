#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
��ˮ���(floodFill): �����汾.
int floodFill(InputOutputArray image, Point seedPoint, Scalar newValue, Rect* rect=0, Scalar loDiff=Scalar(), Scalar upDiff=Scalar(), int flags=4);
int floodFill(InputOutputArray image, InputOutputArray mask, Point seedPoint, Scalar newValue, Rect* rect=0, Scalar loDiff=Scalar(), Scalar upDiff=Scalar(), int flags=4);

@image: ����/���1ͨ����3ͨ��, 8λ�򸡵�ͼ��
@mask : ��ͨ��, 3λ, ���Ϳ�������ͼ��image���������ص�. [��ˮ��䲻�������ģmask�ķ�����������]
@seedPoint: ��ˮ����㷨����ʼ��
@newValue : �ػ��������ص���ֵ, ���ص㱻Ⱦɫ��ֵ
@loDiff	  : ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮����(lower brightness/color difference)�����ֵ
@upDiff   : ����
*/

int main()
{
	// Load image
	Mat src = imread("..\\..\\picture\\1.jpeg");k
	imshow("Src Image", src);

	// Flood Fill
	Rect ccomp;
	floodFill(src, Point(0, 0), Scalar(0, 0, 0), &ccomp, Scalar(20, 20, 4), Scalar(10, 10, 10));

	// Display Result
	imshow("Result", src);

	waitKey(0);

	return 0;
}