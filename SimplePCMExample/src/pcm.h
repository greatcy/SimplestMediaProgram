/** 
 * Split Left and Right channel of 16LE PCM file. 
 * @param url  Location of PCM file. 
 * 
 */  
int simplest_pcm16le_split(char *url);

/** 
 * Halve volume of Left channel of 16LE PCM file 
 * @param url  Location of PCM file. 
 */  
int simplest_pcm16le_halfvolumeleft(char *url);

/** 
 * Re-sample to double the speed of 16LE PCM file 
 * @param url  Location of PCM file. 
 */  
int simplest_pcm16le_doublespeed(char *url);

/** 
 * Convert PCM-16 data to PCM-8 data. 
 * @param url  Location of PCM file. 
 */  
int simplest_pcm16le_to_pcm8(char *url);

/** 
 * Cut a 16LE PCM single channel file. 
 * @param url        Location of PCM file. 
 * @param start_num  start point 
 * @param dur_num    how much point to cut 
 */  
int simplest_pcm16le_cut_singlechannel(char *url,int start_num,int dur_num);

/** 
 * Cut a 16LE PCM single channel file. 
 * @param url        Location of PCM file. 
 * @param start_num  start point 
 * @param dur_num    how much point to cut 
 */  
int simplest_pcm16le_cut_singlechannel(char *url,int start_num,int dur_num);

/** 
 * Convert PCM16LE raw data to WAVE format 
 * @param pcmpath      Input PCM file. 
 * @param channels     Channel number of PCM file. 
 * @param sample_rate  Sample rate of PCM file. 
 * @param wavepath     Output WAVE file. 
 */  
int simplest_pcm16le_to_wave(const char *pcmpath,int channels,int sample_rate,const char *wavepath);
