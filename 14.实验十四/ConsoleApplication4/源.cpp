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

#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h> 

int main(void)
{
	int i = 40;
	IplImage *img = cvLoadImage("6013202130.bmp", 0);
	IplImage *imga = cvLoadImage("xibao.jpg", 0);
	
	IplImage *oo_fushi = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage *oo_pengzhang = cvCreateImage(cvGetSize(img), 8, 1);

	IplImage *oo_kai = cvCreateImage(cvGetSize(imga), 8, 1);
	IplImage *oo_bi = cvCreateImage(cvGetSize(imga), 8, 1);

	cvErode(img, oo_fushi, NULL, 1); //��ʴͼ��
	cvDilate(img, oo_pengzhang, NULL, 1); //����ͼ��
	cvMorphologyEx(imga, oo_kai, NULL, NULL, CV_MOP_OPEN,1);//������
	cvMorphologyEx(imga, oo_bi, NULL, NULL, CV_MOP_CLOSE,3);//������
	
	


	cvNamedWindow("ԭͼ");
	cvNamedWindow("��ʴ��");
	cvNamedWindow("���ͺ�");
	cvNamedWindow("�������");
	cvNamedWindow("�������");
	

	cvShowImage("ԭͼ",img);
	cvShowImage("��ʴ��", oo_fushi);
	cvShowImage("���ͺ�", oo_pengzhang);
	cvShowImage("�������", oo_kai);
	cvShowImage("�������", oo_bi);


	cvWaitKey(-1);


	cvReleaseImage(&oo_pengzhang);
	cvReleaseImage(&oo_fushi);
	cvReleaseImage(&oo_kai);
	cvReleaseImage(&oo_bi);

	cvDestroyAllWindows();


	return 0;
}