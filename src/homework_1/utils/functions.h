#pragma once


#include <algorithm>


#include "utils/glm_utils.h"


// Contains the functions used for terrain generation. Format: b * f(ax)

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
}


