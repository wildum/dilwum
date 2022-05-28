#include "creature.h"
#include "randomGen.h"

Creature::Creature(Vec pos, Vec dir, size_t id) : m_position(pos), m_direction(dir), m_id(id)
{

}

void Creature::pickRandomAction()
{
    m_action = static_cast<Action>(RandomGen::getRandomInt(0, action::LAST_ACTION_INDEX));
}

void Creature::performAction()
{
    switch (m_action)
    {
    case ROTATE_LEFT:
        m_direction.rotateAroundPoint(m_position, config::CREATURE_ROTATION_DEGREE);
        break;
    case ROTATE_RIGHT:
        m_direction.rotateAroundPoint(m_position, -config::CREATURE_ROTATION_DEGREE);
        break;
    case WAIT:
        break;
    case MOVE_FORWARD:
        m_position.x += m_direction.x * m_speed;
        m_position.y += m_direction.y * m_speed;
        break;
    default:
        break;
    }
}

FrameCreature Creature::toFrameCreature() const
{
    FrameCreature frameCreature;
    frameCreature.id = m_id;
    frameCreature.position = m_position;
    frameCreature.direction = m_direction;
    return frameCreature;
}