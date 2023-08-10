#ifndef LOOPBACK_HPP
#define LOOPBACK_HPP

#include <audioclient.h>
#include <mmdeviceapi.h>
#include <functional>

using LoopCB = std::function<void(BYTE *, UINT32)>;

class Loopback final
{
public:
    Loopback() = default;
    ~Loopback();
    void Initialize();
    void Start(LoopCB loop_func);

    const WAVEFORMATEX &GetFormat() const { return *m_CaptureFormat; }
private:
    IMMDeviceEnumerator *m_DeviceEnum;
    IAudioClient *m_AudioClient;
    IAudioCaptureClient *m_AudioCaptureClient;
    IMMDevice *m_Device;
    WAVEFORMATEX *m_CaptureFormat;
};

#endif