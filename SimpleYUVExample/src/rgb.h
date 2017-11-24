#ifndef _RGB_SIMPLEST_
#define _RGB_SIMPLEST_

/** 
 * Split R, G, B planes in RGB24 file. 
 * @param url  Location of Input RGB file. 
 * @param w    Width of Input RGB file. 
 * @param h    Height of Input RGB file. 
 * @param num  Number of frames to process. 
 * 
 */  
int simplest_rgb24_split(char *url, int w, int h,int num);

/** 
 * Convert RGB24 file to BMP file 
 * @param rgb24path    Location of input RGB file. 
 * @param width        Width of input RGB file. 
 * @param height       Height of input RGB file. 
 * @param url_out      Location of Output BMP file. 
 */  
int simplest_rgb24_to_bmp(const char *rgb24path,int width,int height,const char *bmppath);

/** 
 * Convert RGB24 file to YUV420P file 
 * @param url_in  Location of Input RGB file. 
 * @param w       Width of Input RGB file. 
 * @param h       Height of Input RGB file. 
 * @param num     Number of frames to process. 
 * @param url_out Location of Output YUV file. 
 */  
int simplest_rgb24_to_yuv420(char *url_in, int w, int h,int num,char *url_out);


#endif
