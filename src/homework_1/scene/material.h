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
			bool _deform
		);

		Material(MaterialType material);
		Material();

		MaterialType type;
		std::string name;
		glm::vec3 color;
		GLfloat friction;
		bool deform;
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

		std::vector<GLfloat>* GetBasePoints();
		std::vector<GLfloat>* GetHeightPoints();
		std::string GetMaterialName() const;
		bool CanBeDeformed() const;

	private:
		std::vector<GLfloat> basePoints;
		std::vector<GLfloat> heightPoints;
		GLuint pointCount;
		Material material;
	};
}


