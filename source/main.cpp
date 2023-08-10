#include <iostream>
#include <stdexcept>
#include <thread>

#include "loopback.hpp"
#include "window.hpp"
#include "visualizer.hpp"

int main(int argc, char *argv[])
{
    Window window("Visualizer", 600, 400);
    Visualizer visualizer;

    window.SetFrameCallback([&visualizer](const Window &w) { visualizer.Render(w.GetFrameTime(), w.GetFBWidth(), w.GetFBHeight()); });
    window.DoMainLoop();
    return 0;
}
