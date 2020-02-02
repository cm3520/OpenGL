#ifndef _SHADER_H
#define _SHADER_H

#define GLEW_STATIC
#include<GL/glew.h>

typedef enum {
    VSHADER = 0,
    FSHADER,
    MAXSHADER
} ShaderType;

//创建流程是一样的，只有vertex和shader是不一样的
class Shader {
public:
    // For fragment shader
    Shader(const char* path, ShaderType type);

    void useProgram();
    GLuint getProgram();

    ~Shader();
private:
    Shader(const char* path, ShaderType type, bool isDelegate);

    GLuint mProgram{0U};

    Shader& operator=(const Shader&);
};

#endif