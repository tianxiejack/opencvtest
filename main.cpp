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

typedef struct{
	int a;
	int b;
	int c;
}test_t;


int main(int argc , char** argv)
{
	test_triangle();

	return 0;
}
