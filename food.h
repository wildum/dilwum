#ifndef FOOD
#define FOOD

#include "vec.h"
#include "config.h"

struct FrameFood
{
    size_t id;
    int value;

};

class Food
{
public:
    Food(Vec pos, int value, size_t m_id);
    void decayValue() {m_value--;}
    bool isDepleted(){m_value <= 0;}
    FrameFood toFrameFood() const;
private:
    Vec m_position;
    size_t m_id;
    int m_value;
    int m_radius = config::FOOD_RADIUS;
};

#endif