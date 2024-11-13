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
		BULLET,
		PROP_OBJECT
	};


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


