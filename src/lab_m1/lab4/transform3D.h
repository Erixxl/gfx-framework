#pragma once


#include <cmath>

#include "utils/glm_utils.h"


namespace transform3D
{
	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		glm::mat4 matrix = glm::mat4(
			1, 0, 0, translateX,
			0, 1, 0, translateY,
			0, 0, 1, translateZ,
			0, 0, 0,          1
		);

		return glm::transpose(matrix);
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		glm::mat4 matrix = glm::mat4(
			scaleX,      0,      0, 0,
			     0, scaleY,      0, 0,
			     0,      0, scaleZ, 0,
			     0,      0,      0, 1
		);

		return glm::transpose(matrix);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		float cosine = std::cos(radians);
		float sine = std::sin(radians);

		glm::mat4 matrix = glm::mat4(
			cosine,  -sine, 0, 0,
			  sine, cosine, 0, 0,
			     0,      0, 1, 0,
			     0,      0, 0, 1
		);

		return glm::transpose(matrix);
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		float cosine = std::cos(radians);
		float sine = std::sin(radians);

		glm::mat4 matrix = glm::mat4(
			cosine, 0,   sine, 0,
			     0, 1,      0, 0,
			 -sine, 0, cosine, 0,
			     0, 0,      0, 1
		);

		return glm::transpose(matrix);
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		float cosine = std::cos(radians);
		float sine = std::sin(radians);

		glm::mat4 matrix = glm::mat4(
			1,      0,      0, 0,
			0, cosine,  -sine, 0,
			0,   sine, cosine, 0,
			0,      0,      0, 1
		);

		return glm::transpose(matrix);
	}
}   // namespace transform3D
