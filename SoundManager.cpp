#include "SoundManager.h"
#include <algorithm>

#pragma comment(lib, "fmod_vc.lib")

SoundManager* SoundManager::m_pInst = nullptr;

void SoundManager::Init()
{
    FMOD::System_Create(&m_system);

    if (m_system != nullptr)
    {
        m_system->init(32, FMOD_INIT_NORMAL, nullptr);
    }
}

void SoundManager::Update()
{
    if (m_system != nullptr)
        m_system->update();
}

void SoundManager::Release()
{
    for (auto& pair : m_sounds)
    {
        if (pair.second != nullptr)
            pair.second->release();
    }

    m_sounds.clear();

    StopBGM();

    if (m_system != nullptr)
    {
        m_system->close();
        m_system->release();
        m_system = nullptr;
    }
}

void SoundManager::Load(const std::string& key, const std::string& filePath)
{
    if (m_system == nullptr)
        return;

    if (m_sounds.find(key) != m_sounds.end())
        return;

    FMOD::Sound* sound = nullptr;

    m_system->createSound(
        filePath.c_str(),
        FMOD_DEFAULT,
        nullptr,
        &sound
    );

    if (sound != nullptr)
        m_sounds[key] = sound;
}

void SoundManager::PlaySFX(const std::string& key)
{
    if (m_system == nullptr)
        return;

    auto it = m_sounds.find(key);

    if (it == m_sounds.end())
        return;

    FMOD::Channel* channel = nullptr;

    m_system->playSound(
        it->second,
        nullptr,
        false,
        &channel
    );

    if (channel != nullptr)
        channel->setVolume(m_sfxVolume);
}

void SoundManager::PlayBGM(const std::string& key)
{
    if (m_system == nullptr)
        return;

    auto it = m_sounds.find(key);

    if (it == m_sounds.end())
        return;

    StopBGM();

    it->second->setMode(FMOD_LOOP_NORMAL);

    m_system->playSound(
        it->second,
        nullptr,
        false,
        &m_bgmCh
    );

    if (m_bgmCh != nullptr)
        m_bgmCh->setVolume(m_bgmVolume);
}

void SoundManager::StopBGM()
{
    if (m_bgmCh != nullptr)
    {
        m_bgmCh->stop();
        m_bgmCh = nullptr;
    }
}

void SoundManager::SetBGMVolume(float volume)
{
    m_bgmVolume = std::max(0.0f, std::min(1.0f, volume));

    if (m_bgmCh != nullptr)
        m_bgmCh->setVolume(m_bgmVolume);
}

void SoundManager::SetSFXVolume(float volume)
{
    m_sfxVolume = std::max(0.0f, std::min(1.0f, volume));
}