/*
 * trigonometric.cpp
 *
 *  Created on: 2019年2月20日
 *      Author: alex
 */


#include "trigonometric.hpp"
#include <string.h>

using namespace cr_trigonometricInterpolation;
#define CONFIG_TRIGONOMETRIC_FILE		"ConfigTrignometricFile.yml"

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

int Trigonometric::Point2getPos(const Point2i inPoint,Point2i &result)
{
	int ret = 0;
	use2Calc.clear();

	getTriangleVertex( inPoint , use2Calc );
	for(std::vector<position_t>::iterator plist = use2Calc.begin(); plist != use2Calc.end(); ++plist)
	{
		if( plist->ver.x <= 0 || plist->ver.x > rect.width || plist->ver.y <= 0 || plist->ver.y > rect.height )
			ret = -1;
		break;
	}
	if( -1 == ret )
		return ret;

	vertex2pos( use2Calc );
	getPos( inPoint , use2Calc , result );
	return ret;
}

void Trigonometric::getTriangleVertex( Point2f fp, vector<position_t> &inPoints )
{
	 int e0=0, vertex=0;
	 position_t tmpVal;
	 subdiv.locate(fp, e0, vertex);
	 if( e0 > 0 )
	 {
		 int e = e0;
		 do
		 {
			 Point2f org, dst;
			 if( subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst) > 0 )
			 {
			 	 tmpVal.ver = org ;
				 inPoints.push_back(tmpVal);
			 }
			 e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
		 }
		 while( e != e0 );
	 }
}

void Trigonometric::vertex2pos( vector<position_t>& inPoints )
{
	 for(int i = 0 ; i< inPoints.size(); i++)
	 {
		for(std::vector<position_t>::iterator plist = fpassemble.begin(); plist != fpassemble.end(); ++plist)
		{
			if( plist->ver == inPoints[i].ver )
			{
				inPoints[i].pos = plist->pos;
				break;
			}
		}
	 }
	 return;
}

bool comp(const position_t &a,const position_t &b)
{
	unsigned int tmpa ,tmpb;
	tmpa = a.pos.x;
	tmpb = b.pos.x;
	return tmpa<tmpb;
}

void Trigonometric::preprocessPos( vector<position_t>& inPoints )
{
	int min = 40000 , max = 0;
	int sizeNum = inPoints.size();
	if(sizeNum)
		sort(inPoints.begin(),inPoints.end(),comp);

	if(abs(inPoints[2].pos.x - inPoints[0].pos.x) > 18000)
	{
		inPoints[0].pos.x += 36000;
		if(inPoints[1].pos.x < 18000)
			inPoints[1].pos.x += 36000;
	}

	for(int j=0;j<3;j++)
	{
		if( inPoints[j].pos.y > 32000)
		{
			inPoints[j].pos.y = 32768 - inPoints[j].pos.y;
		}
	}

	return ;
}

void Trigonometric::InterpolationPos( Point2i inPoint , vector<position_t>& inPoints , Point2i& result )
{
	 double d1, d2, d3;
	 double f1, f2, f3, dtmp;
	 int deltax,deltay;

	 for(int abc = 0 ; abc > inPoints.size() ; abc++)
	 {
		 printf("[%d] : x,y --(%d , %d )  , posx,posy --(%d , %d ) \n ",  abc , inPoints[abc].ver.x,inPoints[abc].ver.y,inPoints[abc].pos.x,inPoints[abc].pos.y   );
	 }

	 deltax = inPoint.x - inPoints[0].ver.x ;
	 deltay = inPoint.y - inPoints[0].ver.y ;
	 d1 = sqrt(pow(deltax,2) + pow(deltay,2));

	 deltax = inPoint.x - inPoints[1].ver.x ;
	 deltay = inPoint.y - inPoints[1].ver.y ;
	 d2 = sqrt(pow(deltax,2) + pow(deltay,2));

	 deltax = inPoint.x - inPoints[2].ver.x ;
	 deltay = inPoint.y - inPoints[2].ver.y ;
	 d3 = sqrt(pow(deltax,2) + pow(deltay,2));

	 dtmp = 1+ d1/d2 + d1/d3 ;
	 f1 = 1/dtmp;
	 f2 = d1/d2*f1;
	 f3 = 1 - f1 - f2;

	 result.x = f1*inPoints[0].pos.x + f2*inPoints[1].pos.x + f3*inPoints[2].pos.x;
	 result.y = f1*inPoints[0].pos.y + f2*inPoints[1].pos.y + f3*inPoints[2].pos.y;

	 result.x %= 36000;
	 	if(result.y < 0)
	 		result.y = 32768 - result.y ;

	 return ;
}

void Trigonometric::getPos( Point2i inPoint , vector<position_t>& inPoints , Point2i& result )
{
	preprocessPos( inPoints );

	InterpolationPos( inPoint, inPoints, result );

	return ;
}


