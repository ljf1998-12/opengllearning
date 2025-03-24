#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include"my_log.h"

string current_time(){
    time_t now = time(0);
    tm tstruct = *localtime(&now);
    char buf[64];
    strftime(buf,sizeof(buf),"%Y-%m-%d %X",&tstruct);
    return string(buf);
}

void print_log(const char *file,const int lineNumber,const log_level level, const string msg){
    stringstream log;
    if(INFO == level){
        log << "INFO ";
    }
    else if (ERR == level)
    {
        log << "ERR ";
    }
    log << current_time() << ' ';
    log << file << ':' << lineNumber << ' ';
    log << msg;
    ofstream logfile("D:\\OneDrive\\learnopengl\\src\\09\\mylog",ios::out|ios::app);
    if(logfile.is_open()){
        logfile << log.str() << endl;
    }
    else{
        cout << log.str() << endl; 
    }
}