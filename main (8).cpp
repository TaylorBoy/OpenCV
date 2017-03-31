#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*---------------------------*/
bool ROI_AddImage();
bool ROI_LinearBlending();
bool LinearBlending();
/*---------------------------*/

int main()
{
	system("color 5E");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	{
		cout << "Pragram run succeed !" << endl;
	}

	waitKey(0);

	return 0;
}

/*------------ ROI_LinearBlending() ------------*/
// ָ������ ���ͻ��, �Զ����������ͻ�� cv::addWeighted()
// void addWeighted(InputArray src1, double a1, InputArray src2, double a2, double a3, OutputArray dst, int dtype=-1);
//                  img              Ȩ��1      img2             Ȩ��2      Ȩ�� (+��)  ���            ��ѡ���,-1Ϊ�������ͬ

bool ROI_LinearBlending()
{
	// 1. Load image
	Mat srcImage = imread("..\\..\\picture\\14.jpg");
	Mat logoImage = imread("..\\..\\picture\\15.jpg");
	if (!srcImage.data | !logoImage.data)
		return false;

	// 2. ����һ��Mat����, ���趨ROI����
	Mat imageROI;
	// ��һ: Rect() ����ѡ��
	imageROI = srcImage(Rect(60, 20, logoImage.cols, logoImage.rows));
	// ����: Range() ��Χѡ��
	//imageROI = srcImage(Range(20, 20 + logoImage.rows), Range(20, 20 + logoImage.cols));

	// 3. ���
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	// 4. ��ʾ
	namedWindow("<1>��������ͼ����");
	imshow("<1>��������ͼ����", srcImage);

	return true;
}

/*-------------- ROI_AddImage() ---------------*/
// ���ø���Ȥ������ROIʵ��ͼ�����
bool ROI_AddImage()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\4.jpg");
	Mat logoImage = imread("..\\..\\picture\\sound.png");
	
	// 2. ����һ��Mat���趨ROI����
	Mat imageROI = srcImage(Rect(20, 30, logoImage.cols, logoImage.rows));

	// 3. ������ģ(ע: �����ǻҶ�ͼ)
	Mat mask = imread("..\\..\\picture\\sound.", 0);

	// 4. ����ģ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);

	// 5. Display
	namedWindow("<2>����ROIʵ��ͼ�����ʾ������");
	imshow("<2>����ROIʵ��ͼ�����ʾ������", srcImage);

	return true;
}

/*------------ LinearBlending() -------------*/
// ����cv::addWdighted()ʵ��ͼ�����Ի��

bool LinearBlending()
{
	// ��������
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage1, srcImage2, dstImage;

	// 1. Load image (ע: ��ͼƬ����ͬ����, ͬ�ߴ�)
	srcImage1 = imread("F:\\��ֽ\\benbenla-06c.jpg");
	srcImage2 = imread("F:\\��ֽ\\background.jpg");
	if (!srcImage1.data | !srcImage2.data)
		return -1;

	// 2. ����ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0.0, dstImage);
	
	// 3. ��ʾ
	//namedWindow("<3.0>ԭͼ");
	//imshow("<3.0>ԭͼ", srcImage1);

	namedWindow("<3.1>���Ի��");
	imshow("<3.1>���Ի��", dstImage);

	return true;
}