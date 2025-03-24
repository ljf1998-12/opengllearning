#include<iostream>
#include<fstream>
#include"utilities.h"
#include"my_log.h"


GLuint create_shader(const string path,GLenum shaderType){
    string shadersource = read_shader_file(path);
    if(shadersource.empty()){
        LOG_ERR("shadersource.empty");
        return 0;
    }
    GLuint shaderref = glCreateShader(shaderType); 
    const char *cshadersource = shadersource.c_str();
    glShaderSource(shaderref,1,&cshadersource,NULL);
    glCompileShader(shaderref);
    return shaderref;
}
string read_shader_file(const string path){
    string content;
    string oneline;
    ifstream istrm(path, ios::in);
    if(!istrm.is_open()){
        LOG_ERR("istrm.is_open");
        return "";
    }
    while(!istrm.eof()){
        getline(istrm, oneline);
        content.append(oneline+'\n');
    }
    LOG_INFO(content);
    return content;
}