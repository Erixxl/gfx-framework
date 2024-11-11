#include "homework_1/actors/tank_actor.h"


using namespace actors;
using namespace std;


TankActor::TankActor()
	: Actor()
{
	actorName = "tank";
	type = TANK;

	mainColor = glm::vec3(1);
	secondColor = glm::vec3(0);
	team = 0;
}


TankActor::TankActor(TankColor color, GLuint tankTeam)
	: TankActor()
{
	actorName = actorName + "_team" + to_string(tankTeam);
	team = tankTeam;

	switch (color)
	{
	case BROWN:
		break;
	case RED:
		break;
	case BLUE:
		break;
	default:
		break;
	}
}


void TankActor::Debug()
{
	Actor::Debug();

	cout << "\tDebug info:\n";
	cout << "\t\tTeam ID: " << team << '\n';
	cout << "\t\tPosition: (x = " << xPos << ", y = " << yPos << ")\n";
}


void TankActor::SetOrientation(GLfloat angle)
{
	orientation = utils::Rotate(angle);
}


