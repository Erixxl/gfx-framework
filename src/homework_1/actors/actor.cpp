#include "homework_1/actors/actor.h"


using namespace actors;
using namespace std;


Actor::Actor()
{
	actorName = "default";
	type = DEFAULT;

	orientation = glm::mat3(1);
	objectMesh = nullptr;
	xPos = 0;
	yPos = 0;
}


void Actor::Debug()
{
	cout << "\n[Debug]\n";
	cout << "Debug command called for actor [" + actorName + "]\n";
}


inline pair<GLuint, GLuint> Actor::GetPosition() const
{
	return pair<GLuint, GLuint>({ xPos, yPos });
}


inline void Actor::SetPosition(GLuint xNew, GLuint yNew)
{
	xPos = xNew;
	yPos = yNew;
}


