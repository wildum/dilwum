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
    void reset();
    void pickRandomAction();
    void pickAction();
    void performAction(std::vector<Food>& food);
    void setAction(Output iaction){m_action = iaction;}
    void setAngle(int angle){m_angle = angle;}
    void setSpeed(int speed){m_speed = speed;}
    void setScore(float score){m_score = score;}
    void setHealth(int value){m_health = value;}
    const Vec& getPosition() const {return m_position;}
    int getAngle() {return m_angle;}
    const int getHealth() const {return m_health;}
    const int getRadius() const {return m_radius;}
    const int getDeadAt() const {return m_deadAt;}
    const float getScore() const {return m_score;}
    const int getId() const {return m_id;}
    Brain& getBrain() {return m_brain;}
    void decayHealth(int turn);
    const bool isAlive() const {return m_isAlive;}
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
    bool m_isAlive = true;
    int m_deadAt = -1;
    float m_score;
};

#endif