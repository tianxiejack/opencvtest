/*
 * trigonometric.hpp
 *
 *  Created on: 2019年2月20日
 *      Author: alex
 */

#ifndef TRIGONOMETRIC_HPP_
#define TRIGONOMETRIC_HPP_

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

using namespace cv;

namespace cr_trigonometricInterpolation{

typedef struct{
	Point2i ver;
	Point2i pos;
}position_t;

class Trigonometric{

public:
	Trigonometric(int width , int height);
	virtual ~Trigonometric();

	void insertVertexAndPosition(const position_t insert);
	void updateSubdiv();

	int Point2getPos(const Point2i inPoint );
	void getTriangleVertex( Point2f fp, vector<Point2i> &result );
	void vertex2pos(vector<Point2i> &vertex , vector<Point2i> & getPos );

	void InterpolationPos( Point2i inPoint , vector<Point2i>& triVertex ,  vector<Point2i>& triPos , Point2i result );
	void preprocessPos( vector<Point2i>& inpos , vector<Point2i>& outpos );
	void getPos( Point2i inPoint , vector<Point2i>& triVertex ,  vector<Point2i>& triPos , Point2i result );

private:
	Subdiv2D subdiv;
	Rect rect;
	vector<position_t> fpassemble;



};





}



#endif /* TRIGONOMETRIC_HPP_ */