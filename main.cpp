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
	//test_triangle();

	Mat test = Mat(1080,1920,CV_8UC3);


	Trigonometric tri = Trigonometric(1920,1080);

	vector<position_t> verfp;

	 Point2i inpoint;
	 position_t tmp;
	 Point2i result;

	 tmp.ver.x = 0;
	 tmp.ver.y = 0;
	 tmp.pos.x = 35000;
	 tmp.pos.y = 33768;
	 verfp.push_back(tmp);

	 tmp.ver.x = 300;
	 tmp.ver.y = 0;
	 tmp.pos.x = 1000;
	 tmp.pos.y = 2000;
	 verfp.push_back(tmp);

	 tmp.ver.x = 150;
	 tmp.ver.y = 300;
	 tmp.pos.x = 2000;
	 tmp.pos.y = 1000;
	 verfp.push_back(tmp);

	 tri.insertVertexAndPosition( verfp );
	 tri.draw_subdiv( test , true );

	 imshow("abcde" , test);
	 cv::waitKey(10000);
	 return 0;


	 /****************************************/

	// inpoint.x = 150;
	// inpoint.y = 200;

	//int flag  =  tri.Point2getPos( inpoint,result );

	//printf("flag = %d        ****   result x,y = %d ,%d \n",flag ,result.x,result.y);

	return 0;
}
