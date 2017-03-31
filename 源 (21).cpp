/*
	寻找凸包: convexHull()
	原型: void concexHull(InputArray points, OutputArray hull, bool clockwize=false, bool returPoints=true);
	      @param points : Mat或vector的二维点集
		  @param hull   : 凸包
		  @param clockwise    : 顺时针方向, 操作方向标志
		  @param returnPoints : 操作标识. 若为真, 函数返回各凸包的各个点; 否则, 返回凸包各点的指数; 当输出为vector时, 此标志忽略.
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
		// 参数初始化
		char key;
		int count = (unsigned)rng % 100 + 3;   // 随机生成点数量
		std::vector<Point> points;  // 点值

		// 随机生成点坐标
		for (int i = 0; i < count; ++i)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		// 检测凸包
		std::vector<int> hull;
		convexHull(Mat(points), hull, true);

		// 绘制颜色随机的点
		image = Scalar::all(0);
		for (int i = 0; i < count; ++i)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		// 准备参数
		int hullcount = (int)hull.size();				// 凸包的边数
		Point point0 = points[hull[hullcount - 1]];		// 连接凸包的坐标点

		// 检测凸包的边
		for (int i = 0; i < hullcount; ++i)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
			point0 = point;
		}

		// Display
		imshow("凸包检测示例", image);

		key = (char)waitKey();
		if (27 == key || 'q' == key || 'Q' == key)
			break;
	}

	return 0;
}