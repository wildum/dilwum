#ifndef RANDOMGEN
#define RANDOMGEN

#include <random>

class RandomGen
{
public:
  static void initialize();
  static int getRandomInt(int a, int b);
  static float getRandomFloat(float a, float b);
  static float getRandomFloat();
  static bool flipCoin();
private:
  static std::random_device rd;
  static std::mt19937 gen;
};

#endif