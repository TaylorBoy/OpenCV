#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void createAlphaMat(Mat &mat)
{
	for (int i = 0; i < mat.rows; ++i)
	{
		for (int j = 0; j < mat.cols; ++j)
		{
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j))) / ((float(mat.cols) * UCHAR_MAX));
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i))) / ((float(mat.rows) * UCHAR_MAX));
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}


int main()
{
	// 创建带alpha通道的Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int> compression_params;
	// OpenCV3
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try{
		// bool imwrite(const string% filename, InputArray img, const vector<int>& params=vector<int>());
		// 1. 对于JPEG格式, params表示0-100的图片质量, 默认为95
		// 2. 对于PNG格式, params表示0-9的压缩级别, 默认为3
		// 3. 对于ppm,pgm,pbm, params表示0或1的二进制格式标志, 默认为1
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生成的图", mat);
		fprintf(stdout, "图片数据保存完毕~~");
		waitKey(0);
	}
	catch (runtime_error& ex){
		fprintf(stderr, "图片数据保存失败: %s", ex.what());
		return 1;
	}

	return 0;
}