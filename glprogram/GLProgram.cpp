#include <iostream>
#include <vector>

#include <Vertex.h>
#include <Shader.h>
#include <GLProgram.h>

#include <SOIL.h>

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
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // 左上
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


    //texture
    int width, height;
    unsigned char* image = SOIL_load_image("img.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    mTexture = texture;

}

void GLProgram::render() {

    /*
    GLint location = glGetUniformLocation(mProgram, "myColor");
    GLfloat color[]{1.0f, 1.0f, 0.0f, 1.0f};
    glUniform4fv(location, 1, color);
    */
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
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