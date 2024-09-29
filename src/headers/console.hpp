#ifndef CONSOLE_H
#define CONSOLE_H

#include"colors.h"
#include<string>

void create_log();
void write_to_log(char* type,char* info);
void log(std::string type,std::string info);

#endif
