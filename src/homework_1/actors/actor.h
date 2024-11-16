#pragma once


#include <iostream>
#include <string>
#include <utility>
#include <vector>


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

		std::pair<GLfloat, GLfloat> GetActorPosition() const;
		void SetActorPosition(std::pair<GLfloat, GLfloat> coords);
		GLfloat GetActorAngle() const;
		void SetActorAngle(GLfloat _angle);
		std::string GetActorName() const;
		std::vector<Mesh*> GetMeshList() const;
		virtual void SetMeshList();

	protected:
		std::string actorName;
		ActorType type;
		std::vector<Mesh*> meshList;
		GLfloat xPos;
		GLfloat yPos;
		GLfloat angle;
	};
}


