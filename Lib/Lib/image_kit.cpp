#include "image_kit.h"
#include "global_header.h"


void image_kit::ik_rotate( const Mat& img_in32F, double theta, bool bComplete/*=1*/, IK_METHOD_INTERP method /*= IK_BILINEAR*/, OUT Mat& img_out32F/*=Mat()*/ )
{
	theta*=-1.0;
	std::cout<< img_in32F.depth()<<std::endl;
	CV_Assert(img_in32F.depth() == 5);
	int x_rotate, y_rotate, x_min = 10000000, x_max = -1000000, y_min = 1000000, y_max = -1000000;

	ik_rotate_coordinate(0, 0, theta, x_rotate, y_rotate);
	
	x_min = min(x_min,x_rotate);
	x_max = max(x_max,x_rotate);
	y_min = min(y_min,y_rotate);
	y_max = max(y_max,y_rotate);

	ik_rotate_coordinate(0, img_in32F.rows, theta, x_rotate, y_rotate);

	x_min = min(x_min,x_rotate);
	x_max = max(x_max,x_rotate);
	y_min = min(y_min,y_rotate);
	y_max = max(y_max,y_rotate);

	ik_rotate_coordinate(img_in32F.cols, 0, theta, x_rotate, y_rotate);

	x_min = min(x_min,x_rotate);
	x_max = max(x_max,x_rotate);
	y_min = min(y_min,y_rotate);
	y_max = max(y_max,y_rotate);

	ik_rotate_coordinate(img_in32F.cols, img_in32F.rows ,theta, x_rotate, y_rotate);

	x_min = min(x_min,x_rotate);
	x_max = max(x_max,x_rotate);
	y_min = min(y_min,y_rotate);
	y_max = max(y_max,y_rotate);

	int row = y_max-y_min;
	int col = x_max-x_min;


	vector<Mat> img_channels, out_img_channels;
	split(img_in32F , img_channels);
	
	for(int c= 0 ; c<img_channels.size() ; ++c)
	{
		Mat in_per_channel = img_channels[c];
		Mat out_per_channel =  Mat::zeros(row, col, CV_32FC1);

		for(int y = 0; y<row ; ++y)
		{
			for(int x=0; x<col; ++x)
			{
				float u,v;
				if( bComplete == true )
				{
					u = (x+x_min)*cos(theta)+(y+y_min)*sin(theta);
					v = (y+y_min)*cos(theta)-(x+x_min)*sin(theta);
				}
				else
				{
					u = (x)*cos(theta)+(y)*sin(theta);
					v = (y)*cos(theta)-(x)*sin(theta);
				}
				if(method == IK_NEAREST)
				{
					 int iu = int(u), iv = int(v);
					 if( iu>=0 && iu< img_in32F.cols && iv>=0 && iv < img_in32F.rows)
						 out_per_channel.at<float>(y,x) = in_per_channel.at<float>(iv,iu);
				}
				else if( method == IK_BILINEAR)
				{
					int x1 = int(u), x2 = x1+1, y1=int(v), y2=y1+1;
					if( x1>=0 && x2<img_in32F.cols && y1>=0 && y2<img_in32F.rows )
						out_per_channel.at<float>(y,x) = ik_bilinearInterp(in_per_channel, u, v);
				}

			}
		}
		out_img_channels.push_back(out_per_channel);
	}
	merge(out_img_channels, img_out32F);
}

