#include "food.h"

Food::Food(Vec pos, int value, size_t id) : m_position(pos), m_value(value), m_id(id)
{

}

FrameFood Food::toFrameFood() const
{
    FrameFood frameFood;
    frameFood.id = m_id;
    frameFood.value = m_value;
    frameFood.position = m_position;
    return frameFood;
}