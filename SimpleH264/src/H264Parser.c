#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	NALU_TYPE_SLICE=1,
	NALU_TYPE_DPA=2,
	NALU_TYPE_DPB=3,
	NALU_TYPE_DPC=4,
	NALU_TYPE_IDR=5,
	NALU_TYPE_SEI=6,
	NALU_TYPE_SPS=7,
	NALU_TYPE_PPS=8,
	NALU_TYPE_AUD=9,
	NALU_TYPE_EOSEQ=10,
	NALU_TYPE_EOSTREAM=11,
	NALU_TYPE_FILL=12
} NaluType;

typedef enum{
	NALU_PRIORITY_DISPOSABLE=0,
	NALU_PRIORITY_LOW=1,
	NALU_PRIORITY_HIGH=2,
	NALU_PRIORITY_HIGHEST=3
} NaluPriority;

//represent a NALU item
typedef struct{
	int startcodeprefix_len;//nalu prefix ,0x00000001 present one frame
	unsigned int len;
	unsigned int max_size;
	int forbidden_bit;//when network error the forbidden set to 1
	int nal_reference_idc;//the priority of nalu,low priority will be discard when necessary.
	int nal_unit_type;
	char *buf;//contain of nalu
} Nalu_t;

FILE *h264bitstream=NULL;

int info2=0,info3=0;

static int FindStartCode2(unsigned char *Buf){
	if(Buf[0]!=0||Buf[1]!=0||Buf[2]!=1){//ox000001? 
		return 0;	
	}
	return 1;
}

static int FindStartCode3(unsigned char *Buf){
	if(Buf[0]!=0||Buf[1]!=0||Buf[2]!=0||Buf[3]!=1){//ox00000001? start of a frame
		return 0;	
	}
	return 1;
}

int GetAnnexbNALU(Nalu_t *nalu){
	int pos =0;
	int startCodeFound,rewind;
	unsigned char *Buf;
	
	if((Buf=(unsigned char*)calloc(nalu->max_size,sizeof(char)))==NULL){
		printf("GetAnnexbNANLU:Could not allocate buf memory\n");
		return 0;
	}

	//find 0x000001 or ox00000001
	nalu->startcodeprefix_len=3;

	if(3!=fread(Buf,1,3,h264bitstream)){
		free(Buf);
		return 0;
	}
	
	info2=FindStartCode2(Buf);

	if(info2!=1){
		if(1!=fread(Buf+3,1,1,h264bitstream)){
			free(Buf);
			return 0;
		}

		info3=FindStartCode3(Buf);
		if(info3!=1){
			free(Buf);
			return 0;
		}
		else{
			pos=4;
			nalu->startcodeprefix_len=4;
		}
	}
	else{
			pos=3;
			nalu->startcodeprefix_len=3;
	}
	startCodeFound=0;
	info2=0;
	info3=0;

	//fill nalu	
	while(!startCodeFound){
		//the last nalu
		if(feof(h264bitstream)){
			nalu->len=(pos-1)-nalu->startcodeprefix_len;
			memcpy(nalu->buf,&Buf[nalu->startcodeprefix_len],nalu->len);
			//nalu head occupy 1 byte
			nalu->forbidden_bit=nalu->buf[0]&0x80; //1 bit
			nalu->nal_reference_idc = nalu->buf[0] & 0x60;//2 bit
			nalu->nal_unit_type=(nalu->buf[0])&0x1f;
			free(Buf);
			return pos-1;
		}
		
		Buf[pos++]=fgetc(h264bitstream);
		info3 = FindStartCode3(&Buf[pos-4]);  
        	if(info3 != 1)  
            		info2 = FindStartCode2(&Buf[pos-3]);  
        	startCodeFound = (info2 == 1 || info3 == 1);  
	}

	rewind=(info3==1)?-4:-3;
	if(0!=fseek(h264bitstream,rewind,SEEK_CUR)){
		free(Buf);
		printf("GetAnnexbNALU: Cannot fseek in the bit stream file");  
		return;
	}

	nalu->len = (pos+rewind)-nalu->startcodeprefix_len;  
    	memcpy (nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);//  
    	nalu->forbidden_bit = nalu->buf[0] & 0x80; //1 bit  
    	nalu->nal_reference_idc = nalu->buf[0] & 0x60; // 2 bit  
    	nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;// 5 bit  
    	free(Buf);  
  
    	return (pos+rewind);
}

