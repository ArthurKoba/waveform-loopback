#include "loopback.hpp"
#include <stdexcept>
#include <thread>
#include <iostream>

#define REFTIMES_PER_SEC 10000000
#define REFTIMES_PER_MILLISEC 10000

#define SAFE_FREE(a)    \
    if ((a) != NULL)    \
    {                   \
        (a)->Release(); \
        (a) = NULL;     \
    }

Loopback::~Loopback()
{
    CoTaskMemFree(m_CaptureFormat);
    SAFE_FREE(m_Device);
    SAFE_FREE(m_DeviceEnum);
    SAFE_FREE(m_AudioClient);
    SAFE_FREE(m_AudioCaptureClient);
}

#define THROW_ERROR_IF(a, b) \
    if (FAILED(a))           \
    throw std::runtime_error("Error: " b)

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);

void Loopback::Initialize(void)
{
    CoInitialize(0);

    THROW_ERROR_IF(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void **)&m_DeviceEnum), "Enumerator");

    THROW_ERROR_IF(m_DeviceEnum->GetDefaultAudioEndpoint(eRender, eConsole, &m_Device), "Device");
    THROW_ERROR_IF(m_Device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, IID_PPV_ARGS_Helper(&m_AudioClient)), "AudioClient");
    THROW_ERROR_IF(m_AudioClient->GetMixFormat(&m_CaptureFormat), "CaptureFormat");

    THROW_ERROR_IF(m_AudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, REFTIMES_PER_SEC, 0, m_CaptureFormat, NULL), "Init");

    UINT32 bufferSize = 0;
    THROW_ERROR_IF(m_AudioClient->GetBufferSize(&bufferSize), "Buffer Size");
    THROW_ERROR_IF(m_AudioClient->GetService(IID_PPV_ARGS(&m_AudioCaptureClient)), "AudioCaptureClient");
    m_AudioClient->Start();
}

void Loopback::Start(LoopCB loop_func)
{
    BYTE *data;
    UINT32 frames, packet_length;
    DWORD flags;

    m_AudioCaptureClient->GetNextPacketSize(&packet_length);

    while (packet_length != 0)
    {
        m_AudioCaptureClient->GetBuffer(&data, &frames, &flags, NULL, NULL);

        if (flags & AUDCLNT_BUFFERFLAGS_SILENT)
            data = NULL;

        loop_func(data, frames * m_CaptureFormat->nChannels * m_CaptureFormat->wBitsPerSample / 8);
        m_AudioCaptureClient->ReleaseBuffer(frames);
        m_AudioCaptureClient->GetNextPacketSize(&packet_length);
    }
}
