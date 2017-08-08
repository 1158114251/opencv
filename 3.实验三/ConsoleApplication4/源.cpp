/**********************************************************************************************************
 *  opencv ѧϰ �� 2016��4��1��21:47:28

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
*rotateImage(ԭͼ��, �Ƕ�) ������ת���ͼ��ָ��
 ***********************************************************************************************************/


#include <opencv/cv.h>
#include <opencv/highgui.h>

IplImage *rotateImage(const IplImage *src, int angleDegrees)
{
	IplImage *imageRotated = cvCloneImage(src);
	if (angleDegrees != 0){
		CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);
		CvPoint2D32f center = cvPoint2D32f(cvGetSize(imageRotated).width / 2, cvGetSize(imageRotated).height / 2);
		cv2DRotationMatrix(center, angleDegrees, 1, rot_mat);
		cvWarpAffine(src, imageRotated, rot_mat);
	}
	return imageRotated;
}


int main()
{

	IplImage* img;
	IplImage* rotated_img;
	int angle = 0;
		img = cvLoadImage("6013202130.jpg");
		rotated_img = rotateImage(img, 223);
		cvNamedWindow("ѡ��-ͼƬ��ת", CV_WINDOW_AUTOSIZE);
		cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
		cvShowImage("ԭͼ", img);
		cvShowImage("ѡ��-ͼƬ��ת", rotated_img);
		cvWaitKey(0);//�ȴ�����
		cvDestroyWindow("ԭͼ");
		cvDestroyWindow("ѡ��-ͼƬ��ת");
		cvReleaseImage(&img);
		cvReleaseImage(&rotated_img);

	return 0;
}
