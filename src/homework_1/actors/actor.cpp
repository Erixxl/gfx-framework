#include "homework_1/actors/actor.h"


using namespace actors;
using namespace std;


Actor::Actor(std::string _name, ActorType _type)
	: actorName(_name)
	, type(_type)
	, xPos(0.0f)
	, yPos(0.0f)
{
}


Actor::Actor()
	: Actor("default", DEFAULT)
{
}


void Actor::MoveActor(GLfloat xNew, GLfloat yNew)
{
}


void Actor::RotateActor(GLfloat angleNew)
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


string Actor::GetActorName() const
{
	return actorName;
}


void Actor::Debug()
{
	cout << "\n[Debug]\n";
	cout << "Debug command called for actor [" + actorName + "]\n";
}


