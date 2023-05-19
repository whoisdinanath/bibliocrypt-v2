#include <gl-window/gl_init.hpp>
#include <library.hpp>
#include <thread>

// Path: src/gl-window/gl-init.cpp

int main()
{
    std::thread server_thread(server);
    std::thread library_thread(library_func);
    initGLwindow();
    server_thread.join();
    library_thread.join();
    return 0;
}
