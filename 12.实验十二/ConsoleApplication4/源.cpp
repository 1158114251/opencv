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
#define GrayScale 256   //frame�Ҷȼ�   
int mytsu( IplImage *frame);
int main()
{
	int a=0;
	 IplImage * test;
	IplImage * test_1;
	test = cvLoadImage("6013202130.bmp", 0);//ͼƬ·���� ConsoleApplication4 �ļ����ͬʱʵ��Ҫ��תΪ�Ҷ�ͼƬ
	test_1 = cvCreateImage(cvSize((test->width), (test->height)), IPL_DEPTH_8U, 1); //����ͼ�񣬸�ָ�븳ֵ
	a= mytsu(test);
	CvScalar s;

	for (int i = 0; i < test->height; i++)
	{

		for (int j = 0; j < test->width; j++)
		{
			s = cvGet2D(test, i, j);
			if (s.val[0] >a)
				s.val[0] = 255;
			else
				s.val[0] = 0;
			cvSet2D(test_1, i, j, s);

		}


	}

	cvNamedWindow("ԭͼ��6013202130", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ��6013202130", test);
	cvNamedWindow("�����任��6013202130", CV_WINDOW_AUTOSIZE);
	cvShowImage("�����任��6013202130", test_1);
	cvWaitKey(0);//�ȴ�����
	cvDestroyWindow("ԭͼ��6013202130");
	cvDestroyWindow("�����任��6013202130");
	cvReleaseImage(&test);//�ͷ��ڴ档 
	cvReleaseImage(&test_1);

	return 0;
}



int mytsu( IplImage *frame) //�������ֵ   
{

	int width = frame->width;
	int height = frame->height;
	int pixelCount[GrayScale] = { 0 };
	float pixelPro[GrayScale] = { 0 };
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)frame->imageData;

	//ͳ��ÿ���Ҷȼ������صĸ���   
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}

	//����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���   
	for (i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}

	//�����Ҷȼ�[0,255],Ѱ�Һ��ʵ�threshold   
	float w0, w1, u0tmp, u1tmp, u0, u1, deltaTmp, deltaMax = 0;
	for (i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = deltaTmp = 0;
		for (j = 0; j < GrayScale; j++)
		{
			if (j <= i)   //��������   
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   //ǰ������   
			{
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}
		u0 = u0tmp / w0;
		u1 = u1tmp / w1;
		deltaTmp = (float)(w0 *w1* pow((u0 - u1), 2));
		if (deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	return threshold;
}