/*
	使用多边形将轮廓包围:

	1) 返回外部矩形边界: Rect boundintRect(InputArray points)

	2) 寻找最小包围矩形: RotatedRect minAreaRect(InputArray points)

	3) 寻找最小包围圆形: void minEnclosingCircle(InputArray points, Point2f& center, float& radius);

	4) 用椭圆拟合二维点集: RotatedRect fitEllipse(InputArray points)

	5) 逼近多边形曲线: void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed);
					   @param epsilon : 逼近的精度
					   @param closed  : 近似的曲线是否为封闭曲线(第一个顶点和最后一个顶点相连)
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
		int count = rng.uniform(3, 103);   // 随机生成点数
		vector<Point> points;  // 点值

		// 随机生成点坐标
		for (int i = 0; i < count; ++i)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		// 对给定的2D点集, 寻找最小面积的包围矩形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		// 绘制随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; ++i)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		// 绘制出最小面积的包围矩形
		for (int i = 0; i < 4; ++i)
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		
		imshow("矩形包围示例", image);

		char key = (char)waitKey(0);
		if ('q' == key)
			break;
	}

	return 0;
}