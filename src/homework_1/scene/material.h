#pragma once


#include <vector>
#include <functional>
#include <string>


#include "GL/glew.h"
#include "glm/glm.hpp"


namespace scene
{
	enum MaterialType
	{
		GRASS,
		DIRT,
		STONE,
		SAND,
		METAL,
		ERROR
	};


	static MaterialType AllMaterialTypes[] = {
		GRASS,
		DIRT,
		STONE,
		SAND,
		METAL,
		ERROR
	};


	struct Material
	{
		Material(
			MaterialType _type,
			std::string _name,
			glm::vec3 _color,
			GLfloat _friction,
			GLfloat _fallBoundry,
			GLfloat _fallSpeed
		);

		Material(MaterialType material);
		Material();

		MaterialType type;
		std::string name;
		glm::vec3 color;
		GLfloat friction;
		GLfloat fallBoundry;
		GLfloat fallSpeed;
	};


	class Landmass
	{
	public:
		Landmass(
			std::function<GLfloat (GLfloat)> baseGen,
			std::function<GLfloat (GLfloat)> heightGen,
			Material materialInfo
		);
		~Landmass();

		std::vector<GLfloat>* getBasePoints();
		std::vector<GLfloat>* getHeightPoints();
		std::string getMaterialName() const;

	private:
		std::vector<GLfloat> basePoints;
		std::vector<GLfloat> heightPoints;
		GLuint pointCount;
		Material material;
	};
}


