#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	// 初始化矩阵
	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	// 1. OpenCV默认风格
	cout << "OpenCV: " << endl << r << endl;

	// 2. Python风格
	// OpenCV2: cout << "Python: " << endl << format(r, "python") << endl;
	cout << "Python: " << endl << format(r, Formatter::FMT_PYTHON) << endl;

	// 3. CSV, 逗号分隔风格
	cout << "CSV: " << endl << format(r, Formatter::FMT_CSV) << endl;

	// 4. Numpy风格
	cout << "Numpy:	" << endl << format(r, Formatter::FMT_NUMPY) << endl;

	// 5. C
	cout << "C: " << endl << format(r, Formatter::FMT_C) << endl;

	/* Other */
	// 6. 二维点
	Point2f p2f(6, 3);
	cout << endl << "二维点: " << p2f << endl;

	// 7. 三维点
	Point3f p3f(3, 4, 6);
	cout << "三维点: " << p3f << endl;

	// 8. 基于Mat的std::vector
	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	cout << "基于Mat的std::vector: " << endl << Mat(v) << endl;

	// 9. std::vector
	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "std::vector: " << endl << points << endl;



	waitKey(0);

	return 0; 
}