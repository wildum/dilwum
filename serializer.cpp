#include "serializer.h"

#include <fstream>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

GameFeedback Serializer::read(const std::string& fileName)
{
    GameFeedback gameFeedback;
    std::ifstream file_obj("save/" + fileName);
    if (file_obj)
    {
        boost::archive::text_iarchive ia(file_obj);
        ia >> gameFeedback;
    }
    else
    {
        tools::log("could not read from the file : " + fileName);
    }
    return gameFeedback;
}

void Serializer::write(const GameFeedback& gameFeedback)
{
    std::ofstream file_obj("save/lastPlay.txt");
    if (file_obj)
    {
        boost::archive::text_oarchive oa(file_obj);
        oa << gameFeedback;
    }
    else
    {
        tools::log("could not write last play");
    }
}