/*
	1. Ѱ������: findContours()
	   void findContours(InputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point());
	   @param image : ������ 8λ ��ͨ��ͼ��
	   @param contours : ��⵽������, ÿ����������Ϊһ������vector<Point>
	   @param hierarchy : ��ѡ�������, ����������Ϣ
	   @param mode : ��������ģʽ
		      RETR_EXTERNAL
			  RETR_LIST
			  RETR_CCOMP
			  RETR_TREE
	   @param method : �����Ľ��ư취
			  CHAIN_APPROX_NONE
			  CHAIN_APPROX_SIMPLE
			  CHAIN_APPROX_TC89_L1
			  CHAIN_APPROX_TC89_KCOS
	   @param offset : ÿ��������Ŀ�ѡƫ����

	2. ��������: drawContours()
	   void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8,
	                     InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point());
	   @param contourIdx : �������Ƶ�ָʾ����, ��Ϊ��ֵ, �������������
	   @param color : ��������ɫ
	   @param thickness : ���������Ĵ�ϸ��
	   @param hierarchy : ��ѡ�Ĳ�νṹ��Ϣ
	   @param maxLevel  : �������Ƶ����ȼ�
*/

#include <opencv2/opencv.hpp>	
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. �Զ�ֵģʽ����ԭʼͼ
	Mat srcImage = imread("..\\..\\picture\\19.jpg", 0);
	if (!srcImage.data) return -1;
	imshow("ԭʼͼ", srcImage);

	// 2. ��ʼ�����ͼ
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	// 3. srcImageȡ������ֵ119���ǲ���
	srcImage = srcImage > 119;
	imshow("ȡ��ֵ���ԭʼͼ", srcImage);

	// 4. ���������Ͳ��
	std::vector<std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	// 5. ��������
	
	// OpenCV2
	// findContours(srcImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	// OpenCV3
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	// 6. �������ж��������, �������ɫ���Ƴ�ÿ�����������ɫ
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		// OpenCV2
		// drawContours(dstImage, contours, index, color, CV_FILLED, 8, hierarchy);
		// OpenCV3
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}

	imshow("����ͼ", dstImage);

	waitKey(0);

	return 0;
}