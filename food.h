#ifndef FOOD
#define FOOD

#include "vec.h"
#include "config/config.h"

struct FrameFood
{
    size_t id;
    int value;
    Vec position;
};

class Food
{
public:
    Food(Vec pos, int value, size_t m_id);
    void decayValue() {m_value--;}
    bool isDepleted(){return m_value <= 0;}
    const Vec& getPosition() const {return m_position;}
    const int getRadius() const {return m_radius;}
    int getValue(){return m_value;}
    FrameFood toFrameFood() const;
private:
    Vec m_position;
    size_t m_id;
    int m_value;
    int m_radius = Config::getFOOD_RADIUS();
};

#endif