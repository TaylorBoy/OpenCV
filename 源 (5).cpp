/*
	1. ����ƥ���: drawMatches()
	�汾1: void drawMatches(
	            const Mat& img1,
	            const vector<KeyPoint>& keypoints1,
				const Mat& img2,
				const vector<KeyPoint>& keypoints2,
				const vector<DMatch>& matches1to2,
				Mat& outImg,
				const Scalar& matchColor=Scalar::all(-1),
				const Scalar& singlePointColor=Scalar::all(-1),
				const vector<char>& matchesMask=vector<char>(),
				int flags=DrawMatchesFlags::DEFAULT
			)
	�汾2: void drawMatches(
	            const Mat& img1,
				const vector<KeyPoint>& keypoints1,
				const Mat& img2,
				const vector<KeyPoint>& keypoints2,
				const vector<vector<DMatch> >& matches1to2,  // **
				Mat& outImg,
				const Scalar& matchColor=Scalar::all(-1),
				const Scalar& singlePointColor=Scalar::all(-1),
				const vector<vector<char> >& matchesMask=vector<vector<char> >(),  // **
				int flags=DrawMatchesFlags::DEFAULT
		   )
		   @param img1       : ��һ��Դͼ
		   @param keypoints1 : �������, ���ݵ�һ��Դͼ�õ���������
		   @param img2       : �ڶ���Դͼ
		   @param keypoints2 : �������, ���ݵڶ���Դͼ�õ���������
		   @param mathces1to2      : ��һ��ͼ���ڶ���ͼ��ƥ���(һһ��Ӧ)
		   @param outImg           : ���ͼ��, ȡ����flags
		   @param matchColor       : ƥ��������ɫ, ���ߺ͹ؼ������ɫ, Ĭ�����
		   @param singlePointColor : ��һ���������ɫ
		   @param matchesMask      : ȷ����Щƥ���ǻ���Ƴ�������Ĥ, Ϊ�ձ�ʾȫ�����л���
		   @param flags            : �������Ʊ�ʶ��.

	2. BruteForceMatcher���õ�����match(), �Ǵ�DescriptorMatcher��̳ж�����
	   //  Ϊ�����������ҵ�һ����ѵ�ƥ��(����ĤΪ��)
	       CV_WRAP void match(
		       const Mat& queryDescriptors, 
		       const Mat& trainDescriptors, 
		       CV_OUT vector<DMatch>& matches, 
		       const Mat& mask=Mat() 
	       )const;
*/

// ʹ��DescriptorExtractor�ӿ���Ѱ�ҹؼ����Ӧ����������
// ʹ��SurfDescriptorExtractor�Լ����ĺ���compute()������ض��ļ���
// ʹ��BruteForceMatcher��ƥ����������
// ʹ��drawMatches()�����Ƽ�⵽��ƥ���

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	// 1. ����ͼ��
	Mat srcImage1 = imread("1.jpg", IMREAD_COLOR);
	Mat srcImage2 = imread("2.jpg", IMREAD_COLOR);
	if (!srcImage1.data || !srcImage2.data) return -1;

	// 2. ʹ��SURF���Ӽ��ؼ���
	int minHessian = 700;   // hessian��ֵ
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keyPoint1, keyPoint2;

	// 3. ����detect()����SURF�����ؼ���, ������vector������
	detector.detect(srcImage1, keyPoint1);
	detector.detect(srcImage2, keyPoint2);

	// 4. ����������(��������)
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage1, keyPoint1, descriptors1);
	extractor.compute(srcImage2, keyPoint2, descriptors2);

	// 5. ʹ��BruteForce����ƥ��

	// ʵ����һ��ƥ����
	BruteForceMatcher<L2<float> > matcher;
	vector<DMatch> matches;
	// ƥ������ͼ�е�������(Descriptor)
	matcher.match(descriptors1, descriptors2, matches);

	// 6. ���ƴ�����ͼ����ƥ������Ĺؼ���
	Mat imgMatches;
	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches, Scalar::all(-1), Scalar(0, 0, 255));

	imshow("ƥ��ͼ", imgMatches);

	waitKey(0);

	return 0;
}
