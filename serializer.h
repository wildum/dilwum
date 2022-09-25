#ifndef SERIALIZER
#define SERIALIZER

#include "game.h"

class Serializer
{
public:
  static GameFeedback read(const std::string& fileName);
  static void write(const GameFeedback& gameFeedback);
};

#endif