/**********************************************************************************************************
 *  opencv ѧϰ �� 2016��3��15��20:10:06

1. ͼ�����뺯��
����cvLoadImage����ָ��ͼ���ļ���������ָ����ļ���IplImageָ�롣����֧��bmp��jpg�� png�� tiff�ȸ�ʽ��ͼ���亯��ԭ�����£�
IplImage* cvLoadImage( const char* filename, int iscolor);
���У�filename �Ǵ�����ͼ������ƣ�����ͼ�����չ����iscolor��һ�������������ѡ��������͸�������ֵ��������ʾ��Ϊ��ͨ��ͼ�����룬���ʾ��ͼ����Ϊ��ͨ��ͼ�񣬸�����ʾ����ͼ���ͨ������ͼ���ļ����������
2. ���ڶ��庯��
����cvNamedWindow����һ�����ڣ�������ʾͼ���亯��ԭ�����£�
int cvNamedWindow( const char* name, unsigned long flags );
���У�name�Ǵ�������flags�Ǵ�������ָ��ֵ������ѡ��CV_WINDOW_AUTOSIZE��0����ֵ��CV_WINDOW_AUTOSIZE��ʾ���ڳߴ���ͼ��ԭʼ�ߴ���ͬ��0��ʾ�Թ̶��Ĵ��ڳߴ���ʾͼ��
3. ͼ����ʾ����
����cvShowImage����ָ���Ĵ�������ʾͼ���亯��ԭ�����£�
void cvShowImage( const char* name, const CvArr* image );
���У�name�Ǵ������ƣ�image��ͼ������ָ�룬һ����IplImageָ�롣
4. ͼ�񱣴溯��
����cvSaveImage��ָ�����ļ�������IplImage���͵�ָ��������亯��ԭ�����£�
int cvSaveImage( const char* filename, const CvArr* image );
���У�filename��ͼ�񱣴�·�������ƣ�image��IplImageָ�������
5. ͼ�����ٺ���
����cvReleaseImage�����Ѷ����IplImageָ��������ͷ�ռ���ڴ�ռ䡣�亯��ԭ�����£�
void cvReleaseImage( IplImage** image );
���У�imageΪ�Ѷ����IplImageָ�롣
6. ͼ��ת������
cvGetImage( const CvArr* arr, IplImage* image_header )
7.����һ�����ڡ�
void cvDestroyWindow( const char* name );
 ***********************************************************************************************************/


#include <cv.h>
#include <highgui.h> //ͼ����Ƶ���/����ͷ�ļ�
using namespace std;

IplImage* AddGuassianNoise(IplImage* src)    //��Ӹ�˹����
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	IplImage* noise = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	CvRNG rng = cvRNG(-1);
	cvRandArr(&rng, noise, CV_RAND_NORMAL, cvScalarAll(0), cvScalarAll(15));
	cvAdd(src, noise, dst);
	return dst;
}
IplImage* AddPepperNoise(IplImage* src)      //��Ӻ��������������ɫ��
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src, dst);
	for (int k = 0; k<8000; k++)
	{
		int i = rand() % src->height;
		int j = rand() % src->width;
		CvScalar s = cvGet2D(src, i, j);
		if (src->nChannels == 1)
		{
			s.val[0] = 0;
		}
		else if (src->nChannels == 3)
		{
			s.val[0] = 0;
			s.val[1] = 0;
			s.val[2] = 0;
		}
		cvSet2D(dst, i, j, s);
	}
	return dst;
}
IplImage* AddSaltNoise(IplImage* src)       //����������������ɫ��
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src, dst);
	for (int k = 0; k<8000; k++)
	{
		int i = rand() % src->height;
		int j = rand() % src->width;
		CvScalar s = cvGet2D(src, i, j);
		if (src->nChannels == 1)
		{
			s.val[0] = 255;
		}
		else if (src->nChannels == 3)
		{
			s.val[0] = 255;
			s.val[1] = 255;
			s.val[2] = 255;
		}
		cvSet2D(dst, i, j, s);
	}
	return dst;
}
IplImage* AddPepperSaltNoise(IplImage* src)    //��ӽ�������������ڰ׵�
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src, dst);
	for (int k = 0; k<8000; k++)
	{
		int i = rand() % src->height;
		int j = rand() % src->width;
		int m = rand() % 2;
		CvScalar s = cvGet2D(src, i, j);
		if (src->nChannels == 1)
		{
			if (m == 0)
			{
				s.val[0] = 255;
			}
			else
			{
				s.val[0] = 0;
			}
		}
		else if (src->nChannels == 3)
		{
			if (m == 0)
			{
				s.val[0] = 255;
				s.val[1] = 255;
				s.val[2] = 255;
			}
			else
			{
				s.val[0] = 0;
				s.val[1] = 0;
				s.val[2] = 0;
			}
		}
		cvSet2D(dst, i, j, s);
	}
	return dst;
}

//������ֵ�˲�������ģ���С5*5
IplImage* ArithmeticMeanFilter(IplImage* src)
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvSmooth(src, dst, CV_BLUR, 5);
	return dst;
}


int main()
{
	IplImage * test, *test_1, *test_2;
	test = cvLoadImage("6013202130.jpg",0);//ͼƬ·���� ConsoleApplication4 �ļ����ͬʱʵ��Ҫ��תΪ�Ҷ�ͼƬ
	test_1 = cvCreateImage(cvSize((test->width), (test->height)), IPL_DEPTH_8U, 1); //����ͼ�񣬸�ָ�븳ֵ
	test_2 = cvCreateImage(cvSize((test->width), (test->height)), IPL_DEPTH_8U, 1); //����ͼ�񣬸�ָ�븳ֵ
	test_2 = AddGuassianNoise(test);
	
	test_1 = ArithmeticMeanFilter(test_2);


	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", test);
	cvNamedWindow("�˲���", CV_WINDOW_AUTOSIZE);
	cvShowImage("�˲���", test_1);
	cvNamedWindow("������", CV_WINDOW_AUTOSIZE);
	cvShowImage("������", test_2);
	cvWaitKey(0);//�ȴ�����
	cvDestroyWindow("zhang_fei_1");
	cvDestroyWindow("zhang_fei_2");
	cvDestroyWindow("zhang_fei_3");
	cvReleaseImage(&test);//�ͷ��ڴ档 
	cvReleaseImage(&test_1);
	cvReleaseImage(&test_2);
	return 0;
}