void Trigonometric::draw_subdiv( Mat& img ,bool bdraw)
{
    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    vector<Point> pt(3);
    CvScalar color;
    if(bdraw)
    	color = cvScalar(0,100,255,255);
    else
    	color = cvScalar(0,0,0,0);

    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
        line(img, pt[0], pt[1], color, 1, CV_AA, 0);
        line(img, pt[1], pt[2], color, 1, CV_AA, 0);
        line(img, pt[2], pt[0], color, 1, CV_AA, 0);
    }
    return ;
}


int Trigonometric::draw_point_triangle( Mat& img , Point2i fp , vector<position_t> &back,Point2i &pos, bool bdraw )
{
    int e0=0, vertex=0;
    int num = 0;
    int ret = 0;
    int flag;
    int index;
    CvScalar color;
    vector<Point2f> orgpoint;
    Point2i tmppos;
    position_t tmpBack;

    if(bdraw)
    	color = cvScalar(255,0,255,255);
    else
    	color = cvScalar(0,0,0,0);

    subdiv.locate(fp, e0, vertex);

    if( e0 > 0 )
    {
        int e = e0;
        do
        {
            Point2f org, dst;
            if( subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst) > 0 )
            {
            	orgpoint.push_back(org);
            	if( org.x <= 0.00001 || org.x >  rect.width || org.y <= 0.00001 || org.y > rect.height )
            		ret = -1;
            }
            e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }

    if( -1 == ret )
    	return ret;

    for( int k=0;k<3 ; k++ )
    {
    	index = (k+1)%3;
        line( img, orgpoint[k], orgpoint[index], color, 3, CV_AA, 0 );
    }

    draw_subdiv_point( img, fp, color );
    back.clear();
    for( int k=0;k<3 ; k++ )
    {
    	flag = findposInFpassembel( orgpoint[k] , tmppos );

    	if( -1 == flag )
    		return -1;
    	else
    	{
    		tmpBack.ver = orgpoint[k];
    		tmpBack.pos = tmppos;
    		back.push_back(tmpBack);
    	}
    }
   Point2getPos( fp , pos );
    return 0;
}

int Trigonometric::findposInFpassembel(Point2f &fp , Point2i &pos)
{
	for(std::vector<position_t>::iterator plist = fpassemble.begin(); plist != fpassemble.end(); ++plist)
	{
		if( plist->ver.x == fp.x && plist->ver.y == fp.y )
		{
			pos.x = plist->pos.x;
			pos.y = plist->pos.y;
			return 0;
		}
	}
	return -1;
}

void Trigonometric::draw_subdiv_point( Mat& img, Point2i fp, Scalar color )
{
    circle( img, fp, 3, color, CV_FILLED, 8, 0 );
}

bool Trigonometric::readParams(std::vector<position_t>& getParam)
{
	char paramName[40];
	memset(paramName,0,sizeof(paramName));
	string cfgFile;
	cfgFile = CONFIG_TRIGONOMETRIC_FILE;
	m_readfs.open(cfgFile,FileStorage::READ);
	int size ;
	position_t tmpPos;

	fpassemble.clear();
	getParam.clear();
	if(m_readfs.isOpened())
	{
		sprintf(paramName,"vectorSize");	
		m_readfs[paramName] >> size ;
		for(int i=0; i<size; i++)
		{
			sprintf(paramName,"points_pos_x_%d",i);
			m_readfs[paramName] >>tmpPos.pos.x;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_pos_y_%d",i);
			m_readfs[paramName] >>tmpPos.pos.y;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_ver_x_%d",i);
			m_readfs[paramName] >>tmpPos.ver.x;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_ver_y_%d",i);
			m_readfs[paramName] >>tmpPos.ver.y;
			memset(paramName,0,sizeof(paramName));
			
			fpassemble.push_back(tmpPos);
		}
		getParam = fpassemble;
		m_readfs.release();
		return true;
	}
	return false;
}


bool Trigonometric::writeParams(void)
{
	char paramName[40];
	memset(paramName,0,sizeof(paramName));
	string cfgFile;
	cfgFile = CONFIG_TRIGONOMETRIC_FILE;
	
	m_writefs.open(cfgFile,FileStorage::WRITE);
	
	if(m_writefs.isOpened())
	{		
		sprintf(paramName,"vectorSize");
		m_writefs<<paramName<<(int)fpassemble.size();
		
		for(int i=0; i<fpassemble.size(); i++)
		{
			sprintf(paramName,"points_pos_x_%d",i);
			m_writefs<<paramName<<(int)fpassemble[i].pos.x;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_pos_y_%d",i);
			m_writefs<<paramName<<(int)fpassemble[i].pos.y;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_ver_x_%d",i);
			m_writefs<<paramName<<(int)fpassemble[i].ver.x;
			memset(paramName,0,sizeof(paramName));
			
			sprintf(paramName,"points_ver_y_%d",i);
			m_writefs<<paramName<<(int)fpassemble[i].ver.y;
			memset(paramName,0,sizeof(paramName));
		}
		m_writefs.release();
		return true;
	}

	return false;
}

