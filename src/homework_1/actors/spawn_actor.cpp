#include "homework_1/actors/spawn_actor.h"


using namespace actors;
using namespace glm;


SpawnActor::SpawnActor()
	: SpawnActor(0)
{
}


SpawnActor::SpawnActor(GLuint _team)
	: Actor("spawn", SPAWN)
{
	actorName = actorName + "_bullet_" + to_string(_team);
	team = _team;

	barrelAngle = 0;
	outlineCenter = { 0, 35, 0 };

	outline = new Object(SPAWN_BULLET);
	outline->MeshSetup(BROWN, _team);

	SetMeshList();
}


void SpawnActor::Debug()
{
	Actor::Debug();

	cout << "Debug info:\n";
	cout << "\tTeam ID: " << team << '\n';
	cout << "\tPosition: " << xPos << ", " << yPos << '\n';
	cout << "\tTank angle: " << angle << '\n';
	cout << "\tBarrel angle: " << barrelAngle << '\n';
	cout << "\t\tSpawn angle: " << angle + barrelAngle << '\n';
	cout << "\t\t... as x * PI: " << (AI_MATH_HALF_PI + angle + barrelAngle) / AI_MATH_PI << " * PI\n";
	cout << "\tSpawn center: " << outlineCenter.x << ", " << outlineCenter.y << '\n';
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
	UpdateSpawnCenter();
}


void SpawnActor::SetActorAngle(GLfloat _angle)
{
	Actor::SetActorAngle(_angle);

	mat3 tankRot = utils::Rotate(angle);
	mat3 barrelRot = utils::RotateFrom(0, 15, barrelAngle);

	outline->SetRotMatrix(tankRot * barrelRot);
	UpdateSpawnCenter();
}


GLfloat SpawnActor::GetBarrelAngle() const
{
	return barrelAngle;
}


void SpawnActor::SetBarrelAngle(GLfloat _angle)
{
	barrelAngle = _angle;

	mat3 tankRot = utils::Rotate(angle);
	mat3 barrelRot = utils::RotateFrom(0, 15, barrelAngle);

	// Reset orientation
	outline->SetRotMatrix(tankRot * barrelRot);
	UpdateSpawnCenter();
}


void SpawnActor::UpdateSpawnCenter()
{
	mat3 finalMatrix = utils::Translate(xPos, yPos) * utils::Rotate(angle) * utils::RotateFrom(0, 15, barrelAngle);

	outlineCenter = finalMatrix * vec3(0, 35, 1);
}


pair<GLfloat, GLfloat> SpawnActor::GetSpawnCoords() const
{
	return { outlineCenter.x, outlineCenter.y };
}


Object* SpawnActor::GetOutline() const
{
	return outline;
}


