#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>

#include "frame.h"
#include "creature.h"

struct GameFeedback
{
    std::vector<Frame> frames;
    std::vector<Creature> creatures;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & frames;
        ar & creatures;
    }
};