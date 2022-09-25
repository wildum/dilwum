#ifndef FOOD
#define FOOD

#include "vec.h"
#include "config/config.h"
#include <boost/serialization/access.hpp>

struct FrameFood
{
    size_t id;
    int value;
    Vec position;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & id;
        ar & value;
        ar & position;
    }
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

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_position;
        ar & m_id;
        ar & m_value;
        ar & m_radius;
    }
};

#endif