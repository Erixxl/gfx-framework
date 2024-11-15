#pragma once


#include <iostream>
#include <string>


#include "GL/glew.h"
#include "glm/glm.hpp"


#include "core/gpu/mesh.h"
#include "homework_1/actors/actor_enums.h"


namespace actors
{
	class Actor
	{
	public:
		Actor();
		Actor(std::string _name, ActorType _type);

		virtual void Debug();

	protected:
		std::string actorName;
		ActorType type;
	};
}


