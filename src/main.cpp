#include <iostream>
#include <filesystem>
#include <windows.h>
#include <glad/glad.h> //先包含glad, 后包含glfw
#include <GLFW/glfw3.h>
#include"my_log.h"
#include"myglfw.h"
#include"mywindow.h"
#include"utilities.h"
#include <glog/logging.h>

using namespace std;
//渲染程序标识符
static GLuint renderingProgram;
//顶点个数
#define numVAOs 1
//顶点数组
GLuint vao[numVAOs];
//窗口长宽
GLuint SCR_WIDTH = 800;
GLuint SCR_HEIGHT = 600;

static void error_callback(int error, const char *description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc,char *argv[]){
    cout << "enter main" << endl;
   google::InitGoogleLogging(argv[0]); 
   google::SetLogDestination(google::GLOG_INFO, "./logs/info_");  // INFO级别的日志将被保存到 info_*.log 文件
   LOG(INFO) << "Found " << 100 << " cookies"; 
    LOG_INFO("Enter main");
    //设置glfw错误回调
    glfwSetErrorCallback(error_callback);
    //glfw初始化
    myglfw my_glfw;

	if(!my_glfw.init()){
		LOG_ERR("my_glfw.init");
		return -1;
	}
    LOG_INFO("my_glfw.init");
    //设置OpenGL上下文版本和模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置opengl主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置opengl次版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置OpenGL核心模式
    //创建窗口和上下文
    mywindow my_window;
	GLFWwindow *window = my_window.create(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); 
	if (window == NULL)
	{
		LOG_ERR("my_window.create");
		return -1;
	}
    //设为当前上下文
    glfwMakeContextCurrent(window); 
    //加载glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {//加载glad
		LOG_ERR("gladLoadGLLoader");
        return -1;
	}
    //设置GLFW按键回调
    glfwSetKeyCallback(window, key_callback); 
    //设置缓冲区交换机制
    glfwSwapInterval(1);
    //创建shader程序 
    renderingProgram = glCreateProgram();
    string exepath;
    #ifdef _WIN32 //win 32 or 64
        char path[MAX_PATH];
        DWORD ret = GetModuleFileNameA(NULL,path,MAX_PATH);
        if(ret){
            exepath = path;
        }
        else{
            return -1;
        }
    #else
    #endif
    const string vpath = "D:\\OneDrive\\learnopengl\\src\\09\\vshaderSource.glsl";
    const string fpath = "D:\\OneDrive\\learnopengl\\src\\09\\fshaderSource.glsl";
    GLuint vref = create_shader(vpath,GL_VERTEX_SHADER);
    GLuint fref = create_shader(fpath,GL_FRAGMENT_SHADER);
    if(vref){
        glAttachShader(renderingProgram,vref);
    }
    if(fref){
        glAttachShader(renderingProgram,fref);
    }
    glLinkProgram(renderingProgram);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    //设置OpenGL默认缓冲底色
    glClearColor(1.0, 0.0, 0.0, 1.0);
    //清空缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);
    glPointSize(30.0f); //设置点的大小为30
    glDrawArrays(GL_POINTS, 0, 1);
    //交换缓冲区
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window)){
        //处理屏幕事件
        glfwPollEvents();
    }
    //程序退出
    LOG_INFO("return 0");
    return 0;
} 
//glfw错误回调
void error_callback(int error, const char *description){
	fprintf(stderr, "Error: %s\n", description);
}
//glfw按键回调
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){//ESC按键回调函数
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}