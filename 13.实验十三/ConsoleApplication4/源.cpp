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

对灰度图使用Laplacian算子:

Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
函数接受了以下参数:

src_gray: 输入图像。
dst: 输出图像
ddepth: 输出图像的深度。 因为输入图像的深度是 CV_8U ，这里我们必须定义 ddepth = CV_16S 以避免外溢。
kernel_size: 内部调用的 Sobel算子的内核大小，此例中设置为3。
scale, delta 和 BORDER_DEFAULT: 使用默认值。
 ***********************************************************************************************************/

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst, src_gray, abs_dst;

	Mat src = imread("6013202130.jpg");  //工程目录下应该有一张名为1.jpg的素材图

	imshow("【原始图】sobel边缘检测", src);

	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("【效果图】整体方向Sobel", dst);

	

	
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, CV_RGB2GRAY);

	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	convertScaleAbs(dst, abs_dst);

	imshow("【效果图】图像Laplace变换", abs_dst);





	waitKey(0);
	return 0;
}