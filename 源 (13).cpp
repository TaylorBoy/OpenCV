/*
	1. ����ֱ��ͼ(Histogram): calcHist()
	ԭ��: void calcHist(const Mat* image, int nimages, const int* channels, InputArray mask, OutputArray hist,
					    int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false);
		  @param images   : ��������(CV_8U / CV32F)
		  @param nimages  : �����������
		  @param channels : ��Ҫͳ�Ƶ�ͨ��(dim)����[��һ������: 0~images[0].channels()-1]
		  @param mask     : ��ѡ����(8λ)
		  @param hist     : �������
		  @param dims     : ��Ҫ�����ֱ��ͼά��, ������CV_MAX_DIMS(32)
		  @param histSize : ���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		  @param ranges   : ÿһά�������ȡֵ��Χ
		  @param uniform  : ָʾֱ��ͼ�Ƿ����
		  @param accumulate : �ۼƱ�ʶ��, trueʱֱ��ͼ�����ýضϲ��ᱻ����

	2. Ѱ����ֵ: minMaxLoc()
	ԭ��: void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray());
		  @param src : ����ĵ�ͨ������
		  @param minVal : ������Сֵ��ָ��
		  @param maxVal : �������ֵ��ָ��
		  @param minLoc : ������Сλ�õ�ָ��
		  @param maxLoc : �������λ�õ�ָ��
		  @param mask   : ��ѡ��Ĥ
		  
	3. ����:
		  dims : ��Ҫͳ�Ƶ�������Ŀ, ��Ҷ�ͼdims = 1
		  bins : ÿ�������ռ������ε���Ŀ, ��ֱ������Ŀ
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. ����ԭͼ, תΪHSV��ɫģ��
	Mat srcImage, hsvImage;
	srcImage = imread("..\\..\\picture\\31.jpg");
	if (!srcImage.data) return -1;

	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	// 2. ����׼��

	//    ��ɫ������Ϊ30���ȼ�, �����Ͷ�����Ϊ32���ȼ�
	int hueBinNum = 30;          // ɫ��ֱ��ͼ������
	int staturationBinNum = 32;  // ���Ͷ�����
	int histSize[] = { hueBinNum, staturationBinNum };
	//    ����ɫ���任��Χ: 0-179
	float hueRanges[] {0, 180};
	//    ���履�Ͷȱ仯��Χ0-255
	float staturationRanges[] = { 0, 255 };
	const float* ranges[] = { hueRanges, staturationRanges };
	MatND dstHist;

	//    �����0�͵�1ͨ����ֱ��ͼ
	int channels[] = { 0, 1 };

	// 3. ��ʽ����calcHist()
	calcHist(&hsvImage,
		1,           // �������Ϊ1
		channels,    // ͨ������
		Mat(),       // ��ʹ����Ĥ
		dstHist,     // ���Ŀ��
		2,           // ��Ҫ�����ֱ��ͼ��ά��
		histSize,    // ���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges,      // ÿ��ά�������ȡֵ��Χ
		true,        // ���ȵ�ֱ��ͼ
		false);      // ���ۼ�, ����

	// 4. Ϊ����ֱ��ͼ׼������
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	int scale = 10;
	Mat histImg = Mat::zeros(staturationBinNum * scale, hueBinNum * 10, CV_8UC3);

	// 5. ����ֱ��ͼ
	for (int hue = 0; hue < hueBinNum; ++hue)
	{
		for (int staturation = 0; staturation < staturationBinNum; ++staturation)
		{
			float binValue = dstHist.at<float>(hue, staturation);  // ֱ��ͼ��ֵ
			int intensity = cvRound(binValue * 255 / maxValue);    // ǿ��

			// ��ʽ����
			rectangle(histImg, Point(hue * scale, staturation * scale), Point((hue + 1) * scale - 1, (staturation + 1) * scale - 1),
				Scalar::all(intensity), FILLED);
		}
	}

	imshow("�ز�ͼ", srcImage);
	imshow("H-Sֱ��ͼ", histImg);

	waitKey(0);
}

