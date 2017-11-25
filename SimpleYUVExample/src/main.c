#include <stdio.h>
#include "rgb.h"
#include "yuv.h"

int main(){
	//simplest_yuv420_split("lena_256x256_yuv420p.yuv",256,256,1);
	//simplest_yuv444_split("lena_256x256_yuv444p.yuv",256,256,1); 
	
    //simplest_yuv420_gray("lena_256x256_yuv420p.yuv",256,256,1);	
	//simplest_yuv420_halfy("lena_256x256_yuv420p.yuv",256,256,1);
    //simplest_yuv420_border("lena_256x256_yuv420p.yuv",256,256,20,1);
    //simplest_rgb24_split("cie1931_500x500.rgb", 500, 500,1);
    //simplest_rgb24_to_bmp("lena_256x256_rgb24.rgb",256,256,"output_lena.bmp");
    simplest_rgb24_to_bmp("cie1931_500x500.rgb",500,500,"output_500.bmp");
	printf("done\n");
}
