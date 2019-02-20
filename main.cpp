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

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

typedef struct{
	int a;
	int b;
	int c;
}test_t;


int main(int argc , char** argv)
{
	//test_triangle();

	vector<Point2i> verfp;
	vector<Point2i> posfp;
	 Point2i inpoint;
	 Point2i tmp;
	 Point2i result;

	 tmp.x = 0;
	 tmp.y = 0;
	 verfp.push_back(tmp);

	 tmp.x = 1000;
	 tmp.y = 0;
	 verfp.push_back(tmp);

	 tmp.x = 500;
	 tmp.y = 500;
	 verfp.push_back(tmp);
	 /****************************************/
	 tmp.x = 0;
	 tmp.y = 0;
	 posfp.push_back(tmp);

	 tmp.x = 1000;
	 tmp.y = 0;
	 posfp.push_back(tmp);

	 tmp.x = 500;
	 tmp.y = 500;
	 posfp.push_back(tmp);

	 inpoint.x = 500;
	 inpoint.y = 500;

	 unsigned int d1, d2, d3 ,d;
	 double f1, f2, f3;




	 d1 = pow((inpoint.x - verfp[0].x),2) + pow((inpoint.y - verfp[0].y),2);
	 d2 = pow((inpoint.x - verfp[1].x),2) + pow((inpoint.y - verfp[1].y),2);
	 d3 = pow((inpoint.x - verfp[2].x),2) + pow((inpoint.y - verfp[2].y),2);
	 d = d1 + d2 + d3;

	 printf("d1 , d2, d3  ,d = (%u , %u ,%u , %u ) \n",d1, d2 ,d3 ,d );
	 f1 =  (double)d1/d;
	 f2 =  (double)d2/d;
	 f3 =  (double)d3/d;
	 printf("f1 , f2, f3  = (%f , %f ,%f)\n",f1, f2 ,f3);
	 result.x = f1*posfp[0].x + f2*posfp[1].x + f3*posfp[2].x;
	 result.y = f1*posfp[0].y + f2*posfp[1].y + f3*posfp[2].y;

	 printf("result x,y = (%d , %d )\n",result.x, result.y);


	return 0;
}
