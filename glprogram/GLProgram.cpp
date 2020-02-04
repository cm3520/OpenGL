#include <iostream>
#include <vector>

#include <Vertex.h>
#include <Shader.h>
#include <GLProgram.h>

using namespace std;


GLProgram::GLProgram(const char * path) try : GLProgram(true, path)
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

GLProgram::GLProgram(bool isDelegate, const char *path) {
    cout << __func__ << endl;
    if (path == nullptr)
        throw("Json's path is null");

    // For Test
    vector<GLfloat>v{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw("Failed to initialize GLEW");
    }

    Vertex vt(v);
    mVAO = vt.getVAO();

    Shader vs("vshader.txt", VSHADER);
    Shader fs("fshader.txt", FSHADER);

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vs.getShader());
    glAttachShader(mProgram, fs.getShader());
    glLinkProgram(mProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
        cout << "Link program failed:" << infoLog << endl;
    }

    vs.deleteShader();
    fs.deleteShader();

    glUseProgram(mProgram);

}

void GLProgram::render() {
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void GLProgram::setViewPort(int wdith, int height) {
    glViewport(0, 0, wdith, height);
}

GLProgram::~GLProgram() {
    glDeleteProgram(mProgram);
    mProgram = 0UL;
    glDeleteVertexArrays(1, &mVAO);
    mVAO = 0UL;
    cout << __func__ << endl;
}