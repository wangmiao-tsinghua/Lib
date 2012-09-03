#include "logger.h"
#include "array.h"
#include "min_heap.h"
#include "iostream"


#include "image_kit.h"

int main()
{

/****************	Logger   *********************/
	Logger::init("Logger.log",1,1);
	Logger::demo();

/****************	array	 *********************/
	util::array::Array<int> a;
	a.demo();

/****************  MinHeap   *********************/
	util::heap::MinHeap<int,int> h;
	h.demo();


/***************   image_kit  *********************/

	//Rotate at (0,0) ANTI-clockwise
	Mat _973 = imread("973.jpg");
	_973.convertTo(_973, CV_32F , 1/255.0);
	SHOW_IMG("test",_973);
	Mat _973_out;
	for( int i =0; i < 12 ; ++i)
	{
		image_kit::ik_rotate(_973 , -i*2*CV_PI/12, 1, image_kit::IK_BILINEAR, _973_out);
		SHOW_IMG("test",_973_out);
	}
	return 0;

}