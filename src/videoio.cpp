/*
 * videoio.cpp
 *
 *  Created on: 2018年7月5日
 *      Author: alex
 */
/*

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		printf("could not load video data...\n");
		return -1;
	}

	double fps = capture.get(CV_CAP_PROP_FPS);
	printf("FPS : %f", fps);

	Mat frame, gray, binary;
	Mat bsmaskMOG2, bsmaskKNN;
	namedWindow("input video", CV_WINDOW_AUTOSIZE);
	namedWindow("MOG2", CV_WINDOW_AUTOSIZE);
	//namedWindow("KNN Model", CV_WINDOW_AUTOSIZE);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Ptr<BackgroundSubtractor> pMOG2 =  createBackgroundSubtractorMOG2();

	namedWindow("video-demo", CV_WINDOW_AUTOSIZE);

	while (capture.read(frame)) {

			flip(frame, frame, 1);
			imshow("video-demo", frame);

	//		pMOG2->apply(frame, bsmaskMOG2);
	//		morphologyEx(bsmaskMOG2, bsmaskMOG2, MORPH_OPEN, kernel, Point(-1, -1));
	//		imshow("MOG2", bsmaskMOG2);


			char c = waitKey(10);
			if (c == 27) {
				break;
			}
		}
	return 0;
}
*/
