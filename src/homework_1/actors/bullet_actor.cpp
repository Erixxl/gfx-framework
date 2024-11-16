#include "homework_1/actors/bullet_actor.h"


using namespace std;
using namespace actors;


BulletActor::BulletActor()
	: BulletActor(0)
{
}


BulletActor::BulletActor(GLuint _team)
	: Actor("bullet", BULLET)
{
	actorName = actorName + "_team_" + to_string(_team);
	team = _team;

	radius = 40.0f;
	damage = 20.0f;

	bulletObj = new Object(BULLET_OBJ);
	bulletObj->MeshSetup(BROWN, _team);
}


void BulletActor::SetMeshList()
{
	meshList.clear();

	meshList.push_back(bulletObj->GetObjectMesh());
}


void BulletActor::Debug()
{
	Actor::Debug();

	cout << "Debug info:\n";
	cout << "\tTeam ID: " << team << '\n';
	cout << "\tPosition: " << xPos << ", " << yPos << '\n';
	cout << "\tVelocity: (" << velocity.first << ", " << velocity.second << ")\n";
}


std::pair<GLfloat, GLfloat> BulletActor::GetVelocity() const
{
	return velocity;
}


void BulletActor::SetVelocity(GLfloat xPart, GLfloat yPart)
{
	velocity = { xPart, yPart };
}


void BulletActor::SetActorPosition(std::pair<GLfloat, GLfloat> coords)
{
	Actor::SetActorPosition(coords);

	bulletObj->SetPosMatrix(utils::Translate(coords.first, coords.second));
}


void BulletActor::SetActorAngle(GLfloat _angle)
{
	Actor::SetActorAngle(_angle);

	bulletObj->SetRotMatrix(utils::Rotate(_angle));
}


Object* BulletActor::GetBulletObj() const
{
	return bulletObj;
}


