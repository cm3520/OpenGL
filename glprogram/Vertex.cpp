#include <Vertex.h>


Vertex::Vertex(const vector<GLfloat> & vertex)
    try : Vertex(true, vertex)
{
    cout << __func__ << endl;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

Vertex::Vertex(bool isDelegate, const vector<GLfloat> & vertex) {
    if (vertex.empty())
        throw("vertex can ");

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);

    //link vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

GLuint Vertex::getVAO() {
    return mVAO;
}

Vertex::~Vertex() {
    cout << __func__ << endl;
}