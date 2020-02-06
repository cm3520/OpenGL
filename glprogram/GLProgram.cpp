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
    /*
    vector<GLfloat> vertices{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    */
    vector<GLfloat> vertices{
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // 顶部
    };

    // opengl主要是用来处理三角形，索引巨型需要通过两个三角形组成
    vector<GLfloat>v{
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    //注意索引值是int型
    vector<GLint>i{ // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw("Failed to initialize GLEW");
    }

    //正方形
    //Vertex vt(v, i);
    CommonCoord<GLfloat, GLint> vv(vector<GLfloat>{
        // 位置              // 颜色
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    }, vector<GLint>{3, 3, 2});

    CommonCoord<GLint, GLint> ii(vector<GLint>{
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    }, {});

    //三角形
    //Vertex vt(vertices);

    Vertex vt(vv, ii);

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, mTexture);

    glBindVertexArray(mVAO);
    //绘三角形
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //绘制矩形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GLProgram::setViewPort(int wdith, int height) {
    glViewport(0, 0, wdith, height);
}

void GLProgram::use() {
    glUseProgram(mProgram);
}

GLProgram::~GLProgram() {
    glDeleteProgram(mProgram);
    mProgram = 0UL;
    glDeleteVertexArrays(1, &mVAO);
    mVAO = 0UL;
    glDeleteTextures(1, &mTexture);
    mTexture = 0UL;
    cout << __func__ << endl;
}