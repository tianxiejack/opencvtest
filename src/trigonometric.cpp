/*
 * trigonometric.cpp
 *
 *  Created on: 2019年2月20日
 *      Author: alex
 */


#include "trigonometric.hpp"

using namespace cr_trigonometricInterpolation;

Trigonometric::Trigonometric(int width , int height)
{
	rect.x = 0 ;
	rect.y = 0;
	rect.width = width ;
	rect.height = height;
	 subdiv.initDelaunay(rect);
}

Trigonometric::~Trigonometric()
{
	fpassemble.clear();
}

void Trigonometric::insertVertexAndPosition(vector<position_t> insert)
{
	fpassemble.clear();
	fpassemble = insert;
	updateSubdiv();
	return ;
}

void Trigonometric::updateSubdiv()
{
	for(std::vector<position_t>::iterator plist = fpassemble.begin(); plist != fpassemble.end(); ++plist)
	{
		 subdiv.insert( plist->ver );
	}
}

int Trigonometric::Point2getPos(const Point2i inPoint)
{
	int ret = 0;
	vector<Point2i> triVertex;
	vector<Point2i> triPos;
	Point2i result ;

	getTriangleVertex( inPoint , triVertex);
	for(std::vector<Point2i>::iterator plist = triVertex.begin(); plist != triVertex.end(); ++plist)
	{
		if( plist->x <= 0 || plist->x >= rect.width || plist->y <= 0 || plist->y >= rect.height )
			ret = -1;
		break;
	}

	if( -1 == ret )
		return ret;

	vertex2pos( triVertex, triPos );

	getPos( inPoint , triVertex ,  triPos , result );

	return ret;
}

void Trigonometric::getTriangleVertex( Point2f fp, vector<Point2i> &result )
{
	 int e0=0, vertex=0;
	 Point2i tmp;
	 subdiv.locate(fp, e0, vertex);
	 if( e0 > 0 )
	 {
		 int e = e0;
		 do
		 {
			 Point2f org, dst;
			 if( subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst) > 0 )
			 {
				 result.push_back(org);
			 }
			 e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
		 }
		 while( e != e0 );
	 }
}

void Trigonometric::vertex2pos(vector<Point2i> &vertex, vector<Point2i> & getPos )
{
	 getPos.clear();
	 for(int i = 0 ; i< vertex.size(); i++)
	 {
		for(std::vector<position_t>::iterator plist = fpassemble.begin(); plist != fpassemble.end(); ++plist)
		{
			if( plist->ver == vertex[i] )
			{
				getPos.push_back( plist->pos );
				break;
			}
		}
	 }

	 return;
}



void Trigonometric::preprocessPos( vector<Point2i>& inpos , vector<Point2i>& outpos )
{
	int min,max;


	return ;
}

void Trigonometric::InterpolationPos( Point2i inPoint , vector<Point2i>& triVertex ,  vector<Point2i>& triPos , Point2i result )
{
	 unsigned int d1, d2, d3 ,d;
	 double f1, f2, f3;

	 d1 = pow((inPoint.x - triVertex[0].x),2) + pow((inPoint.y - triVertex[0].y),2);
	 d2 = pow((inPoint.x - triVertex[1].x),2) + pow((inPoint.y - triVertex[1].y),2);
	 d3 = pow((inPoint.x - triVertex[2].x),2) + pow((inPoint.y - triVertex[2].y),2);
	 d = d1 + d2 + d3;
	 f1 = d1/d;
	 f2 = d2/d;
	 f3 = d3/d;

	 result.x = f1*triPos[0].x + f2*triPos[1].x + f3*triPos[2].x;
	 result.y = f1*triPos[0].y + f2*triPos[1].y + f3*triPos[2].y;

	 return ;
}

void Trigonometric::getPos( Point2i inPoint , vector<Point2i>& triVertex ,  vector<Point2i>& triPos , Point2i result )
{
	vector<Point2i> outpos;
	//preprocessPos( triPos , outpos );

	InterpolationPos( inPoint, triVertex, triPos, result );

	return ;
}
