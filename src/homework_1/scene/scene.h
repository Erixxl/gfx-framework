#pragma once


#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>


#include "components/simple_scene.h"


#include "homework_1/scene/scene.h"
#include "homework_1/scene/material.h"
#include "homework_1/utils/functions.h"


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
		GRASS_LEVEL,
		DESERT_LEVEL,
		//BUILDING_LEVEL,
		TUNNEL_LEVEL,
		ERROR_LEVEL
	};


	struct SceneData
	{
		SceneData(
			LevelType _level,
			glm::vec3 _background,
			std::vector<Landmass> _stripes,
			GLuint _stripeCount,
			std::pair<GLfloat, GLfloat> _spawnP1,
			std::pair<GLfloat, GLfloat> _spawnP2
		);
		SceneData();

		LevelType level;

		glm::vec3 background;
		std::vector<Landmass> stripes;
		GLuint stripeCount;

		std::pair<GLfloat, GLfloat> spawnP1;
		std::pair<GLfloat, GLfloat> spawnP2;
	};


	class Scene
	{
	public:
		Scene();
		Scene(LevelType _level);
		~Scene();

		SceneData* GetSceneData();

	private:
		const std::function<GLfloat(GLfloat)> baseLayer =
			[](GLfloat x) -> GLfloat
			{
				return utils::LineFunc(x, 0);
			};

		void BasicLevelGen();
		void GrassLevelGen();
		void DesertLevelGen();
		void TunnelLevelGen();

		SceneData data;
	};
}


