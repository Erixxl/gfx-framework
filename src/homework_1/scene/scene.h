#pragma once


#include <cmath>
#include <vector>
#include <algorithm>


#include "components/simple_scene.h"


#include "homework_1/scene/scene.h"
#include "homework_1/scene/material.h"


namespace scene
{
	enum LevelType
	{
		BASIC_LEVEL,
		GRASS_LEVEL,
		DESERT_LEVEL,
		BUILDING_LEVEL,
		TUNNEL_LEVEL,
		ERROR_LEVEL
	};

	static LevelType AllowedLevelTypes[] = {
		BASIC_LEVEL,
		//GRASS_LEVEL,
		//DESERT_LEVEL,
		//BUILDING_LEVEL,
		//TUNNEL_LEVEL,
		ERROR_LEVEL
	};


	struct SceneData
	{
		SceneData(
			LevelType _level,
			glm::vec3 _background,
			std::vector<Landmass> _stripes,
			GLuint _stripeCount
		);
		SceneData();

		LevelType level;

		glm::vec3 background;
		std::vector<Landmass> stripes;
		GLuint stripeCount;
	};


	class Scene
	{
	public:
		Scene();
		Scene(LevelType _level);
		~Scene();

		SceneData* GetSceneData();

	private:
		// Functions used for terrain generation: b * f(ax)
		inline GLfloat LineFunc(GLfloat x, GLfloat a = 1.0f);
		inline GLfloat SinFunc(GLfloat x, GLfloat a = 1.0f, GLfloat b = 1.0f);
		inline GLfloat FenceFunc(GLfloat x, GLfloat b = 1.0f);

		SceneData data;
	};
}


