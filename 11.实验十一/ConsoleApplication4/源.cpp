/**********************************************************************************************************
 *  opencv 学习 ： 2016年3月15日20:10:06

1. 图像载入函数
函数cvLoadImage载入指定图像文件，并返回指向该文件的IplImage指针。函数支持bmp、jpg、 png、 tiff等格式的图像。其函数原型如下：
IplImage* cvLoadImage( const char* filename, int iscolor);
其中，filename 是待载入图像的名称，包括图像的扩展名；iscolor是一个辅助参数项，可选正数、零和负数三种值，正数表示作为三通道图像载入，零表示该图像作为单通道图像，负数表示载入图像的通道数由图像文件自身决定。
2. 窗口定义函数
函数cvNamedWindow定义一个窗口，用于显示图像。其函数原型如下：
int cvNamedWindow( const char* name, unsigned long flags );
其中，name是窗口名，flags是窗口属性指标值，可以选择CV_WINDOW_AUTOSIZE和0两种值。CV_WINDOW_AUTOSIZE表示窗口尺寸与图像原始尺寸相同，0表示以固定的窗口尺寸显示图像。
3. 图像显示函数
函数cvShowImage是在指定的窗口中显示图像，其函数原型如下：
void cvShowImage( const char* name, const CvArr* image );
其中，name是窗口名称，image是图像类型指针，一般是IplImage指针。
4. 图像保存函数
函数cvSaveImage以指定的文件名保存IplImage类型的指针变量，其函数原型如下：
int cvSaveImage( const char* filename, const CvArr* image );
其中，filename是图像保存路径和名称，image是IplImage指针变量。
5. 图像销毁函数
函数cvReleaseImage销毁已定义的IplImage指针变量，释放占用内存空间。其函数原型如下：
void cvReleaseImage( IplImage** image );
其中，image为已定义的IplImage指针。
6. 图像转换函数
cvGetImage( const CvArr* arr, IplImage* image_header )
7.销毁一个窗口。
void cvDestroyWindow( const char* name );
 ***********************************************************************************************************/


#include <cv.h>
#include <highgui.h> //图像视频输出/输入头文件
using namespace std;

IplImage* AddGuassianNoise(IplImage* src)    //添加高斯噪声
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	IplImage* noise = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	CvRNG rng = cvRNG(-1);
	cvRandArr(&rng, noise, CV_RAND_NORMAL, cvScalarAll(0), cvScalarAll(15));
	cvAdd(src, noise, dst);
	return dst;
}
IplImage* AddPepperNoise(IplImage* src)      //添加胡椒噪声，随机黑色点
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
IplImage* AddSaltNoise(IplImage* src)       //添加盐噪声，随机白色点
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
IplImage* AddPepperSaltNoise(IplImage* src)    //添加椒盐噪声，随机黑白点
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

//算术均值滤波器——模板大小5*5
IplImage* ArithmeticMeanFilter(IplImage* src)
{
	IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvSmooth(src, dst, CV_BLUR, 5);
	return dst;
}


int main()
{
	IplImage * test, *test_1, *test_2;
	test = cvLoadImage("6013202130.jpg",0);//图片路径是 ConsoleApplication4 文件夹里，同时实验要求转为灰度图片
	test_1 = cvCreateImage(cvSize((test->width), (test->height)), IPL_DEPTH_8U, 1); //创建图像，给指针赋值
	test_2 = cvCreateImage(cvSize((test->width), (test->height)), IPL_DEPTH_8U, 1); //创建图像，给指针赋值
	test_2 = AddGuassianNoise(test);
	
	test_1 = ArithmeticMeanFilter(test_2);


	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", test);
	cvNamedWindow("滤波后", CV_WINDOW_AUTOSIZE);
	cvShowImage("滤波后", test_1);
	cvNamedWindow("噪声后", CV_WINDOW_AUTOSIZE);
	cvShowImage("噪声后", test_2);
	cvWaitKey(0);//等待按键
	cvDestroyWindow("zhang_fei_1");
	cvDestroyWindow("zhang_fei_2");
	cvDestroyWindow("zhang_fei_3");
	cvReleaseImage(&test);//释放内存。 
	cvReleaseImage(&test_1);
	cvReleaseImage(&test_2);
	return 0;
}
