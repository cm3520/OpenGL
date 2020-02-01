#include <iostream>
#include <memory>

#include <GLWindow.h>

using namespace std;


int main(int argc, char *argv[])
{
    
    shared_ptr<GLWindow> gwidow(new GLWindow());

    while (true) {
        if (!gwidow->render())
            break;
    }

    return 0;
}