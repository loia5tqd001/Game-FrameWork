#pragma once
#include <random>

class Random
{
private:
	std::random_device rd;
	std::mt19937 rng = std::mt19937( rd() );

private:
	Random() = default;

	static const std::mt19937& GetRng()
	{
		static Random instance;
		return instance.rng;
	}

public:
	template<typename Int>
	static Int NextInt(Int min, Int max)
	{
		std::uniform_int_distribution<Int> dist(min, max);
		return dist( GetRng() );
	}

	template<typename Real>
	static Real NextReal(Real min, Real max)
	{
		std::uniform_real_distribution<Real> dist(min, max);
		return dist( GetRng() );
	}
};
