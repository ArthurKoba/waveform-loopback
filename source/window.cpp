#include <GLFW/glfw3.h>

#include "window.hpp"

Window::Window(const std::string &name, int width, int height) : m_WindowName(name), m_Width(width), m_Height(height)
{
    this->InitGLFW();
}

Window::~Window()
{
    this->ShutDownGLFW();
}

void Window::DoMainLoop(void)
{
    double prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        double currentTime = glfwGetTime();
        m_FrameTime = currentTime - prevTime;
        prevTime = currentTime;

        if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED))
        {
            glfwWaitEvents();
        }
        else
        {
            glfwPollEvents();

            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            if (this->m_FrameCallback) this->m_FrameCallback(*this);

            glfwSwapBuffers(m_Window);
        }
    }
}

const int Window::GetFBWidth() const
{
    return m_FBWidth;
}

const int Window::GetFBHeight() const
{
    return m_FBHeight;
}

void Window::InitGLFW()
{
    if (glfwInit() == GLFW_FALSE)
        (printf("GLFW failed to init.\n"), std::exit(EXIT_FAILURE));

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
        (printf("Window couldn't be created\n"), std::exit(EXIT_FAILURE));

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    glViewport(0, 0, m_Width, m_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, m_Width, m_Height, 0.0, 0.0, 1.0);

    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwGetFramebufferSize(m_Window, &m_FBWidth, &m_FBHeight);
    glViewport(0, 0, m_FBWidth, m_FBHeight);
}

void Window::ShutDownGLFW()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
