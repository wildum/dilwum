#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <vector>
#include <unordered_map>

#include "frame.h"
#include "entity.h"

class Environment
{
public:
    static void run();
    static sf::Image creatureImage;
    static sf::Texture creatureTexture;
private:
    static void initialize();
    static void loadAssets();
    static void updateEntities(sf::RenderWindow& window, 
        std::unordered_map<size_t, CreatureEntity>& creatures, 
        std::unordered_map<size_t, FoodEntity>& foods,
        const std::vector<Frame>::iterator& currentFrameIterator,
        const std::vector<Frame>::iterator& nextFrameIterator,
        float time);
    static std::unordered_map<size_t, CreatureEntity> initCreaturesEntities(sf::RenderWindow& window, Frame& firstFrame);
    static std::unordered_map<size_t, FoodEntity> initFoodEntities(sf::RenderWindow& window, Frame& firstFrame);
};

#endif