int simplest_h264_parser(char * url){
	Nalu_t *n;
	int buffersize=100000;
	
	FILE *myout=stdout;	
	h264bitstream=fopen(url,"r");
	if(h264bitstream==NULL)
	{
		printf("Open file error\n");  
        	return 0;  
	}
	
	n=(Nalu_t*)calloc(1,sizeof(Nalu_t));
	if(n==NULL){
		printf("Alloc NALU Error\n");  
        	return 0;	
	}
	
	n->max_size=buffersize;
	n->buf=(char *)calloc(buffersize,sizeof(char));
	if(n->buf==NULL){
		free(n);
		printf("Alloc NALU buf Error\n");  
        	return 0;	
	}

	int data_offset=0;  
    	int nal_num=0;  
    	printf("-----+-------- NALU Table ------+---------+\n");  
    	printf(" NUM |    POS  |    IDC |  TYPE |   LEN   |\n");  
    	printf("-----+---------+--------+-------+---------+\n");  
  
    	while(!feof(h264bitstream))   
    	{  
    	    int data_lenth;  
    	    data_lenth=GetAnnexbNALU(n);  
  
    	    char type_str[20]={0};  
    	    switch(n->nal_unit_type){  
    	        case NALU_TYPE_SLICE:sprintf(type_str,"SLICE");break;  
    	        case NALU_TYPE_DPA:sprintf(type_str,"DPA");break;  
    	        case NALU_TYPE_DPB:sprintf(type_str,"DPB");break;  
    	        case NALU_TYPE_DPC:sprintf(type_str,"DPC");break;  
    	        case NALU_TYPE_IDR:sprintf(type_str,"IDR");break;  
    	        case NALU_TYPE_SEI:sprintf(type_str,"SEI");break;  
    	        case NALU_TYPE_SPS:sprintf(type_str,"SPS");break;  
    	        case NALU_TYPE_PPS:sprintf(type_str,"PPS");break;  
    	        case NALU_TYPE_AUD:sprintf(type_str,"AUD");break;  
    	        case NALU_TYPE_EOSEQ:sprintf(type_str,"EOSEQ");break;  
    	        case NALU_TYPE_EOSTREAM:sprintf(type_str,"EOSTREAM");break;  
    	        case NALU_TYPE_FILL:sprintf(type_str,"FILL");break;  
    	    }  
    	    char idc_str[20]={0};  
    	    switch(n->nal_reference_idc>>5){  
    	        case NALU_PRIORITY_DISPOSABLE:sprintf(idc_str,"DISPOS");break;  
    	        case NALU_PRIORITY_LOW:sprintf(idc_str,"LOW");break;  
    	        case NALU_PRIORITY_HIGH:sprintf(idc_str,"HIGH");break;  
    	        case NALU_PRIORITY_HIGHEST:sprintf(idc_str,"HIGHEST");break;  
    	    }  
  
    	    fprintf(myout,"%5d| %8d| %7s| %6s| %8d|\n",nal_num,data_offset,idc_str,type_str,n->len);  
  
    	    data_offset=data_offset+data_lenth;  
  
    	    nal_num++;  
    	}  
  
    	//Free  
    	if (n){  
    	    if (n->buf){  
    	        free(n->buf);  
    	        n->buf=NULL;  
    	    }  
    	    free (n);  
    	}  
    	return 0;  	
}

int main(){
	simplest_h264_parser("sintel.h264"); 
}
