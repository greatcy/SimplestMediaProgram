#ifndef _SIMPLE_YUV_

#define _SIMPLE_YUV_

/** 
 * Split Y, U, V planes in YUV420P file. 
 * @param url  Location of Input YUV file. 
 * @param w    Width of Input YUV file. 
 * @param h    Height of Input YUV file. 
 * @param num  Number of frames to process. 
 * 
 */  
int simplest_yuv420_split(char *url,int w,int h,int mun);

/** 
 * Split Y, U, V planes in YUV444P file. 
 * @param url  Location of YUV file. 
 * @param w    Width of Input YUV file. 
 * @param h    Height of Input YUV file. 
 * @param num  Number of frames to process. 
 * 
 */  
int simplest_yuv444_split(char *url, int w, int h,int num);

/** 
 * Convert YUV420P file to gray picture 
 * @param url     Location of Input YUV file. 
 * @param w       Width of Input YUV file. 
 * @param h       Height of Input YUV file. 
 * @param num     Number of frames to process. 
 */  
int simplest_yuv420_gray(char *url, int w, int h,int num);

/** 
 * Halve Y value of YUV420P file 
 * @param url     Location of Input YUV file. 
 * @param w       Width of Input YUV file. 
 * @param h       Height of Input YUV file. 
 * @param num     Number of frames to process. 
 */  
int simplest_yuv420_halfy(char *url, int w, int h,int num);

/** 
 * Add border for YUV420P file 
 * @param url     Location of Input YUV file. 
 * @param w       Width of Input YUV file. 
 * @param h       Height of Input YUV file. 
 * @param border  Width of Border. 
 * @param num     Number of frames to process. 
 */  
int simplest_yuv420_border(char *url, int w, int h,int border,int num);

#endif
