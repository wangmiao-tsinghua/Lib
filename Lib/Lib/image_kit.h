#ifndef IMAGE_KIT_H_
#define IMAGE_KIT_H_

#include "global_header.h"
namespace image_kit{

	//Interpolate method
	//nearest or bilinear
	enum IK_METHOD_INTERP
	{
		IK_NEAREST=0,
		IK_BILINEAR
	};
	
	//Bilinear interpolate a point from an image32FC1
	//PARAM INPUT
	//	@ img32FC1	:	image with float type
	//  @ x		:   x-coordinate
	//	@ y		:	y-coordinate
	//PARAM OUTPUT NULL 
	//RETURN
	//	the interpolation result
	inline float ik_bilinearInterp(const Mat & img32FC1, float x, float y)
	{
		int x1 = int(x), x2 = x1+1, y1=int(y), y2=y1+1;
		float fx1y1 = img32FC1.at<float>(y1,x1);
		float fx1y2 = img32FC1.at<float>(y2,x1);
		float fx1 = fx1y1 + (fx1y2-fx1y1)*(y-y1)/(y2-y1);

		float fx2y1 = img32FC1.at<float>(y1,x2);
		float fx2y2 = img32FC1.at<float>(y2,x2);
		float fx2 = fx2y1 + (fx2y2-fx2y1)*(y-y1)/(y2-y1);

		return fx1 + (fx2-fx1)*(x-x1)/(x2-x1);
		
	}

	//Rotate Point(x,y) by angle theta
	//PARAM	 INPUT
	//	@ x		:		input x-coordinate
	//	@ y		:		input y-coordinate
	//	@ theta	:		rotate angle  theta [0,2*PI)
	//PARAM  OUTPUT
	//	@ ox	:		output x-coordinate after rotation
	//	@ oy	:		output y-coordinate after rotation
	//RETURN VOID
	inline void ik_rotate_coordinate( int x, int y, double theta, OUT int &ox, OUT int &oy){
		 ox = (int)(x*cos(theta)-y*sin(theta)+0.5);
		 oy = (int)(x*sin(theta)+y*cos(theta)+0.5);
	}

	//Rotate image at (0,0) by angle theta ANTI-CLOCKWISELY, if want to rotate 
	//CLOCKWISELY, the theta should be negative	 the input type MUST be float
	//PARAM  INPUT
	//	@ img_in32F	:		input image	float
	//PARAM  OUTPUT
	//	@ theta		:		rotate angle  theta [0,2*PI)
	//  @ bComplete    :		show image completely or partly 
	//	@ img_out32F	:		output image float
	//RETURN VOID
	void ik_rotate(		const Mat& img_in32F, 
						double theta, 
						bool bComplete=true, 
						IK_METHOD_INTERP method = IK_BILINEAR,
						OUT Mat& img_out32F=Mat()
					);

}

#endif