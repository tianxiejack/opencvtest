/*
 * 1.cpp
 *
 *  Created on: 2018年6月5日
 *      Author: alex
 */
#if 0

#include "stdio.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv;

//多边形并且进行实心填充
void drawpoly()
{
    //Mat img(500, 500, CV_8U, Scalar(0));
	Mat img = imread("avt51.png");
    Point root_points[1][3];
    root_points[0][0] = Point(200,200);
    root_points[0][1] = Point(300,200);
    root_points[0][2] = Point(250,300);
    //root_points[0][3] = Point(235,465);

    const Point* ppt[1] = {root_points[0]};
    int npt[] = {3};
    polylines(img, ppt, npt, 1, 1, Scalar(255),1,8,0);
    imshow("Test", img);
    waitKey();
    fillPoly(img, ppt, npt, 1, Scalar(255,125,255,255));
    imshow("Test", img);
    waitKey();
}

int main(int argc, char** argv)
{
	//drawpoly();
	return 0;
	Mat tmp = imread("avt51.png");

	putText(tmp,"l",cvPoint(300,300),CV_FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,125,255,255),2,8);


	//line(tmp,Point(100,100),Point(120,100),Scalar(0,0,255),11,4);
	//line(tmp,Point(100,100),Point(110,125),Scalar(0,0,255),11,4);
	//line(tmp,Point(120,100),Point(110,125),Scalar(0,0,255),11,4);


	imshow("abc",tmp);
	waitKey(10);
	return 0;
}

#endif


