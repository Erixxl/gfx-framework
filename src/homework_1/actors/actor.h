#pragma once


#include <iostream>
#include <utility>
#include <string>


#include "GL/glew.h"
#include "glm/glm.hpp"


#include "core/gpu/mesh.h"


namespace actors
{
	enum ActorType
	{
		DEFAULT,
		TANK,
		TANK_BARREL,
		BULLET,
		AIM_TRAIL,
		LIFE_BAR,
		PROP_OBJECT
	};


	class Actor
	{
	public:
		Actor();

		inline std::pair<GLuint, GLuint> GetPosition() const;
		inline void SetPosition(GLuint xNew, GLuint yNew);

		virtual void Debug();

	protected:
		std::string actorName;
		ActorType type;

		glm::mat3 orientation;
		Mesh* objectMesh;
		GLuint xPos;
		GLuint yPos;
	};
}


