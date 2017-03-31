/*
	����任 Huogh Transform:
	HoughLines() : ��׼����任, StandardHough Transform, SHT.
	               ��߶Ȼ���任, Multi-ScaleHough Transform, MSHT.
	HoughLinesP(): �ۼƸ��ʻ���任, ProgressiveProbabilistic Hough Transform, PPHT

	����: �����߱任��ֱ������ֻ���Ǳ�Ե��ֵͼ��.

	��׼����ԭ��: void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0);
	      @image : 8λ��ͨ��������ͼ��.
		  @lines : ÿ����������ʸ��(��, ��)(������)
		  @rho   : ������Ϊ��λ�ľ��뾫��(��)
		  @theta : �Ի���Ϊ��λ�ĽǶȾ���
		  @threshold: �ۼ�ƽ�����ֵ����, ������ֵ���߲���Ϊ���.
		  @srn : ���ڶ�߶Ȼ���任, Ϊrho�ĳ�������(���Ե��ۼӽ����ߴ�Ϊrho, ��ȷΪrho/srn)
		  @stn : ���ڶ�߶Ȼ���任, Ϊtheta�ĳ�������. ��srn=stn=0, ��ʹ�þ������任, ����srn��stnΪ����.

	���ʻ���ԭ��: void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0);
	      @lines : �洢��⵽����, ÿ����4��ʸ��, (x_1,y_1)��(x_2,y_2)Ϊ�߶εĽ�����.
		  @minLineLength : ����߶εĳ���
		  @maxLineGap    : ����ͬһ�е����֮������������������
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

#if (1)
int main()
{
	Mat srcImage = imread("..\\..\\picture\\22.jpg");
	Mat midImage, dstImage;

	// ��Ե���, ת�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	// ���л����߱任
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	
	// �����߶�
	for (size_t i = 0; i < lines.size(); ++i)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		// OpenCV2
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}

	// ��ʾԭͼ \ ��Ե���ͼ \ Ч��ͼ
	imshow("Src Image", srcImage);
	imshow("Canny", midImage);
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}
#endif

// HoughLinesP() �ۼƸ��ʻ���任
#if (0)
int main()
{
	Mat srcImage = imread("..\\..\\picture\\21.jpg");
	Mat midImage, dstImage;

	// ���б�Ե���, תΪ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	// ���л����߱任
	vector<Vec4i> lines;   // ����һ��lines��ŵõ����߶�ʸ������
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	// ������;�л��ÿ���߶�
	for (size_t i = 0; i < lines.size(); ++i)
	{
		Vec4i l = lines[i];

		// OpenCV2
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 15, 153), 1, CV_AA);

		// OpenCV3
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);		
	}

	// ��ʾԭͼ \ ��Ե���ͼ \ Ч��ͼ
	imshow("Src Image", srcImage);
	imshow("Canny", midImage);
	imshow("Result", dstImage);

	waitKey(0);

	return 0;
}

#endif
