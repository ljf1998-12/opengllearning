#ifndef _MY_LOG_H_
#define _MY_LOG_H_
#define LOG_INFO(msg) print_log(__FILE__,__LINE__,INFO,msg);
#define LOG_ERR(msg) print_log(__FILE__,__LINE__,ERR,msg);

#include<string>
using namespace std;

enum log_level{
    INFO = 1,
    ERR = 2
};
string current_time();
void print_log(const char *file,const int lineNumber,const log_level level, const string msg);

#endif