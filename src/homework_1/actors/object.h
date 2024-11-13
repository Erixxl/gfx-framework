#pragma once


#include <string>


#include "core/gpu/mesh.h"
#include "homework_1/actors/tank_actor.h"


namespace actors
{
	enum ObjectType
	{
		DEFAULT,
		TANK_BODY,
		TANK_BARREL,
		TANK_TRAIL,
		TANK_LIFEBAR
	};


	static ObjectType AllObjectTypes[] = {
		DEFAULT,
		TANK_BODY,
		TANK_BARREL,
		TANK_TRAIL,
	//	TANK_LIFEBAR
	};


	class Object
	{
	public:
		Object();
		Object(ObjectType _type);

		void TankMeshSetup(TankColor color);

	protected:
		ObjectType type;
		Mesh* objectMesh;

		glm::mat3 posMatrix;
		glm::mat3 rotMatrix;
		glm::mat3 sclMatrix;
	};
}