#pragma once
#include <random>

class GRandom
{
public:
	GRandom();
	~GRandom();

	int Next();
	int Next(int min, int max);
	
	//return between 0.0f - 1.f
	double NextDouble();
};