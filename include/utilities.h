#ifndef __UTINITIES_H_
#define __UTINITIES_H_
#include <string>
#include <glad/glad.h>
using namespace std;

GLuint create_shader(const string path,GLenum shaderType);
string read_shader_file(const string path);

#endif