#pragma once


#include <algorithm>
#include <cmath>


#include "utils/glm_utils.h"


// Contains auxiliary functions.
// Functions used for terrain generation follow the format: b * f(ax)

namespace utils
{
	inline GLfloat LineFunc(GLfloat x, GLfloat a)
	{
		return a * x;
	}


	inline GLfloat SinFunc(GLfloat x, GLfloat a, GLfloat b)
	{
		return b * std::sin(a * x);
	}


	inline GLfloat CosFunc(GLfloat x, GLfloat a, GLfloat b)
	{
		return b * std::cos(a * x);
	}


	inline GLfloat FenceFunc(GLfloat x, GLfloat b)
	{
		if ((GLuint)x % 20 < 10)
		{
			return b * (x - (GLuint)x + (GLuint)x % 20);
		}

		return b * (20 - x + (GLuint)x - (GLuint)x % 20);
	}


	inline GLfloat FunkyFunc(GLfloat x)
	{
		GLfloat c = 1000 / (sqrt(10 * AI_MATH_PI));
		GLfloat p = (x - 6.4) * (x - 6.4) / -10;

		return c * exp(p) + 10 * sin(0.1 * x);
	}


	inline GLfloat GetTerrainAngle(GLfloat aHeight, GLfloat bHeight)
	{
		return std::atan2(bHeight - aHeight, 1.0);
	}
}


