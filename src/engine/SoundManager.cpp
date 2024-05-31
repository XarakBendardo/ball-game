#include "../include/SoundManager.h"
#include "../include/paths.h"

namespace engine
{

// ORDER MUST FOLLOW ORDER OF THE SoundManager::Sound ENUM!!!
const std::vector<std::string> SoundManager::soundFiles = {
    "/option-change.wav",
    "/option-choose.wav",
    "/ball-rebound.wav"
};

std::vector<sf::Sound> SoundManager::sounds = {};
std::vector<sf::SoundBuffer> SoundManager::soundBuffers = {};

void SoundManager::init()
{
    for(const auto& filename : SoundManager::soundFiles)
    {
        sf::SoundBuffer buffer; buffer.loadFromFile(paths::SOUNDS_DIR + filename);
        sf::Sound sound;
        SoundManager::soundBuffers.push_back(buffer);
        SoundManager::sounds.push_back({});
    }

    for(size_t i = 0; i < SoundManager::sounds.size(); ++i)
        SoundManager::sounds[i].setBuffer(SoundManager::soundBuffers[i]);
    
}

void SoundManager::playSound(const SoundManager::Sound sound)
{
    SoundManager::sounds[(size_t)sound].play();
}

} // namespace engine
