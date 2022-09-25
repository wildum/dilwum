#ifndef FRAME
#define FRAME

#include "food.h"
#include "creature.h"
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

struct Frame
{
    std::vector<FrameFood> food;
    std::vector<FrameCreature> creatures;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & food;
        ar & creatures;
    }
};

#endif