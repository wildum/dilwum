#include "creature.h"
#include "randomGen.h"

Creature::Creature() : m_brain()
{
}

Creature::Creature(Vec pos, int angle, size_t id) : m_position(pos), m_angle(angle), m_id(id), m_brain()
{
}

Creature::Creature(Vec pos, int angle, size_t id, const std::vector<uint32_t>& genome) : m_position(pos), m_angle(angle), m_id(id), m_brain(genome)
{
}

void Creature::reset()
{
    m_deadAt = -1;
    m_isAlive = true;
    m_health = Config::getCREATURE_HEALTH();
}

void Creature::pickRandomAction()
{
    m_action = static_cast<Output>(RandomGen::getRandomInt(0, neuron::OUTPUT_NUMBER-1));
}

void Creature::eat(std::vector<Food>& food)
{
    Vec mouthPosition = getMouthPosition();
    for (auto& foodUnit : food)
    {
        if (mouthPosition.squaredDist(foodUnit.getPosition()) < (foodUnit.getRadius()) * (foodUnit.getRadius()))
        {
            foodUnit.decayValue();
            m_health = std::min(m_health + Config::getCREATURE_EATING_VALUE(), Config::getCREATURE_HEALTH());
            break;
        }
    }
}

void Creature::decayHealth(int turn)
{
    if (m_isAlive)
    {
        m_health = std::max(m_health-1, 0);
        if (m_health <= 0)
        {
            m_deadAt = turn;
            m_isAlive = false;
        }
    }
}

void Creature::performAction(std::vector<Food>& food)
{
    switch (m_action)
    {
    case ROTATE_LEFT:
        m_angle += Config::getCREATURE_ROTATION_DEGREE();
        break;
    case ROTATE_RIGHT:
        m_angle -= Config::getCREATURE_ROTATION_DEGREE();
        break;
    case WAIT:
        break;
    case MOVE_FORWARD:
        m_position.x += cos(tools::degreesToRadian(m_angle)) * m_speed;
        m_position.y += sin(tools::degreesToRadian(m_angle)) * m_speed;
        m_position.clip(m_radius);
        break;
    case EAT:
        eat(food);
    default:
        break;
    }
}

Vec Creature::getLeftAntennaPosition()
{
    return {m_position.x + cos(tools::degreesToRadian(m_angle)) * (Config::getCREATURE_RADIUS() + Config::getCREATURE_ANTENNA_X_OFFSET()),
        m_position.y + sin(tools::degreesToRadian(m_angle)) * (Config::getCREATURE_RADIUS() - Config::getCREATURE_ANTENNA_Y_OFFSET())};
}

Vec Creature::getRightAntennaPosition()
{
    return {m_position.x + cos(tools::degreesToRadian(m_angle)) * (Config::getCREATURE_RADIUS() + Config::getCREATURE_ANTENNA_X_OFFSET()),
        m_position.y + sin(tools::degreesToRadian(m_angle)) * (Config::getCREATURE_RADIUS() + Config::getCREATURE_ANTENNA_Y_OFFSET())};
}

Vec Creature::getMouthPosition()
{
    return {m_position.x + cos(tools::degreesToRadian(m_angle)) * Config::getCREATURE_RADIUS(), m_position.y + sin(tools::degreesToRadian(m_angle)) * Config::getCREATURE_RADIUS()};
}

AntennaTouch Creature::antennaTouchFeedback(const Vec& antennaPosition, std::vector<Food>& food, std::vector<Creature>& creatures)
{
    if (antennaPosition.isOut())
    {
        return AntennaTouch::TOUCH_WALL;
    }

    for (const auto& f : food)
    {
        if (antennaPosition.squaredDist(f.getPosition()) < (f.getRadius()) * (f.getRadius()))
        {
            return AntennaTouch::TOUCH_FOOD;
        }
    }
    for (const auto& c : creatures)
    {
        if (antennaPosition.squaredDist(c.getPosition()) < (c.getRadius()) * (c.getRadius()))
        {
            return AntennaTouch::TOUCH_CREATURE;
        }
    }
    return AntennaTouch::TOUCH_NOTHING;
}

Taste Creature::taste(std::vector<Food>& food)
{
    Taste t = Taste::TASTE_NOTHING;
    Vec mouthPosition = getMouthPosition();
    for (const auto& f : food)
    {
        if (mouthPosition.squaredDist(f.getPosition()) < (f.getRadius()) * (f.getRadius()))
        {
            t = Taste::TASTE_FOOD;
            break;
        }
    }
    return t;
}

void Creature::processInputs(std::vector<Food>& food, std::vector<Creature>& creatures)
{
    m_brain.setHealth(m_health);
    m_brain.setTaste(taste(food));
    m_brain.setLeftAntennaTouch(antennaTouchFeedback(getLeftAntennaPosition(), food, creatures));
    m_brain.setRightAntennaTouch(antennaTouchFeedback(getRightAntennaPosition(), food, creatures));
    m_brain.setRandom(RandomGen::getRandomFloat());
}

void Creature::pickAction()
{
    m_brain.process();
    m_action = m_brain.pickAction();
}

FrameCreature Creature::toFrameCreature() const
{
    FrameCreature frameCreature;
    frameCreature.id = m_id;
    frameCreature.position = m_position;
    frameCreature.angle = m_angle;
    frameCreature.health = m_health;
    return frameCreature;
}