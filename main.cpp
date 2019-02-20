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

typedef struct{
	Point2i ver;
	Point2i pos;
}position_t;

bool comp(const position_t &a,const position_t &b)
{
	unsigned int tmpa ,tmpb;

	tmpa = a.ver.x;
	tmpb = b.ver.x;

	return tmpa<tmpb;
}




int main(int argc , char** argv)
{
	//test_triangle();

	vector<position_t> verfp;

	 Point2i inpoint;
	 position_t tmp;
	 Point2i result;

	 tmp.ver.x = 0;
	 tmp.ver.y = 0;
	 tmp.pos.x = 35000;
	 tmp.pos.y = 0;
	 verfp.push_back(tmp);

	 tmp.ver.x = 1000;
	 tmp.ver.y = 300;
	 tmp.pos.x = 0;
	 tmp.pos.y = 0;
	 verfp.push_back(tmp);

	 tmp.ver.x = 2000;
	 tmp.ver.y = 0;
	 tmp.pos.x = 1000;
	 tmp.pos.y = 500;
	 verfp.push_back(tmp);
	 /****************************************/
	 inpoint.x = 500;
	 inpoint.y = 0;

	 unsigned int d1, d2, d3 ,d;
	 double f1, f2, f3 ,dtmp;


#if 0
	 d1 = pow((inpoint.x - verfp[0].x),2) + pow((inpoint.y - verfp[0].y),2);
	 d2 = pow((inpoint.x - verfp[1].x),2) + pow((inpoint.y - verfp[1].y),2);
	 d3 = pow((inpoint.x - verfp[2].x),2) + pow((inpoint.y - verfp[2].y),2);
	 d = d1 + d2 + d3;

	 printf("d1 , d2, d3  ,d = (%u , %u ,%u , %u ) \n",d1, d2 ,d3 ,d );

	f1 =  (double)d1/d;
	f2 =  (double)d2/d;
	f3 =  (double)d3/d;
	printf("f1 , f2, f3  = (%f , %f ,%f)\n",f1, f2 ,f3);

#else

	int min = 40000 , max = 0;
	int sizeNum = verfp.size();
	if(sizeNum)
		sort(verfp.begin(),verfp.end(),comp);

	if(abs(verfp[2].pos.x - verfp[0].pos.x) > 18000)
	{
		verfp[0].pos.x += 36000;
		verfp[1].pos.x += 36000;
	}

	for(int j=0;j<3;j++)
	{
		if( verfp[j].pos.y > 32000)
		{
			verfp[j].pos.y = 32768 - verfp[j].pos.y;
		}
	}

	 d1 = pow((inpoint.x - verfp[0].ver.x),2) + pow((inpoint.y - verfp[0].ver.y),2);
	 d2 = pow((inpoint.x - verfp[1].ver.x),2) + pow((inpoint.y - verfp[1].ver.y),2);
	 d3 = pow((inpoint.x - verfp[2].ver.x),2) + pow((inpoint.y - verfp[2].ver.y),2);

	 dtmp = 1+ (double)d1/d2 + (double)d2/d3 ;
	 printf("d1 , d2, d3  = (%u , %u ,%u ) \n",d1, d2 ,d3 );
	 f1 = 1/dtmp;
	 f2 = (double)d1/d2*f1;
	 f3 = 1 - f1 - f2;
	 printf("f1 , f2, f3  = (%f , %f ,%f)\n",f1, f2 ,f3);

#endif

	 result.x = f1*verfp[0].pos.x + f2*verfp[1].pos.x + f3*verfp[2].pos.x;
	 result.y = f1*verfp[0].pos.y + f2*verfp[1].pos.y + f3*verfp[2].pos.y;

	result.x %= 36000;
	if(result.y < 0)
		result.y = 32768 - result.y ;

	printf("result x,y = (%d , %d )\n",result.x, result.y);

	return 0;
}
