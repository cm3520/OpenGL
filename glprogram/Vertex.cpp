#include <Vertex.h>


Vertex::Vertex(const vector<GLfloat> & vertex)
    try : Vertex(true, vertex, vector<GLint>{})
{
    cout << __func__ << endl;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

Vertex::Vertex(const vector<GLfloat> & vertex, const vector<GLint> & indice)
    try : Vertex(true, vertex,  indice)
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}


Vertex::Vertex(bool isDelegate, const vector<GLfloat> & vertex, const vector<GLint> & indice) {
    if (vertex.empty())
        throw("vertex can ");

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);

    if (!indice.empty()) {
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(GLint), indice.data(), GL_STATIC_DRAW);
    }

    //link vertex attribute 注意步长和偏移量的不同
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //可以更加抽象和模块化改进的地方
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


Vertex::Vertex(const CommonCoord<GLfloat, GLint> & coord)
try : Vertex(VBOTYPE, coord, CommonCoord<GLint, GLint>{})
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}


Vertex::Vertex(const CommonCoord<GLfloat, GLint> & coord, const CommonCoord<GLint, GLint> & indice)
try : Vertex(EBOTYPE, coord, indice)
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}


Vertex::Vertex(ConsType type, const CommonCoord<GLfloat, GLint> & coord, const CommonCoord<GLint, GLint> & indice) {
    if (coord.isEmpty())
        throw("coord is not valid");

    if (type == EBOTYPE && indice.mCoord.empty())
        throw("indice is not valid");

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, coord.mCoord.size() * sizeof(GLfloat), coord.mCoord.data(), GL_STATIC_DRAW);

    if (!indice.mCoord.empty()) {
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.mCoord.size() * sizeof(GLint), indice.mCoord.data(), GL_STATIC_DRAW);
    }

    int stride = coord.stride();

    for (int i = 0, offset = 0; i < coord.mIndex.size(); ++i, offset = 0) {
        if (i > 0) {
            for (int j = 0; j < i; ++j) {
                offset += coord.mIndex[j];
            }
        }
        glVertexAttribPointer(i, coord.mIndex[i], GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }

    /*
    //link vertex attribute 注意步长和偏移量的不同
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //可以更加抽象和模块化改进的地方
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    */

    glBindVertexArray(0);
}



GLuint Vertex::getVAO() {
    cout << "VAO: " << mVAO <<endl;
    return mVAO;
}

Vertex::~Vertex() {
    cout << __func__ << endl;
}