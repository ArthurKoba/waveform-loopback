#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "loopback.hpp"
#include <vector>
#include <thread>

class Visualizer final
{
public:
    Visualizer();
    ~Visualizer() = default;
    void Render(double dt, int width, int height);
private:
    void PopulateAmplitudes(void);
    void LerpAmplitudes(double dt);

    std::vector<float> m_NewAmplitudes;
    std::vector<float> m_Amplitudes;
    Loopback m_LoopbackCapture;
};

#endif 