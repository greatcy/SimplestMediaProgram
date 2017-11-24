#include <stdlib.h>
#include <stdio.h>
#include "yuv.h"
#include <string.h>

int simplest_yuv420_split(char *url,int w,int h,int num){
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen("output_420_y.y","w");
	FILE *fp2 = fopen("output_420_u.y","w");
	FILE *fp3 = fopen("output_420_v.y","w");

	unsigned char *pic=(unsigned char *)malloc(w*h*3/2); 
	
	//for plane mode
	int i;
	for(i=0;i<num;i++){
		fread(pic,1,w*h*3/2,fp);	
		
		//Y
		fwrite(pic,1,w*h,fp1);
		//U
		fwrite(pic+w*h,1,w*h/4,fp2);
		//V
		fwrite(pic+w*h+w*h/4,1,w*h/4,fp3);
	}

	free(pic);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	
	return 0;
}


int simplest_yuv444_split(char *url, int w, int h,int num){
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen("output_444_y.y","w");
	FILE *fp2 = fopen("output_444_u.y","w");
	FILE *fp3 = fopen("output_444_v.y","w");
	
	unsigned char *pic=(unsigned char *)malloc(w*h*3);
	
	int i;	
	for(i=0;i<num;i++){
		fread(pic,1,w*h*3,fp);	
		
		//Y
		fwrite(pic,1,w*h,fp1);
		//U
		fwrite(pic+w*h,1,w*h,fp2);
		//V
		fwrite(pic+w*h*2,1,w*h,fp3);
	}

	free(pic);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	
	return 0;
}

int simplest_yuv420_gray(char *url, int w, int h,int num){
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen("output_gray.yuv","w");
	
	unsigned char *pic=(unsigned char *)malloc(w*h*3/2); 

	int i;
	for(i=0;i<num;i++){
		fread(pic,1,w*h*3/2,fp);	
		memset(pic+w*h,128,w*h/2);//reset u v weight
		fwrite(pic,1,w*h*3/2,fp1);
	}
	
	free(pic);
	fclose(fp);
	fclose(fp1);

	return 0;
}


int simplest_yuv420_halfy(char *url, int w, int h,int num){ 
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen("output_half.yuv","w");
	
	unsigned char *pic=(unsigned char *)malloc(w*h*3/2); 

	int i;
	for(i=0;i<num;i++){
		fread(pic,1,w*h*3/2,fp);	
		
		int j;
		for(j = 0;j<w*h;j++){
			pic[j]=pic[j]/2;
		}
		
		fwrite(pic,1,w*h*3/2,fp1);
	}
	
	free(pic);
	fclose(fp);
	fclose(fp1);

	return 0;
}

int simplest_yuv420_border(char *url, int w, int h,int border,int num){
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen("output_border.yuv","w");
	
	unsigned char *pic=(unsigned char *)malloc(w*h*3/2); 

	int i;
	for(i=0;i<num;i++){
		//for each frame the read point change	
		fread(pic,1,w*h*3/2,fp);
		
		int j;
		for(j=0;j<h;j++){
			int k;
			for(k=0;k<w;k++){
				pic[j*w+k]=255;
			}	
		}
		
		fwrite(pic,1,w*h*3/2,fp1);
	}
	
	free(pic);
	fclose(fp);
	fclose(fp1);

	return 0;
}

