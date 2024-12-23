#include "homework_1/actors/tank_actor.h"


using namespace actors;
using namespace std;
using namespace glm;


TankActor::TankActor()
	: TankActor(BROWN, 0)
{
}


TankActor::TankActor(TankColor _color, GLuint _team)
	: Actor("tank", TANK)
{
	actorName = actorName + "_team_" + to_string(_team);
	team = _team;
	color = _color;

	barrelAngle = 0.0;
	hitRadius = 30.0f;
	lifepoints = 100.0f;

	tankBody = new Object(TANK_BODY);
	tankBody->MeshSetup(_color, _team);

	tankBarrel = new Object(TANK_BARREL);
	tankBarrel->MeshSetup(_color, _team);

	tankLifebar = new Object(TANK_LIFEBAR);
	tankLifebar->MeshSetup(_color, _team);

	tankLifebarBackground = new Object(TANK_LIFEBAR_BKG);
	tankLifebarBackground->MeshSetup(_color, _team);

	SetMeshList();
}


void TankActor::Debug()
{
	Actor::Debug();

	cout << "Debug info:\n";
	cout << "\tTeam ID: " << team << '\n';
	cout << "\tPosition: " << xPos << ", " << yPos << '\n';
	cout << "\tAngle: " << angle << '\n';
	cout << "\tLifepoints: " << lifepoints << '\n';
}


void TankActor::SetMeshList()
{
	meshList.clear();

	meshList = {
		tankBody->GetObjectMesh(),
		tankBarrel->GetObjectMesh(),
		tankLifebar->GetObjectMesh(),
		tankLifebarBackground->GetObjectMesh()
	};
}


void TankActor::SetActorPosition(std::pair<GLfloat, GLfloat> coords)
{
	Actor::SetActorPosition(coords);

	mat3 position = utils::Translate(coords.first, coords.second);
	mat3 barrelTr = utils::Translate(0, 0);
	mat3 lifebarTr = utils::Translate(-50, 60);

	tankBody->SetPosMatrix(position);
	tankBarrel->SetPosMatrix(position);
	tankLifebar->SetPosMatrix(lifebarTr * position);
	tankLifebarBackground->SetPosMatrix(lifebarTr * position);
}


void TankActor::SetActorAngle(GLfloat _angle)
{
	Actor::SetActorAngle(_angle);

	mat3 rotation = utils::Rotate(_angle);
	mat3 barrelRot = utils::RotateFrom(0, 15, barrelAngle);

	tankBody->SetRotMatrix(rotation);
	tankBarrel->SetRotMatrix(rotation * barrelRot);
	tankLifebar->SetRotMatrix(mat3(1));
}


GLfloat TankActor::GetBarrelAngle() const
{
	return barrelAngle;
}


void TankActor::SetBarrelAngle(GLfloat newAngle)
{
	barrelAngle = newAngle;

	// Reset orientation
	tankBarrel->SetRotMatrix(utils::Rotate(angle) * utils::RotateFrom(0, 15, barrelAngle));
}


GLfloat TankActor::GetHitRadius() const
{
	return hitRadius;
}


GLfloat TankActor::GetLifepoints() const
{
	return lifepoints;
}


void TankActor::SetLifepoints(GLfloat val)
{
	lifepoints = val;
}


Object* TankActor::GetTankBody() const
{
	return tankBody;
}


Object* TankActor::GetTankBarrel() const
{
	return tankBarrel;
}


Object* TankActor::GetTankLifebar() const
{
	return tankLifebar;
}


