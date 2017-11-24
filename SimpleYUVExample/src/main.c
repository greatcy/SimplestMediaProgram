#include <stdio.h>
#include "rgb.h"
#include "yuv.h"

int main(){
	simplest_yuv420_split("lena_256x256_yuv420p.yuv",256,256,1);
	//printf("done\n");
}
