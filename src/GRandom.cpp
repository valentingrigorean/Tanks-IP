#include "GRandom.h"

#define INT_MAX 2147483647

static std::random_device rd;
static std::default_random_engine eng(rd());

GRandom::GRandom()
{	
	
}

GRandom::~GRandom()
{
	
}

int GRandom::Next()
{	
	return std::uniform_int_distribution<>(0, INT_MAX)(eng);
}

int GRandom::Next(int min, int max)
{
	return std::uniform_int_distribution<>(min, max)(eng);
}

double GRandom::NextDouble()
{
	return std::uniform_real_distribution<>(0, 1)(eng);
}
