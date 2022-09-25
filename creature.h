#ifndef CREATURE
#define CREATURE

#include "vec.h"
#include "config/config.h"
#include "neuron.h"
#include "food.h"
#include "brain.h"

#include <vector>
#include <boost/serialization/access.hpp>

struct FrameCreature
{
    size_t id;
    Vec position;
    int angle;
    int health;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & id;
        ar & position;
        ar & angle;
        ar & health;
    }
};

class Creature
{
public:
    Creature();
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
    int m_speed = Config::getCREATURE_SPEED();
    int m_radius = Config::getCREATURE_RADIUS();
    int m_health = Config::getCREATURE_HEALTH();
    bool m_isAlive = true;
    int m_deadAt = -1;
    float m_score;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_brain;
        ar & m_position;
        ar & m_angle;
        ar & m_action;
        ar & m_id;
        ar & m_speed;
        ar & m_radius;
        ar & m_health;
        ar & m_isAlive;
        ar & m_deadAt;
        ar & m_score;
    }
};

#endif