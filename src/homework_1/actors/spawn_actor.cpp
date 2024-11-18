#include "homework_1/actors/spawn_actor.h"


using namespace actors;
using namespace glm;


SpawnActor::SpawnActor()
	: SpawnActor(0)
{
}


SpawnActor::SpawnActor(GLuint _team)
{
	outline = new Object(SPAWN_BULLET);
	outline->MeshSetup(BROWN, _team);

	SetMeshList();
}


void SpawnActor::Debug()
{
	Actor::Debug();

	std::cout << "Hey, how are you reading this?!\n";
}


void SpawnActor::SetMeshList()
{
	meshList.clear();

	meshList.push_back(outline->GetObjectMesh());
}


void SpawnActor::SetActorPosition(std::pair<GLfloat, GLfloat> coords)
{
	Actor::SetActorPosition(coords);

	mat3 position = utils::Translate(coords.first, coords.second);

	outline->SetPosMatrix(position);
}


void SpawnActor::SetActorAngle(GLfloat _angle)
{
	Actor::SetActorAngle(_angle);

	mat3 tankRot = utils::Rotate(_angle);
	mat3 barrelRot = utils::RotateFrom(0, 35, barrelAngle);

	outline->SetRotMatrix(tankRot * barrelRot);
}


GLfloat SpawnActor::GetBarrelAngle() const
{
	return barrelAngle;
}


void SpawnActor::SetBarrelAngle(GLfloat _angle)
{
	barrelAngle = _angle;

	mat3 tankRot = utils::Rotate(angle);
	mat3 barrelRot = utils::RotateFrom(0, 35, barrelAngle);

	// Reset orientation
	outline->SetRotMatrix(tankRot * barrelRot);
}


Object* SpawnActor::GetOutline() const
{
	return outline;
}


