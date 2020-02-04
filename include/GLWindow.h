//C++11 _Pragma: 是一个操作符而不是一个预处理指令(#pragma once)，能使用在宏扩展中，灵活性好
_Pragma("once")

#include <memory>

#include <GLProgram.h>

#include <GLFW/glfw3.h>

#define NAMELEN (30)

typedef void* (*FunEntry)(void *arg);

class GLWindow {
public:
    //委派构造函数
    GLWindow();
    GLWindow(int width, int height);
    GLWindow(const char* title);
    GLWindow(int width, int height, const char* title);

    //设置窗口的渲染函数
    void setRender(FunEntry entry);
    void setProgram(std::shared_ptr<GLProgram> & program);

    void start();
    void stop();

    void eventLoop();

    virtual ~GLWindow();

private:
    //目标构造函数
    GLWindow(const char* title, int width, int height);

    // create render thread
    void startRender();

    bool render();

    // For multi thread
    static void *threadEntry(void *glw);
    void * run();

    //init glfw
    void initAndConfig();

    GLFWwindow * mWindow;
    
    //默认窗口大小，窗口默认比率为4:3
    int mWdith{800};
    int mHeight{600};
    char mTitile[NAMELEN + 1]{"Default"};

    FunEntry mEntry{nullptr};

    bool mExitThread{false};
    unsigned long mHandle{0UL};

    std::shared_ptr<GLProgram> mProgram{nullptr};
};