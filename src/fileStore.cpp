#if 0

#include "stdio.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	string cfgAvtFile;
	cfgAvtFile = "avt.yml";
    char cfg_avt[16] = "cfg_avt_";
    int configId_Max=128;
    float cfg_blk_val[128];

	FILE *fp = fopen(cfgAvtFile.c_str(), "rt");
	float abc = 1.23456789;
	if(fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fclose(fp);

		if(len < 10)
			return -1;
		else
		{
			FileStorage fr(cfgAvtFile, FileStorage::WRITE);
			if(fr.isOpened())
			{
				for(int i=0; i<configId_Max; i++){
					sprintf(cfg_avt, "cfg_avt_%d", i);
					//cfg_blk_val[i] = (float)fr[cfg_avt];
					//printf(" update cfg [%d] %f \n", i, cfg_blk_val[i]);
					fr<< cfg_avt << (float)abc;
				}
			}else
				return -1;
		}



	}






    return 0;
}
#endif
