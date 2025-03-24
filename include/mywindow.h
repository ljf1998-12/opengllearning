#ifndef _MY_WINDOW_H_
#define _MY_WINDOW_H_
#include <GLFW/glfw3.h>
#include"my_log.h"

class mywindow{
public:
    mywindow(){

    }
    ~mywindow(){
        if(windowNeedDestroy){
            glfwDestroyWindow(window);
            LOG_INFO("glfwDestroyWindow");
        }
    }
    GLFWwindow *create(int width,int height,const char *title,GLFWmonitor *monitor,GLFWwindow *share){
        window = glfwCreateWindow(width, height, title, monitor, share);
        if (window == NULL){
            return NULL;
        }
        setwindowNeedDestroy();
        return window;
    }
    void setwindowNeedDestroy(){
        windowNeedDestroy = true;
    }
private:
    bool windowNeedDestroy = false;
    GLFWwindow *window = NULL;
};

#endif