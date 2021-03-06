#include <iostream>
#include <cstring>
#include <vector>

//c++ thread is disable, so using pthread
#include <pthread.h>

// First
//#define GLEW_STATIC
//#include <GL/glew.h>

// Second: glfw
#include <GLWindow.h>

#include <Vertex.h>
#include <Shader.h>

using namespace std;


//委派构造函数
GLWindow::GLWindow() : GLWindow(0, 0, nullptr) {}

GLWindow::GLWindow(int width, int height) : GLWindow(width, height, nullptr) {}

GLWindow::GLWindow(const char * title) : GLWindow(0, 0, title) {}

GLWindow::GLWindow(int width, int height, const char* title) try : GLWindow(title, width, height)
{
    cout << __func__ << endl;
} catch(const std::exception& e)
{
    glfwTerminate();
    std::cerr << e.what() << '\n';
}
 
/////////////////////目标构造函数///////////////////////////////////////
GLWindow::GLWindow(const char* title, int width, int height) {
    //0. init member variable
    if (title != nullptr && strlen(title) > 0) {
        strncpy(mTitile, title, NAMELEN);
        mTitile[NAMELEN] = '\0';
    }

    if (width > 0)
        mWdith = width;

    if (height > 0)
        mHeight = height;
    
    //1. init glfw
    initAndConfig();

    //2. create window
    mWindow = glfwCreateWindow(mWdith, mHeight, mTitile, nullptr, nullptr);
    if (mWindow == nullptr) {
        //Terminates the GLFW library. because inited
        glfwTerminate();
        throw("Failed to create GLFW window");
    }

    //3. set current context
    glfwMakeContextCurrent(mWindow);

    /*
    //4. init glew
    // 让glew来管理OpenGL中的函数指针

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw("Failed to initialize GLEW");
    }
    
    //5. 视口
    int w, h;
    glfwGetFramebufferSize(mWindow, &w, &h);
    glViewport(0, 0, w, h);
    */
}

GLWindow::~GLWindow() {
    cout << "deconstruct GLWindow" << endl;
    stop();
    mProgram = nullptr;
    glfwTerminate();
}

void GLWindow::initAndConfig() {
    if (glfwInit() != GL_TRUE)
        throw("glfwInit failed");
    
    //设置version，和设置shader相似
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //设置窗口是否可变大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void GLWindow::setRender(FunEntry entry) {
    mEntry = entry;
}

void GLWindow::setProgram(std::shared_ptr<GLProgram> & program) {
    mProgram = program;
}

void GLWindow::start() {
    mExitThread = false;
    startRender();
}

void GLWindow::stop() {
    mExitThread = true;
    if (mHandle != 0UL) {
        pthread_join(*((pthread_t*)(&mHandle)), NULL);
        mHandle = 0UL;
    }
}

//static
void *GLWindow::threadEntry(void *glw) {
    return ((GLWindow*)glw)->run();
}

void * GLWindow::run() {
    while (!mExitThread && !glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
        
        if (mEntry != nullptr) {
            mEntry(this);
        }

        glfwSwapBuffers(mWindow);
    }

    return NULL;
}

void GLWindow::startRender() {
    int ret;

    ret = pthread_create((pthread_t*)(&mHandle), NULL, threadEntry, this);
    
    if (ret != 0) {
        cout << "create render thread failed." << endl;
        return;
    }
}

bool GLWindow::render()
{
    if (glfwWindowShouldClose(mWindow))
        return false;
    glfwPollEvents();

    /*
    glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    */

    glfwSwapBuffers(mWindow);
    return true;
}

void GLWindow::eventLoop() {
    int w, h;
    glfwGetFramebufferSize(mWindow, &w, &h);
    mProgram->setViewPort(w, h);
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
        //gl render
        mProgram->render();

        glfwSwapBuffers(mWindow);
    }
}