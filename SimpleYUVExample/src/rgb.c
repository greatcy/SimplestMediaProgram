#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rgb.h"

int simplest_rgb24_split(char *url, int w, int h,int num){
	FILE *fp = fopen(url,"r");
	FILE *fp1 = fopen(url,"w");
	FILE *fp2 = fopen(url,"w");
	FILE *fp3 = fopen(url,"w");
	
	unsigned char *pic = (unsigned char *)malloc(w*h*3);

	//Packed mode
	int i;
	for(i=0;i<num;i++){
		//R
		fwrite(pic+i,1,1,fp1);

		//G
		fwrite(pic+i+1,1,1,fp2);

		//B
		fwrite(pic+i+1+1,1,1,fp3);
	}

	free(pic);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}


int simplest_rgb24_to_bmp(const char *rgb24path,int width,int height,const char *bmppath){
	typedef struct{
		long imageSize;
		long blank;
		long startPosition;
	}BmpHead;

	typedef struct{
		long Length;
		long width;
		long height;
		unsigned short colorPlane;
		unsigned short bitColor;
		long zipFormat;
		long realSize;
		long xPels;
		long yPels;
		long colorUse;
		long colorImportant;
	}InfoHead;

	int i=0,j=0;
	BmpHead m_BMPHeader={0};
	InfoHead m_BMPInfoHeader={0};
	char bfType[2]={'B','M'};
	int header_size=sizeof(bfType)+sizeof(BmpHead)+sizeof(InfoHead);
	unsigned char *rgb24_buffer=NULL;
	FILE *fp_rgb24=NULL,*fp_bmp=NULL;
	
	if((fp_rgb24=fopen(rgb24path,"r"))==NULL){
		printf("Error : cannot open input rgb24\n");
		return -1;
	}

	if((fp_bmp=fopen(bmppath,"w"))==NULL){
		printf("Error : cannot open input rgb24\n");
		return -1;
	}

	rgb24_buffer = (unsigned char *)malloc(width*height*3);
	fread(rgb24_buffer,1,width*height*3,fp_rgb24);

	m_BMPHeader.imageSize=3*width*height+header_size;
	m_BMPHeader.startPosition=header_size;

	m_BMPInfoHeader.Length=sizeof(InfoHead);
	m_BMPInfoHeader.width=width;
	//BMP storage pixel form bottom to top
	m_BMPInfoHeader.height=-height;
	m_BMPInfoHeader.colorPlane=1;
	m_BMPInfoHeader.bitColor=24;
	m_BMPInfoHeader.realSize=3*width*height;

	//add head to BMP FILE
	fwrite(bfType,1,sizeof(bfType),fp_bmp);
	fwrite(&m_BMPHeader,1,sizeof(m_BMPHeader),fp_bmp);
	fwrite(&m_BMPInfoHeader,1,sizeof(m_BMPInfoHeader),fp_bmp);
	
	//add pixels data to BMP FILE.The pixels data storage in little Endian
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			char temp=rgb24_buffer[(j*width+i)*3+2];//save B weight
			rgb24_buffer[(j*width+i)*3+2]=rgb24_buffer[(j*width+i)*3+0];
			rgb24_buffer[(j*width+i)*3+0]=temp;
		}
	}

	fwrite(rgb24_buffer,3*width*height,1,fp_bmp);  
    	fclose(fp_rgb24);  
    	fclose(fp_bmp);  
    	free(rgb24_buffer);  
    	printf("Finish generate %s!\n",bmppath);  
    	return 0;
}

static unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){  
    if(x>max_val){  
        return max_val;  
    }else if(x<min_val){  
        return min_val;  
    }else{  
        return x;  
    }  
} 

//RGB to YUV420  
static int RGB24_TO_YUV420(unsigned char *RgbBuf,int w,int h,unsigned char *yuvBuf)  
{  
    	unsigned char*ptrY, *ptrU, *ptrV, *ptrRGB;  
    	memset(yuvBuf,0,w*h*3/2);  
    	ptrY = yuvBuf;  
    	ptrU = yuvBuf + w*h;  
    	ptrV = ptrU + (w*h*1/4);  
    	unsigned char y, u, v, r, g, b;  
	int j;
    	for (j = 0; j<h;j++){  
    	    ptrRGB = RgbBuf + w*j*3 ;  
	    int i;
    	    for (i = 0;i<w;i++){  
    	          
    	        r = *(ptrRGB++);  
    	        g = *(ptrRGB++);  
    	        b = *(ptrRGB++);  
    	        y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;            
    	        u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;            
    	        v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;  
    	        *(ptrY++) = clip_value(y,0,255);  
    	        if (j%2==0&&i%2 ==0){  
    	            *(ptrU++) =clip_value(u,0,255);  
    	        }  
    	        else{  
    	            if (i%2==0){  
    	            *(ptrV++) =clip_value(v,0,255);  
    	            }  
    	        }  
    	    }  
    	}  
    	return 1;  
}  

int simplest_rgb24_to_yuv420(char *url_in, int w, int h,int num,char *url_out){ 
	FILE *fp=fopen(url_in,"r");  
    	FILE *fp1=fopen(url_out,"w");  
  
    	unsigned char *pic_rgb24=(unsigned char *)malloc(w*h*3);  
    	unsigned char *pic_yuv420=(unsigned char *)malloc(w*h*3/2);  
  
	int i;
    	for(i=0;i<num;i++){  
    	    fread(pic_rgb24,1,w*h*3,fp);  
    	    RGB24_TO_YUV420(pic_rgb24,w,h,pic_yuv420);  
    	    fwrite(pic_yuv420,1,w*h*3/2,fp1);  
    	}  
  
    	free(pic_rgb24);  
    	free(pic_yuv420);  
    	fclose(fp);  
    	fclose(fp1);  
  
    return 0;  
}

