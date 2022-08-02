#include "creature.h"
#include "randomGen.h"

Creature::Creature(Vec pos, int angle, size_t id) : m_position(pos), m_angle(angle), m_id(id)
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
        m_angle += config::CREATURE_ROTATION_DEGREE;
        break;
    case ROTATE_RIGHT:
        m_angle -= config::CREATURE_ROTATION_DEGREE;
        break;
    case WAIT:
        break;
    case MOVE_FORWARD:
        m_position.x += cos(tools::degreesToRadian(m_angle)) * m_speed;
        m_position.y += sin(tools::degreesToRadian(m_angle)) * m_speed;
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
    frameCreature.angle = m_angle;
    return frameCreature;
}