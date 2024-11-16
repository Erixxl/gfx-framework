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

		void MeshSetup(TankColor color, GLuint team = 0, GLuint index = 0);
		Mesh* GetObjectMesh() const;

		glm::mat3 GetPosMatrix() const;
		void SetPosMatrix(glm::mat3 pos);

		glm::mat3 GetRotMatrix() const;
		void SetRotMatrix(glm::mat3 rot);

		glm::mat3 GetFinalMatrix() const;

	protected:
		ObjectType type;
		Mesh* objectMesh;

		glm::mat3 posMatrix;
		glm::mat3 rotMatrix;
	};
}