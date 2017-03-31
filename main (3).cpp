#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
	// 改变console字体颜色
	system("color 6F");

	// 1. 初始化
	FileStorage fs("test.yaml", FileStorage::READ);

	// 2.1 方法一: 对FileNode操作
	int frameCount = (int)fs["frameCount"];

	// 2.2 方法二: 使用FileNode运算符 >>
	std::string date;
	fs["calibratoinDate"] >> date;

	Mat cameraMatrix, distCoeffs;
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;

	cout << "frameCount: " << frameCount << endl;
	cout << "Calibration date: " << date << endl;
	cout << "cameraMatrix: " << cameraMatrix << endl;
	cout << "distCoeffs: " << distCoeffs << endl;


	// 关闭文件
	fs.release();

	waitKey(0);

	return 0;
}