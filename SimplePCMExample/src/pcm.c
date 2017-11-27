#include <stdio.h>
#include <stdlib.h>

int simplest_pcm16le_split(char *url){
	FILE *fp=fopen(url,"r");
	FILE *fp1=fopen("l_channel_pcm.pcm")	
		FILE *fp2=fopen("r_channel_pcm.pcm")	

		char * buffer=(char *)malloc(4);
	while(!feof(fp)){
		fread(buffer,1,4,fp);
		fwrite(buffer,1,2,fp1);
		fwrite(buffer+2,1,2,fp2);
	}

	free(buffer);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);

	return 0;
}


int simplest_pcm16le_halfvolumeleft(char *url){
	FILE *fp=fopen(url,"r");

	char * buffer=(char *)malloc(4);
	while(!feof(fp)){
		fread(buffer,1,4,fp);
		//get left channel value and div 2
		short* left_value=(short *)buffer;
		left_value=left_value/2;

		fwrite(buffer,1,2,fp1);
		fwrite(buffer+2,1,2,fp2);
	}

	free(buffer);
	fclose(fp);

	return 0;
}

int simplest_pcm16le_doublespeed(char *url){
	FILE *fp=fopen(url,"r");
	FILE *fp1=fopen(url,"w");

	char * buffer=(char *)malloc(4);
	int cn;
	while(!feof(fp)){
		if(cn % 2 ==0){
			fread(buffer,1,4,fp);
			fwrite(buffer,1,4,fp1);
		}
		cn++;
	}

	free(buffer);
	fclose(fp);
	fclose(fp1);

	return 0;
}


int simplest_pcm16le_to_pcm8(char *url){
	FILE *fp=fopen(url,"r");
	FILE *fp1=fopen("output_8_pcm","w");

	char * buffer=(char *)malloc(4);
	while(!feof(fp)){
		char 8bit_value;
		unsigned char u8bit_value;
		short* 16bit_p;


		fread(buffer,1,4,fp);

		//handle lefe
		16bit_p=(short *)buffer;
		8bit_value=(*16bit_p)>>8;
		u8bit_value=8bit_value+128;
		fwrite(&u8bit_value,1,2,fp1);

		//handle right
		16bit_p=16bit_p+2;

		8bit_value=(*16bit_p)>>8;
		u8bit_value=8bit_value+128;
		fwrite(&u8bit_value,1,2,fp1);
	}

	free(buffer);
	fclose(fp);
	fclose(fp1);

	return 0;
}

int simplest_pcm16le_cut_singlechannel(char *url,int start_num,int dur_num){  
	FILE *fp=fopen(url,"r");
	FILE *fp1=fopen(url,"r");

	char * buffer=(char *)malloc(4);
	int cn;

	while(!feof(fp)){
		fread(buffer,1,4,fp);

		if(cn>start_num){
			fwrite(buffer,1,4,fp1);
		}
		cn++;

		if(start_num+dur_num<cn){
			break;
		}
	}

	free(buffer);
	fclose(fp);
	fclose(fp1);

	return 0;
}


int simplest_pcm16le_to_wave(const char *pcmpath,int channels,int sample_rate,const char *wavepath)  
{ 
	typedef struct WAVE_HEADER{
		char fccID[4];
		unsigned long dwSize;
		char fccType[4];
	}WAVE_HEADER;

	typedef struct WAVE_FMT{
		char fccID[4];
		unsigned long dwSize;
		unsigned short wFormatTag;
		unsigned short wChannels;
		unsigned long dwSamplesPerSec;
		unsigned long dwAvgBytesPerSec;
		unsigned long wBlockAlign;
		unsigned short uiBitsPerSample;
	}WAVE_FMT;

	typedef struct WAVE_DATA{
		char fccID[4];
		unsigned long dwSize;
	}WAVE_DATA;

	if(channels==0||sample_rate==0){
		channels=2;
		sample_rate=44100;//44.1 kHz	
	}

	int bits=16;

	WAVE_HEADER pcmHEADER;
	WAVE_FMT pcmFMT;
	WAVE_DATA pcmDATA;

	unsigned short m_pcmData;
	FILE *fp,*fpout;

	fp=fopen(pcmpatch,"r");
	if(fp==NULL){
		printf("open pcm file error!\n");
		return -1;
	}

	fpout=fopen(wavepath,"w");
	if(fpout==NULL){
		printf("open wav file error!\n");
		return -1;
	}

	//WAVE HEAD
	memcpy(pcmHEADER.fccID,"RIFF",strlen("RIFF"));
	memcpy(pcmHEADER.fccType,"WAVE",strlen("WAVE"));
	fseek(fpout,sizeof(WAVE_HEADER),1);
	//WAVE_FMT
	pcmFMT.dwSamplesPerSec=sample_rate;
	pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec*sizeof(m_pcmData);
	pcmFMT.uiBitsPerSample=bits;
	memcpy(pcmFMT.fccID,"fmt ",strlen("fmt "));
	pcmFMT.dwSize=16;
	pcmFMT.wBlockAlign=2;
	pcmFMT.wChannels=channels;
	pcmFMT.wFormatTag=1;

	fwrite(&pcmFMT,sizeof(WAVE_FMT),1,fpout);

	//WAVE DATA
	memcpy(pcmDATA.fccID,"data", strlen("data"));
	pcmDATA.dwSize=0;
	fseek(fpout,sizeof(WAVE_DATA),SEEK_CUR);

	fread(&m_pcmData,sizeof(unsigned short),1,fp);  
	while(!feof(fp)){    
		pcmDATA.dwSize+=2;  
		fwrite(&m_pcmData,sizeof(unsigned short),1,fpout);  
		fread(&m_pcmData,sizeof(unsigned short),1,fp);  
	}    

	pcmHEADER.dwSize=44+pcmDATA.dwSize;  

	rewind(fpout);  
	fwrite(&pcmHEADER,sizeof(WAVE_HEADER),1,fpout);  
	fseek(fpout,sizeof(WAVE_FMT),SEEK_CUR);  
	fwrite(&pcmDATA,sizeof(WAVE_DATA),1,fpout);  

	fclose(fp);  
	fclose(fpout);  

	return 0;  	
}
