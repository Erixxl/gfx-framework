#pragma once


#include <iostream>
#include <string>
#include <utility>


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
		virtual void MoveActor(GLfloat xNew, GLfloat yNew);
		virtual void RotateActor(GLfloat angleNew);

		std::pair<GLfloat, GLfloat> GetActorPosition() const;
		void SetActorPosition(std::pair<GLfloat, GLfloat> coords);
		std::string GetActorName() const;

	protected:
		std::string actorName;
		ActorType type;

		GLfloat xPos;
		GLfloat yPos;
	};
}


