#pragma once


#include <vector>
#include <string>


#include "core/gpu/mesh.h"
#include "homework_1/utils/transform2D.h"
#include "homework_1/actors/actor_enums.h"


namespace actors
{
	class Object
	{
	public:
		Object();
		Object(ObjectType _type);

		void TankMeshSetup(TankColor color, GLuint team = 0, GLuint index = 0);

	protected:
		ObjectType type;
		Mesh* objectMesh;

		glm::mat3 posMatrix;
		glm::mat3 rotMatrix;
		glm::mat3 sclMatrix;
	};
}