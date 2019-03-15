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
#include <algorithm>
#include <vector>

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
	void getPos( Point2i inPoint , vector<position_t>& inPoints , Point2i& result );
	void updateSubdiv();
	void getTriangleVertex( Point2f fp, vector<position_t>& inPoints );
	void vertex2pos( vector<position_t>& inPoints );
	void InterpolationPos( Point2i inPoint , vector<position_t>& inPoints , Point2i& result );
	void preprocessPos( vector<position_t>& inPoints );
	void draw_subdiv_point( Mat& img, Point2i fp, Scalar color );
	int findposInFpassembel(Point2f &fp , Point2i &pos);


	void insertVertexAndPosition(vector<position_t> insert);
	int Point2getPos(const Point2i inPoint,Point2i &result );
	bool readParams(std::vector<position_t>& getParam);
	bool writeParams(void);
	

	void draw_subdiv( Mat& img ,bool bdraw);
	int draw_point_triangle( Mat& img , Point2i fp , vector<position_t> &back,Point2i &pos, bool bdraw );


private:
	Subdiv2D subdiv;
	Rect rect;
	vector<position_t> fpassemble;
	vector<position_t> use2Calc;

	FileStorage m_readfs;
	FileStorage m_writefs;

};

}

#endif /* TRIGONOMETRIC_HPP_ */
