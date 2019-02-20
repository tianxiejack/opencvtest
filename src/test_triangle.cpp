/*
 * test_triangle.cpp
 *
 *  Created on: 2019年2月19日
 *      Author: alex
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "test_triangle.hpp"
#include "stdio.h"
#include "unistd.h"
#include "math.h"

using namespace cv;
using namespace std;


vector<Point2f> fpvec;
Point2f array[100];

typedef struct{
	Point2i ver;
	Point2i pos;
}position_t;

static void help()
{
    cout << "\nThis program demostrates iterative construction of\n"
           "delaunay triangulation and voronoi tesselation.\n"
           "It draws a random set of points in an image and then delaunay triangulates them.\n"
           "Usage: \n"
           "./delaunay \n"
           "\nThis program builds the traingulation interactively, you may stop this process by\n"
           "hitting any key.\n";
}

static void draw_subdiv_point( Mat& img, Point2f fp, Scalar color )
{
    circle( img, fp, 3, color, CV_FILLED, 8, 0 );
}

static void draw_subdiv( Mat& img, Subdiv2D& subdiv, Scalar delaunay_color )
{
#if 1
    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    vector<Point> pt(3);

    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
        line(img, pt[0], pt[1], delaunay_color, 1, CV_AA, 0);
        line(img, pt[1], pt[2], delaunay_color, 1, CV_AA, 0);
        line(img, pt[2], pt[0], delaunay_color, 1, CV_AA, 0);
    }
#else
    vector<Vec4f> edgeList;
    subdiv.getEdgeList(edgeList);
    for( size_t i = 0; i < edgeList.size(); i++ )
    {
        Vec4f e = edgeList[i];
        Point pt0 = Point(cvRound(e[0]), cvRound(e[1]));
        Point pt1 = Point(cvRound(e[2]), cvRound(e[3]));
        line(img, pt0, pt1, delaunay_color, 1, CV_AA, 0);
    }
#endif
}

static void locate_point( Mat& img, Subdiv2D& subdiv, Point2f fp, Scalar active_color )
{
    int e0=0, vertex=0;

    subdiv.locate(fp, e0, vertex);
    int num = 0;
    if( e0 > 0 )
    {
        int e = e0;
        do
        {
            Point2f org, dst;
            if( subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst) > 0 )
            {
            	printf("index = %d \n",num++);
            	draw_subdiv_point( img, org, active_color );
            	draw_subdiv_point( img, dst, active_color );
            	waitKey(1000);
                line( img, org, dst, active_color, 3, CV_AA, 0 );
                putchar(10);
                printf("org.x = %f , org.y = %f \n", org.x ,org.y);
                printf("dst.x = %f , dst.y = %f \n", dst.x ,dst.y);
                putchar(10);
            }


            e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }

    draw_subdiv_point( img, fp, active_color );
}





static void paint_voronoi( Mat& img, Subdiv2D& subdiv )
{
    vector<vector<Point2f> > facets;
    vector<Point2f> centers;
    subdiv.getVoronoiFacetList(vector<int>(), facets, centers);

    vector<Point> ifacet;
    vector<vector<Point> > ifacets(1);

    for( size_t i = 0; i < facets.size(); i++ )
    {
        ifacet.resize(facets[i].size());
        for( size_t j = 0; j < facets[i].size(); j++ )
            ifacet[j] = facets[i][j];

        Scalar color;
        color[0] = rand() & 255;
        color[1] = rand() & 255;
        color[2] = rand() & 255;
        fillConvexPoly(img, ifacet, color, 8, 0);

        ifacets[0] = ifacet;
        polylines(img, ifacets, true, Scalar(), 1, CV_AA, 0);
        circle(img, centers[i], 3, Scalar(), CV_FILLED, CV_AA, 0);
    }
}

void setArray(int index , int x ,int y)
{
	array[index].x = x;
	array[index].y = y;
	return ;
}

void initArray()
{
	setArray(0, 10 , 10);
	setArray(1, 100 , 10);
	setArray(2, 200 , 10);
	setArray(3, 300 , 10);
	setArray(4, 400 , 10);
	setArray(5, 500 , 10);
	setArray(6, 550 , 10);
	setArray(7, 20 , 70);
	setArray(8, 80 , 70);
	setArray(9, 160 , 90);
	setArray(10, 230 , 80);
	setArray(11, 330 , 75);
	setArray(12, 450 , 100);
	setArray(13, 530 , 110);
	setArray(14, 540 , 130);
	setArray(15, 58 , 200);
	setArray(16, 30 ,400);
	setArray(17, 50 ,500);
	setArray(18, 60 ,550);
	setArray(19, 330 ,390);
	setArray(20, 490 ,510);

	return ;
}


void pushFpIntoVector(vector<Point2f> &fp)
{
	for(int i =0 ;i < 20 ;i++)
		fp.push_back(array[i]);
}

 void trigonometric_interpolation(const vector<Point2i> &verfp , Point2i locate,Point2i &result)
 {
	 unsigned int d1, d2, d3 ,d;
	 double f1, f2, f3;

	 d1 = pow((locate.x - verfp[0].x),2) + pow((locate.y - verfp[0].y),2);
	 d2 = pow((locate.x - verfp[1].x),2) + pow((locate.y - verfp[1].y),2);
	 d3 = pow((locate.x - verfp[2].x),2) + pow((locate.y - verfp[2].y),2);
	 d = d1 + d2 + d3;
	 f1 = d1/d;
	 f2 = d2/d;
	 f3 = d3/d;

	 result.x = f1*verfp[0].x + f2*verfp[1].x + f3*verfp[2].x;
	 result.y = f1*verfp[0].y + f2*verfp[1].y + f3*verfp[2].y;

	 return ;
 }

 void InterpolationMethod( const Point2i verfp,vector <position_t> & position ,Point2i & result )
 {
		Point2i  pos;

		for(std::vector<position_t>::iterator plist = position.begin(); plist != position.end(); ++plist)
		{
			if( plist->ver == verfp )
			{
				pos = plist->pos;
				break;
			}
		}


		return ;
 }










int test_triangle()
{

	initArray();
	pushFpIntoVector(fpvec);



    //help();

    Scalar active_facet_color(0, 0, 255), delaunay_color(255,255,255);
    Rect rect(0, 0, 1000, 1000);

    Subdiv2D subdiv(rect);
    Mat img(rect.size(), CV_8UC3);

    img = Scalar::all(0);
    string win = "Delaunay Demo";
    imshow(win, img);
    waitKey(1000);

    for(int i=0; i<fpvec.size();i++)
    {
    	 //locate_point( img, subdiv, fpvec[i], active_facet_color );
    	 subdiv.insert(fpvec[i]);
    }

    subdiv.insert(fpvec);
	img = Scalar::all(0);
	draw_subdiv( img, subdiv, delaunay_color );
	imshow( win, img );
	waitKey(1000);

    Point2f fptmp( 120,230 );
    locate_point( img, subdiv, fptmp, active_facet_color );
    imshow( win, img );

    waitKey(5000);

    fptmp.x = 50 ;
    fptmp.y = 550 ;
    locate_point( img, subdiv, fptmp, active_facet_color );
    imshow( win, img );
	waitKey(1000);

    waitKey(0);
    return 0;

/*********************************************/
#if 0
    Point2f fptmp( 100,100 );
    locate_point( img, subdiv, fptmp, active_facet_color );
    imshow( win, img );
    waitKey(1000);

    subdiv.insert(fptmp);
    draw_subdiv( img, subdiv, delaunay_color );
    imshow( win, img );

    waitKey(1000);

    fptmp.x = 300;
    fptmp.y = 300;
    locate_point( img, subdiv, fptmp, active_facet_color );
    imshow( win, img );
    waitKey(1000);

    subdiv.insert(fptmp);
    draw_subdiv( img, subdiv, delaunay_color );
    imshow( win, img );



#endif



#if 0
    for( int i = 0; i < 200; i++ )
    {
        Point2f fp( (float)(rand()%(rect.width-10)+5),
                    (float)(rand()%(rect.height-10)+5));

        locate_point( img, subdiv, fp, active_facet_color );
        imshow( win, img );

        if( waitKey( 100 ) >= 0 )
            break;

        subdiv.insert(fp);

        img = Scalar::all(0);
        draw_subdiv( img, subdiv, delaunay_color );
        imshow( win, img );

        if( waitKey( 100 ) >= 0 )
            break;
    }

    img = Scalar::all(0);
    paint_voronoi( img, subdiv );
    imshow( win, img );

    waitKey(0);

    return 0;
#endif

}


