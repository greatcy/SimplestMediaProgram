#include <stdio.h>
#include "rgb.h"
#include "yuv.h"

int main(){
	//simplest_yuv420_split("lena_256x256_yuv420p.yuv",256,256,1);
	//simplest_yuv444_split("lena_256x256_yuv444p.yuv",256,256,1); 
	
	//simplest_yuv420_gray("lena_256x256_yuv420p.yuv",256,256,1);	
	simplest_yuv420_halfy("lena_256x256_yuv420p.yuv",256,256,1);
	printf("done\n");
}
