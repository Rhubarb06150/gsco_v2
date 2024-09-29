#include "headers/colors.h"
#include<cstring>
#include<time.h>
#include<iostream>
#include<string>

void create_log();
void write_to_log(char* type,char* info);
void log(std::string type,std::string info){
	time_t now=time(NULL);
	struct tm *tm_struct=localtime(&now);
	int cur_hour=tm_struct->tm_hour;
	int cur_mins=tm_struct->tm_min;
	int cur_secs=tm_struct->tm_sec;
	char cur_h_str[3];
	char cur_m_str[3];
	char cur_s_str[3];
	sprintf(cur_h_str,"%ld",cur_hour);
	sprintf(cur_m_str,"%ld",cur_mins);
	sprintf(cur_s_str,"%ld",cur_secs);
	char hour[3]="";
	char mins[3]="";
	char secs[3]="";
	if(cur_hour<10){strcpy(hour,"0");};strcat(hour,cur_h_str);
	if(cur_mins<10){strcpy(mins,"0");};strcat(mins,cur_m_str);
	if(cur_secs<10){strcpy(secs,"0");};strcat(secs,cur_s_str);
	std::string col=COL_GREEN;
	if(type=="ENGINE"){
		col=COL_GREEN;
	}else if(type=="ERROR"){
		col=COL_RED;
	};
	int spaces=10;
	spaces-=strlen(type.c_str());
	std::cout<<"[ "<<col<<type<<COL_RESET<<" ]";
	for(int i=0;i<spaces;i++)
		std::cout<<" ";
	std::cout<<hour<<":"<<mins<<":"<<secs<<" // "<<info<<std::endl;
	//printf("[%s%s%s] %s:%s:%s // %s\n",col,log_type,COL_RESET,hour,mins,secs,log_info);
}