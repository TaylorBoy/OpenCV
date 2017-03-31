/*
	ʹ�ö���ν�������Χ:

	1) �����ⲿ���α߽�: Rect boundintRect(InputArray points)

	2) Ѱ����С��Χ����: RotatedRect minAreaRect(InputArray points)

	3) Ѱ����С��ΧԲ��: void minEnclosingCircle(InputArray points, Point2f& center, float& radius);

	4) ����Բ��϶�ά�㼯: RotatedRect fitEllipse(InputArray points)

	5) �ƽ����������: void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed);
					   @param epsilon : �ƽ��ľ���
					   @param closed  : ���Ƶ������Ƿ�Ϊ�������(��һ����������һ����������)
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image(600, 600, CV_8UC3);
	RNG rng = theRNG();

	while (true)
	{
		int count = rng.uniform(3, 103);   // ������ɵ���
		vector<Point> points;  // ��ֵ

		// ������ɵ�����
		for (int i = 0; i < count; ++i)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		// �Ը�����2D�㼯, Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		// ���������ɫ�ĵ�
		image = Scalar::all(0);
		for (int i = 0; i < count; ++i)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		// ���Ƴ���С����İ�Χ����
		for (int i = 0; i < 4; ++i)
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		
		imshow("���ΰ�Χʾ��", image);

		char key = (char)waitKey(0);
		if ('q' == key)
			break;
	}

	return 0;
}