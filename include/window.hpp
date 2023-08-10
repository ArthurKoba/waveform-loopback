#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <functional>
#include <string>
#include <memory>

struct GLFWwindow;

class Window final 
{
public:
    using FrameCallback = std::function<void(const Window &)>;
    Window(const std::string &name, int width, int height);
    ~Window();

    void SetFrameCallback(FrameCallback cb) { m_FrameCallback = cb; }
    void DoMainLoop(void);

    const int GetWindowWidth() const { return m_Width; }
    const int GetWindowHeight() const { return m_Height; }
    const int GetFBWidth() const;
    const int GetFBHeight() const;
    const double GetFrameTime() const { return m_FrameTime; }
 
private:
    void InitGLFW();
    void ShutDownGLFW();

    int m_Width, m_Height;
    int m_FBWidth, m_FBHeight;

    GLFWwindow *m_Window;
    std::string m_WindowName;
    FrameCallback m_FrameCallback = nullptr;

    double m_FrameTime;
};

#endif