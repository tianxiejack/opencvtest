/*
 * main.cpp
 *
 *  Created on: 2019年2月19日
 *      Author: alex
 */


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "test_triangle.hpp"
#include "stdio.h"
#include "string.h"

#include <algorithm>

#include <iostream>
#include <vector>

#include "trigonometric.hpp"

using namespace std;
using namespace cv;

using namespace cr_trigonometricInterpolation;

int main(int argc , char** argv)
{


	Mat test = Mat(1080,1920,CV_8UC3);


	Trigonometric tri = Trigonometric(1920,1080);

	vector<position_t> verfp;

	 Point2i inpoint;
	 position_t tmp;
	 Point2i result;

	 tri.readParams(verfp);
	 tri.insertVertexAndPosition( verfp );
	 //tri.writeParams();

	 //vector<position_t> fp88;
	 //tri.readParams(fp88);

	// for(int k =0 ;k < fp88.size();k++)
	 //		printf("orignal   ver -x,y = (%d , %d )  , pos-x,y  = (%d ,%d )\n",fp88[k].ver.x,fp88[k].ver.y, fp88[k].pos.x, fp88[k].pos.y);


#if 1
	 tri.draw_subdiv( test , true );

	 /****************************************/

	inpoint.x = 1300;
	inpoint.y = 800;


	vector<position_t> aaa;
	Point2i getpos;
	tri.draw_point_triangle( test , inpoint ,aaa,getpos ,true );

	//for(int k =0 ;k < aaa.size();k++)
	//	printf("orignal   ver -x,y = (%d , %d )  , pos-x,y  = (%d ,%d )\n",aaa[k].ver.x,aaa[k].ver.y, aaa[k].pos.x, aaa[k].pos.y);
	//printf( "getpos-x,y = (%d , %d ) \n",getpos.x , getpos.y );

	imshow("111111111111", test);
	cv::waitKey(30000);

	//int flag  =  tri.Point2getPos( inpoint,result );

	//printf("flag = %d        ****   result x,y = %d ,%d \n",flag ,result.x,result.y);
#endif

	return 0;
}
