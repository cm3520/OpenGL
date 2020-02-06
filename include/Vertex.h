_Pragma("once")

#include <iostream>
#include <vector>
#include <algorithm>

#define GLEW_STATIC
#include<GL/glew.h>

using namespace std;

class Vertex;

template<typename T1, typename T2>
class CommonCoord {
public:

    CommonCoord()=default;

    //右值引用的都是常量表达式，不能引用一个变量，即左值。
    CommonCoord(vector<T1>&& coord, vector<T2>&& index) : mCoord(coord), mIndex(index) {
        //for test
        for_each(mCoord.begin(), mCoord.end(), [](T1 x){cout << x << " ";});
        cout << endl;
        for_each(mIndex.begin(), mIndex.end(), [](T2 x){cout << x << " ";});
        cout << endl;
    }

    void *operator new(size_t) = delete;

    //非const函数，const的应用变量将无法调用
    bool isEmpty() const {
        if (mCoord.empty() || mIndex.empty())
            return true;
        else
            return false;
    }

    int stride ()  const {
        int stride = 0;
        for (auto i:mIndex)
            stride += i;
        return stride;
    }

    ~CommonCoord() {}

private:
    friend Vertex;

    vector<T1> mCoord{};
    vector<T2> mIndex{};

    CommonCoord(const CommonCoord &)=delete;
    CommonCoord & operator=(const CommonCoord&)=delete;
};

 
class Vertex {
public:
    Vertex(const vector<GLfloat> & vertex);
    Vertex(const vector<GLfloat> & vertex, const vector<GLint> & indice);

    ////////////////////////////////////////////////////////////////////////////////////////////
    Vertex(const CommonCoord<GLfloat, GLint> & coord);
    Vertex(const CommonCoord<GLfloat, GLint> & coord, const CommonCoord<GLint, GLint> & indice);
    ////////////////////////////////////////////////////////////////////////////////////////////

    GLuint getVAO();

    ~Vertex();

private:
    Vertex(bool isDelegate, const vector<GLfloat> & vertex, const vector<GLint> & indice);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef enum {
        VBOTYPE = 0,
        EBOTYPE,
        MAXTYPE
    } ConsType;

    Vertex(ConsType type, const CommonCoord<GLfloat, GLint> & coord, const CommonCoord<GLint, GLint> & indice);

    GLuint mVAO{0U};    
};