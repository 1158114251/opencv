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


#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage;     // 全局的源图像
// 分别对应全局的方框滤波、均值滤波、高斯滤波、中值滤波、双边滤波的输出图像以及内核值/参数值
Mat g_dstImgBox, g_dstImgBlur, g_dstImgGaussian, g_dstImgMedian, g_dstImgBilateral;
int g_BoxFilterVal = 5;
int g_BlurVal = 12;
int g_GaussianBlurVal = 5;
int g_MedianBlurVal = 12;
int g_BilateralFilterVal = 12;

static void on_BoxFilter(int, void *);
static void on_Blur(int, void *);
static void on_GaussianBlur(int, void *);
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void*);

int main()
{
	// 读取图像到g_srcImage
	g_srcImage = imread("6013202130.jpg");
	if (!g_srcImage.data) {
		printf("读取的图片不存在…… \n");
		return false;
	}

	// 分别克隆原图到5中滤波所需的图像中，均为Mat类型
	g_dstImgBox = g_srcImage.clone();
	g_dstImgBlur = g_srcImage.clone();
	g_dstImgGaussian = g_srcImage.clone();
	g_dstImgMedian = g_srcImage.clone();
	g_dstImgBilateral = g_srcImage.clone();

	// 显示原图
	namedWindow("【原图】", 1);
	imshow("【原图】", g_srcImage);

	
	namedWindow("【均值滤波】", 1);
	createTrackbar("内核值", "【均值滤波】", &g_BlurVal, 30, on_Blur);
	on_Blur(g_BlurVal, 0);

	namedWindow("【高斯滤波】", 1);
	createTrackbar("内核值", "【高斯滤波】", &g_GaussianBlurVal, 30, on_GaussianBlur);
	on_GaussianBlur(g_GaussianBlurVal, 0);

	namedWindow("【中值滤波】", 1);
	createTrackbar("内核值", "【中值滤波】", &g_MedianBlurVal, 30, on_MedianBlur);
	on_MedianBlur(g_MedianBlurVal, 0);

	

	cout << "按下“q”键时，程序退出……\n";
	while (char(waitKey(1)) != 'q') {}

	return 0;
}



static void on_Blur(int, void *)
{
	blur(g_srcImage, g_dstImgBlur, Size(g_BlurVal + 1, g_BlurVal + 1),
		Point(-1, -1));
	imshow("【均值滤波】", g_dstImgBlur);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImgGaussian, Size(g_GaussianBlurVal * 2 + 1,
		g_GaussianBlurVal * 2 + 1), 0, 0);
	imshow("【高斯滤波】", g_dstImgGaussian);
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImgMedian, g_MedianBlurVal * 2 + 1);
	imshow("【中值滤波】", g_dstImgMedian);
}

