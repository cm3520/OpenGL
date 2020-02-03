#include <iostream>
#include <memory>

#include <vector>
#include <array>
#include <algorithm>

#include <GLWindow.h>

using namespace std;


int main(int argc, char *argv[])
{
    shared_ptr<GLWindow> gwidow(new GLWindow());
    gwidow->eventLoop();

    return 0;
}