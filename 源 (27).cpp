/*
	��ӳ��: 
	void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interprolation, int borderType=BORDER_CONSTANT, const Scalar& borderValue=Scalar());
	     @src : ��ͨ��8λ���߸�����ͼ��
		 @map1 : 1) ��(x,y)�ĵ�һ��ӳ��; 2) ��ʾCV_16C2, CV_32FC1, CV_32FC2���͵�Xֵ
		 @map2 : 1) map��ʾ(1)ʱmap2�������κ�ֵ; 2) ��ʾCV_16UC1, CV32FC1���͵�Yֵ(�ڶ���ֵ)
		 @interpolation : ��ֵ��ʽ
			INTER_NEAREST  -- ����ڲ�ֵ
			INTER_LINEAR   -- ˫���Բ�ֵ(Ĭ��)
			INTER_CUBLIC   -- ˫����������ֵ(��4x4���������ڵ�˫���β�ֵ)
			INTER_LANCZOS4 -- Lanczos��ֵ(��8x8���������Lanczos��ֵ)
		@
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread("..\\..\\picture\\9.jpg");
	imshow("Src Image", srcImage);

	// ������ԭʼͼһ����Ч��ͼ, x��ӳ��ͼ, y��ӳ��ͼ
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	// �������ص�, �ı�map_x & map_y��ֵ
	for (int j = 0; j < srcImage.rows; ++j)
	{
		for (int i = 0; i < srcImage.cols; ++i)
		{
			// �ı�map_x&map_yֵ
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	// ������ӳ��
	// OpenCV2
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	// OpenCV3
	//remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}