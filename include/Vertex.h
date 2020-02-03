_Pragma("once")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include<GL/glew.h>

using namespace std;
 
class Vertex {
public:
    Vertex(const vector<GLfloat> & vertex);

    GLuint getVAO();

    ~Vertex();

private:
    Vertex(bool isDelegate,const vector<GLfloat> & vertex);

    GLuint mVAO{0U};    
};