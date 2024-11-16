#include "homework_1/actors/actor.h"


using namespace actors;
using namespace std;


Actor::Actor(std::string _name, ActorType _type)
	: actorName(_name)
	, type(_type)
	, meshList(std::vector<Mesh*>(0, nullptr))
	, xPos(0.0f)
	, yPos(0.0f)
	, angle(0.0f)
{
}


Actor::Actor()
	: Actor("default", DEFAULT)
{
}


pair<GLfloat, GLfloat> Actor::GetActorPosition() const
{
	return { xPos, yPos };
}


void Actor::SetActorPosition(std::pair<GLfloat, GLfloat> coords)
{
	xPos = coords.first;
	yPos = coords.second;
}


GLfloat Actor::GetActorAngle() const
{
	return angle;
}


void Actor::SetActorAngle(GLfloat _angle)
{
	angle = _angle;
}


string Actor::GetActorName() const
{
	return actorName;
}


std::vector<Mesh*> Actor::GetMeshList() const
{
	return meshList;
}


void Actor::SetMeshList()
{
}


void Actor::Debug()
{
	cout << "\n[Debug]\n";
	cout << "Debug command called for actor [" + actorName + "]\n";
}


