#ifndef CREATURE
#define CREATURE

#include "vec.h"
#include "config.h"
#include "action.h"
#include "food.h"

#include <vector>

struct FrameCreature
{
    size_t id;
    Vec position;
    int angle;
    int health;
};

class Creature
{
public:
    Creature(Vec pos, int angle, size_t id);
    void pickRandomAction();
    void performAction(std::vector<Food>& food);
    void setAction(Action iaction){m_action = iaction;}
    void setAngle(int angle){m_angle = angle;}
    const Vec& getPosition() const {return m_position;}
    int getAngle() {return m_angle;}
    int getHealth() {return m_health;}
    void decayHealth() {m_health--;}
    bool isAlive() {return m_health > 0;}
    FrameCreature toFrameCreature() const;
private:
    void eat(std::vector<Food>& food);
    Vec m_position;
    int m_angle;
    Action m_action;
    size_t m_id;
    int m_speed = config::CREATURE_SPEED;
    int m_radius = config::CREATURE_RADIUS;
    int m_health = config::CREATURE_HEALTH;
};

#endif