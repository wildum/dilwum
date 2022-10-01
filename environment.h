#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <vector>
#include <unordered_map>

#include "creatureEntity.h"
#include "foodEntity.h"
#include "frame.h"
#include "brainDrawer.h"
#include "game.h"

class Environment
{
public:
    static void runRaw();
    static void runRework(std::string& fileName);
    static void runReplay(std::string& fileName);
    static sf::Image creatureImage;
    static sf::Texture creatureTexture;
    static sf::Font debugFont;
    static bool debugMode;
private:
    static void initialize();
    static void loadAssets();
    static void play(GameFeedback& gamefeedback);
    static void updateEntities(sf::RenderWindow& window, 
        std::unordered_map<size_t, CreatureEntity>& creatures, 
        std::unordered_map<size_t, FoodEntity>& foods,
        const std::vector<Frame>::iterator& currentFrameIterator,
        const std::vector<Frame>::iterator& nextFrameIterator,
        float time);
    static std::unordered_map<size_t, CreatureEntity> initCreaturesEntities(sf::RenderWindow& window, Frame& firstFrame);
    static std::unordered_map<size_t, FoodEntity> initFoodEntities(sf::RenderWindow& window, Frame& firstFrame);
    static void onPressingMouseButton(BrainDrawer& brainDrawer, GameFeedback& gameFeedback, std::vector<Frame>::iterator& frameIterator, int x, int y);
};

#endif