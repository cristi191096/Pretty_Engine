#pragma once

#include "engine\Core\Core.h"

#include <math.h>

#define PI 3.14159265358f

namespace PrettyEngine { 

	PE_API inline float toRadians(float degrees)
	{
		return (float)(degrees * (PI / 180.0f));
	}

	PE_API inline float toDegrees(float radians)
	{
		return (float)(radians * (180.0f / PI));
	}

	PE_API inline int sign(float value)
	{
		return (value > 0) - (value < 0);
	}

	PE_API inline float sin(float angle)
	{
		return ::sin(angle);
	}

	PE_API inline float cos(float angle)
	{
		return ::cos(angle);
	}

	PE_API inline float tan(float angle)
	{
		return ::tan(angle);
	}

	PE_API inline float sqrt(float value)
	{
		return ::sqrt(value);
	}

	PE_API inline float rsqrt(float value)
	{
		return 1.0f / ::sqrt(value);
	}

	PE_API inline float asin(float value)
	{
		return ::asin(value);
	}

	PE_API inline float acos(float value)
	{
		return ::acos(value);
	}

	PE_API inline float atan(float value)
	{
		return ::atan(value);
	}

	PE_API inline float atan2(float y, float x)
	{
		return ::atan2(y, x);
	}

	PE_API inline float _min(float value, float minimum)
	{
		return (value < minimum) ? minimum : value;
	}

	PE_API inline float _max(float value, float maximum)
	{
		return (value > maximum) ? maximum : value;
	}

	PE_API inline float clamp(float value, float minimum, float maximum)
	{
		return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
	}

} 