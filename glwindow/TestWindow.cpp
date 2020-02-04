#include <iostream>
#include <memory>

#include <vector>
#include <array>
#include <algorithm>

#include <GLWindow.h>
#include <GLProgram.h>

using namespace std;


int main(int argc, char *argv[])
{
    shared_ptr<GLWindow> gwidow(new GLWindow());
    shared_ptr<GLProgram>glpro(new GLProgram("xxx"));
    //cout << glpro.use_count() << endl;
    gwidow->setProgram(glpro);
    //cout << glpro.use_count() << endl;
    gwidow->eventLoop();

    return 0;
}