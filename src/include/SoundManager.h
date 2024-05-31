#include <SFML/Audio.hpp>
#include <vector>

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

namespace engine
{
class SoundManager
{
    public:
        enum class Sound
        {
            optionChange,
            optionChoose,
            ballRebound
        };

        static void init();
        static void playSound(const Sound sound);
    
    private:
        static const std::vector<std::string> soundFiles;
        static std::vector<sf::Sound> sounds;
        static std::vector<sf::SoundBuffer> soundBuffers;

        SoundManager() = delete;
        SoundManager(const SoundManager& other) = delete;
        SoundManager& operator=(const SoundManager& other) = delete;
};
} // namespace engine


#endif