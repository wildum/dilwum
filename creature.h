#ifndef CREATURE
#define CREATURE

#include "vec.h"
#include "config.h"
#include "neuron.h"
#include "food.h"
#include "brain.h"

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
    Creature(Vec pos, int angle, size_t id, const std::vector<uint32_t>& genome);
    void pickRandomAction();
    void pickAction();
    void performAction(std::vector<Food>& food);
    void setAction(Output iaction){m_action = iaction;}
    void setAngle(int angle){m_angle = angle;}
    void setSpeed(int speed){m_speed = speed;}
    const Vec& getPosition() const {return m_position;}
    int getAngle() {return m_angle;}
    int getHealth() {return m_health;}
    const int getRadius() const {return m_radius;}
    void decayHealth() {m_health--;}
    bool isAlive() {return m_health > 0;}
    Vec getMouthPosition();
    Vec getLeftAntennaPosition();
    Vec getRightAntennaPosition();
    void processInputs(std::vector<Food>& food, std::vector<Creature>& creatures);
    FrameCreature toFrameCreature() const;
private:
    AntennaTouch antennaTouchFeedback(const Vec& antennaPosition, std::vector<Food>& food, std::vector<Creature>& creatures);
    Taste taste(std::vector<Food>& food);
    void eat(std::vector<Food>& food);
    Brain m_brain;
    Vec m_position;
    int m_angle;
    Output m_action;
    size_t m_id;
    int m_speed = config::CREATURE_SPEED;
    int m_radius = config::CREATURE_RADIUS;
    int m_health = config::CREATURE_HEALTH;
};

#endif