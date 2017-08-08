/**********************************************************************************************************
*  opencv ѧϰ �� 2016��3��24��18:30:08

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

8.cvCvtPixToPlane��openCV�����һ������
#define cvCvtPixToPlane cvSplit
void cvSplit( const CvArr* oo, CvArr* dst0, CvArr* dst1,CvArr* dst2, CvArr* dst3 );
�����ǣ��ָ��ͨ������ɼ�����ͨ��������ߴ���������ȡһ��ͨ��
һ���÷���cvCvtPixToPlane��IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,IplImage *dst4)
��һ��������Դͼ�񣬺����Ƿ������ÿ��ͨ����Ŀ��ͼ�����ԭͼ����3ͨ���ģ����԰����һ����������Ϊ�ա�����cvCvtPixToPlane��IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,NULL)��NULLҲ����дΪ0.
ʹ�øú��������#include<cv.h>ͷ�ļ�

9.CvSetImageCOI������ͼ���COI������Ȥͨ���� of interesting���ĺ�����
���ܣ�
����ͼ���COI������Ȥͨ���� of interesting��
��ʽ��
void cvSetImageCOI��IplImage* image,int coi����
����
image ͼ��ͷ,������ͼ��
coiΪ0ʱ��ʾѡ������ͨ����1��ʾ��һ��ͨ����2��ʾ�ڶ����ȵ�

10.cvCreateImage( CvSize size, int depth, int s );
�����׵�ַ������洢�ռ�,���ص��ǵ�ַ��


***********************************************************************************************************/



/*
      2016��4��13��21:07:50��дopencv��ȡÿ�����ص��rgbֵ����ͨ����ʽת����hsiȻ�������ͼ��
	  ��д��һ���Ӻ���rgbת��Ϊhsi�Ĺ�ʽ��


*/

#include <cv.h>
#include <highgui.h> 
# include <math.h>
#define M_PI 3.1415
void RGB_to_HSI(IplImage *src, IplImage *dst);
int main(void)
{
	IplImage * oo  = cvLoadImage   ("6013202130.jpg", 1);
	IplImage * xx  = cvCreateImage  (cvGetSize(oo), 8, 1);
	RGB_to_HSI(oo, xx);
	cvNamedWindow("ԭͼ", 1);
	cvNamedWindow("HSI", 1);
	cvShowImage("ԭͼ", oo);
	cvShowImage("HSI" , xx);
	cvWaitKey(0);
	cvReleaseImage(&xx);
	cvReleaseImage(&oo);
	return 0;
}

void RGB_to_HSI(IplImage *src, IplImage *dst)
{
	int i, j;
	double b, g, r, numm, den, min, theta, H, S, I;
	CvScalar s0;
	for (i = 0; i<src->height; i++)
	for (j = 0; j<src->width; j++)
	{

		s0 = cvGet2D(src, i, j);
		b = s0.val[0] / 255;//rgb��һ��
		g = s0.val[1] / 255;
		r = s0.val[2] / 255;
		//�����Ƶ���ת��
		numm = 0.5*((r - g) + (r - b));
		den = sqrt((r - g)*(r - g) + (r - b)*(g - b));
		if (den == 0)
			H = 0;
		else
		{
			theta = acos(numm / den);
			if (b>g)
				H = (2 * M_PI - theta) / (2 * M_PI);
			else
				H = theta / (2 * M_PI);
		}
		min = (b>g) ? g : b;
		min = (min>r) ? r : min;
		den = r + g + b;
		if (den == 0)
			S = 0;
		else
			S = 1 - 3 * min / den;
		I = (r + g + b) / 3;
		cvSet2D(dst, i, j, cvScalar(H * 180, S * 255, I * 255));
	}
}

















