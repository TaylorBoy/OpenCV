/*
	Ѱ��͹��: convexHull()
	ԭ��: void concexHull(InputArray points, OutputArray hull, bool clockwize=false, bool returPoints=true);
	      @param points : Mat��vector�Ķ�ά�㼯
		  @param hull   : ͹��
		  @param clockwise    : ˳ʱ�뷽��, ���������־
		  @param returnPoints : ������ʶ. ��Ϊ��, �������ظ�͹���ĸ�����; ����, ����͹�������ָ��; �����Ϊvectorʱ, �˱�־����.
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main()
{
	// Init.
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while (true)
	{
		// ������ʼ��
		char key;
		int count = (unsigned)rng % 100 + 3;   // ������ɵ�����
		std::vector<Point> points;  // ��ֵ

		// ������ɵ�����
		for (int i = 0; i < count; ++i)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		// ���͹��
		std::vector<int> hull;
		convexHull(Mat(points), hull, true);

		// ������ɫ����ĵ�
		image = Scalar::all(0);
		for (int i = 0; i < count; ++i)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		// ׼������
		int hullcount = (int)hull.size();				// ͹���ı���
		Point point0 = points[hull[hullcount - 1]];		// ����͹���������

		// ���͹���ı�
		for (int i = 0; i < hullcount; ++i)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
			point0 = point;
		}

		// Display
		imshow("͹�����ʾ��", image);

		key = (char)waitKey();
		if (27 == key || 'q' == key || 'Q' == key)
			break;
	}

	return 0;
}