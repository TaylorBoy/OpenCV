/*
	Canny����:
	1) ��������: ʹ�ø�˹ƽ���˲����������
	2) �����ݶȷ�ֵ�ͷ���(0,45,90,135), ����Sobel�˲���
	3) �Ǽ���ֵ����: ������ѡ��Ե
	4) �ͺ���ֵ: ����ֵ�͵���ֵ, �ߵ���ֵ���Ƽ���2:1��3:1֮��
	ԭ��: void Canny(InputArray src, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false);
	      @apertureSize: Ӧ��Sobel���ӵĿ׾���С
		  @L2gradient  : ����ͼ���ݶȷ�ֵ�ı�־
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>	
using namespace cv;

int main()
{
	// Load image
	Mat src = imread("..\\..\\picture\\1.jpg");
	Mat src1 = src.clone();

	// Display src image
	imshow("Src Image", src);

	//----------------------------------------------------------------------------------------------------------
	// �߽�Canny�÷�: ת�ɻҶ�ͼ �� ���� �� Canny �� �ȵ���Ե, ��Ϊ����, Copyԭͼ��Ч��ͼ�� �� �õ���ɫ�ı�Եͼ
	//----------------------------------------------------------------------------------------------------------
	Mat dst, edge, gray;

	// 1. ������srcͬ���ͺʹ�С�ľ���dst
	dst.create(src1.size(), src1.type());

	// 2. ��ԭͼת��Ϊ�Ҷ�ͼ
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	// 3. ����: 3x3
	blur(gray, edge, Size(3, 3));

	// 4. ����Canny����
	Canny(edge, edge, 3, 9, 3);
	imshow("Canny edge", edge);

	// 5. ��dst������Ԫ����0
	dst = Scalar::all(0);

	// 6. ʹ��Canny��������ı�Եͼedge��Ϊ����, ��ԭͼcopy��Ŀ��ͼdst��
	src1.copyTo(dst, edge);

	// Display
	imshow("Result", dst);

	waitKey(0);

	return 0;
}