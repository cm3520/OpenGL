_Pragma("once")

//使用静态库
#define GLEW_STATIC
#include <GL/glew.h>

class GLProgram {
public:
    //使用json配置顶点和shader
    GLProgram(const char * path);

    void render();
    void setViewPort(int wdith, int height);

    ~GLProgram();
private:
    GLProgram(bool isDelegate, const char *path);

    GLuint mProgram{0UL};
    GLuint mVAO{0UL};
};