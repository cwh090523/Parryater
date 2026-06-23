#pragma once
#include <string>
#include <map>
#include "Fmod/inc/fmod.hpp"

#define SOUND SoundManager::GetInst()

class SoundManager
{
private:
    SoundManager() = default;
    ~SoundManager() = default;

public:
    static SoundManager* GetInst()
    {
        if (m_pInst == nullptr)
            m_pInst = new SoundManager;

        return m_pInst;
    }

    void Init();
    void Update();
    void Release();

    void Load(const std::string& key, const std::string& filePath);
    void PlaySFX(const std::string& key);

    void PlayBGM(const std::string& key);
    void StopBGM();

    void SetBGMVolume(float volume);
    void SetSFXVolume(float volume);

private:
    static SoundManager* m_pInst;

    FMOD::System* m_system = nullptr;

    FMOD::Channel* m_bgmCh = nullptr;
    FMOD::Channel* m_sfxCh = nullptr;

    std::map<std::string, FMOD::Sound*> m_sounds;

    float m_bgmVolume = 0.5f;
    float m_sfxVolume = 0.5f;
};