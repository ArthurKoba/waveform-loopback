#include "visualizer.hpp"
#include "loopback.hpp"
#include <GLFW/glfw3.h>

Visualizer::Visualizer() : m_LoopbackCapture{}
{
    m_LoopbackCapture.Initialize();
}

void Visualizer::Render(double dt, int width, int height)
{
    PopulateAmplitudes();
    LerpAmplitudes(dt * 10.0);

    glPointSize(2);
	glLineWidth(2);
    glColor4f(1.0, 1.0, 1.0, 1.0);
 
 	glBegin(GL_LINE_STRIP);

    int numSamples = m_Amplitudes.size();

    for (int i = 0; i < numSamples; ++i)
    {
        float x = ((float)i / numSamples) * width * 4.0f;
        float y = height * (0.5f - m_Amplitudes[i]);
        glVertex3f(x, y, 0.0f);
    }

	glEnd();
}

void Visualizer::PopulateAmplitudes(void)
{
    auto func = [this](BYTE *data, UINT32 len) 
    {
        float *input = (float *)data;
        if (data == NULL)
            m_NewAmplitudes.assign(len, 0.0f);
        else
            m_NewAmplitudes.assign(input, input + len);
    };

    m_LoopbackCapture.Start(func);
}

void Visualizer::LerpAmplitudes(double dt)
{
    if (m_Amplitudes.empty() || m_Amplitudes.size() != m_NewAmplitudes.size())
    {
        m_Amplitudes.assign(m_NewAmplitudes.begin(), m_NewAmplitudes.end());
    }
    else
    {
        int size = m_Amplitudes.size();

        for (int i = 0; i < size; ++i)
        {
            if (m_Amplitudes[i] < m_NewAmplitudes[i])
                m_Amplitudes[i] = m_NewAmplitudes[i];
            else
                m_Amplitudes[i] += (m_NewAmplitudes[i] - m_Amplitudes[i]) * dt;
        }
    }
}
