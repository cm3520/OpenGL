#include <iostream>
#include <fstream>
#include <sstream>

#include <Shader.h>

using namespace std;

Shader::Shader(const char* path, ShaderType type) try :Shader(path, type, true)
{
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

Shader::Shader(const char* path, ShaderType type, bool isDelegate) {
    if (path == nullptr)
        throw("Error:ShaderData is null");

    if (type < VSHADER || type >= MAXSHADER)
        throw("Error:type is invalid");

    //文件操作
    string textcode;
    ifstream shaderFile;

    shaderFile.exceptions(ifstream::badbit);

    try
    {
        shaderFile.open(path);

        stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();
        textcode = shaderStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw("open shader file failed");
    }

    //让GLEW在管理OpenGL的函数指针时更多地使用现代化的技术
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw("Failed to initialize GLEW");

    // 获取shader文本
    const GLchar* shaderText = textcode.c_str();

    // 编译Shader
    GLuint shader;

    auto getGLShaderType = [type]()->GLenum{
        GLenum t;
        switch (type) {
            case VSHADER: {
                t = GL_VERTEX_SHADER;
                break;
            }
            case FSHADER: {
                t= GL_FRAGMENT_SHADER;
                break;
            }
        }
        return t;
    };

    shader = glCreateShader(getGLShaderType());
    glShaderSource(shader, 1, &shaderText, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        //需要抛出异常吗???
        cout << "compile shader failed:" << infoLog << endl;
    }

    mShader = shader;
    /*
    GLuint program;
    program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Link program failed:" << infoLog << endl;
    }
    */
    //glDeleteShader(shader);

    //mProgram = program;
}

GLuint Shader::getShader() {
    cout << mShader << endl;
    return mShader;
}

void Shader::deleteShader() {
    glDeleteProgram(mShader);
}

Shader::~Shader() {
    deleteShader();
}