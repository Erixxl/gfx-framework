#include "homework_1/actors/actor.h"


using namespace actors;
using namespace std;


Actor::Actor(std::string _name, ActorType _type)
	: actorName(_name)
	, type(_type)
{
}


Actor::Actor()
	: Actor("default", DEFAULT)
{
}


void Actor::Debug()
{
	cout << "\n[Debug]\n";
	cout << "Debug command called for actor [" + actorName + "]\n";
}


