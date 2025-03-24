#ifndef _MYGLFW_H_
#define _MYGLFW_H_
#include <GLFW/glfw3.h>
#include"my_log.h"

class myglfw
{
public:
    myglfw(){
    }
    ~myglfw(){
        if(glfwNeedTerminate){
            glfwTerminate();
            LOG_INFO("glfwTerminate");
        }
    }
    void setglfwNeedTerminate(){
        glfwNeedTerminate = true;
    }
    bool init(){
        if(!glfwInit()){
            LOG_ERR("glfwInit");
            return false;
        }
        setglfwNeedTerminate();
        return true;
    }
private:
    bool glfwNeedTerminate = false;
};

#endif