#ifndef CREATURE
#define CREATURE

#include "vec.h"
#include "config.h"
#include "action.h"

struct FrameCreature
{
    size_t id;
    Vec position;
    Vec direction;
};

class Creature
{
public:
    Creature(Vec pos, Vec dir, size_t id);
    void pickRandomAction();
    void performAction();
    void decayHealth() {m_health--;}
    bool isAlive() {return m_health > 0;}
    FrameCreature toFrameCreature() const;
private:
    Vec m_position;
    Vec m_direction; // normalized
    Action m_action;
    size_t m_id;
    int m_speed = config::CREATURE_SPEED;
    int m_radius = config::CREATURE_RADIUS;
    int m_health = config::CREATURE_HEALTH;
};

#endif