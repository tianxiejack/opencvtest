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
#include "stdlib.h"
#include <algorithm>

#include <iostream>
#include <vector>

#include "trigonometric.hpp"

using namespace std;
using namespace cv;

using namespace cr_trigonometricInterpolation;
FileStorage pointFs;

int getpointFromYml(int& pointx , int & pointy )
{
	char paramName[40];
	memset(paramName,0,sizeof(paramName));
	string cfgFile;
	cfgFile = "point.yml";
	pointFs.open(cfgFile,FileStorage::READ);
	int size ;

	if(pointFs.isOpened())
	{
		sprintf(paramName,"inPointx");
		pointFs[paramName] >>pointx;
		sprintf(paramName,"inPointy");
		pointFs[paramName] >>pointy;

		pointFs.release();
		return true;
	}
	return false;
}


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

#if 0
	 int tmpnum;
	 for(int k=0; k < 50; k++)
	 {
		 tmpnum = rand()%100;
		 if(tmpnum < verfp.size())
			 verfp.erase(verfp.begin()+tmpnum);
		 else
			 k--;
	 }
	 tri.insertVertexAndPosition( verfp );

	 tri.writeParams();
	 return 0;
#endif

#if 1
	 tri.draw_subdiv( test , true );

	 /****************************************/
	putchar(10);putchar(10);putchar(10);
	inpoint.x = 800;
	inpoint.y = 860;
	getpointFromYml(inpoint.x,inpoint.y);
	printf("inpoint  :x,y =  (%d , %d ) \n" ,inpoint.x , inpoint.y );

	vector<position_t> aaa;
	Point2i getpos;
	tri.draw_point_triangle( test , inpoint ,aaa,getpos ,true );

	for(int k =0 ;k < aaa.size();k++)
		printf("orignal   ver -x,y = (%d , %d )  , pos-x,y  = (%d ,%d )\n",aaa[k].ver.x,aaa[k].ver.y, aaa[k].pos.x, aaa[k].pos.y);
	printf( "getpos-x,y = (%d , %d ) \n",getpos.x , getpos.y );

	imshow("111111111111", test);
	cv::waitKey(0);
	putchar(10);putchar(10);putchar(10);
	//int flag  =  tri.Point2getPos( inpoint,result );

	//printf("flag = %d        ****   result x,y = %d ,%d \n",flag ,result.x,result.y);
#endif

	return 0;
}
