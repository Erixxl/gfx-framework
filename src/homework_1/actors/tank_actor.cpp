#include "homework_1/actors/tank_actor.h"


using namespace actors;
using namespace std;
using namespace glm;


ColorPicker::ColorPicker()
	: ColorPicker(BROWN)
{
}


ColorPicker::ColorPicker(TankColor _type)
{
	switch (_type)
	{
		case BROWN:
			name = "brown";
			main = vec3(193.0 / 255.0, 142.0 / 255.0, 40.0 / 255.0);
			second = vec3(209.0 / 255.0, 178.0 / 255.0, 69.0 / 255.0);
			break;

		case RED:
			name = "red";
			main = vec3(127.0 / 255.0, 3.0 / 255.0, 3.0 / 255.0);
			second = vec3(237.0 / 255.0, 87.0 / 255.0, 87.0 / 255.0);
			break;

		case BLUE:
			name = "blue";
			main = vec3(0.0 / 255.0, 33.0 / 255.0, 127.0 / 255.0);
			second = vec3(87.0 / 255.0, 127.0 / 255.0, 237.0 / 255.0);
			break;

		case GREEN:
		case GRAY:
			break;
	}
}


static ColorPicker actors::GetPalette(TankColor color)
{
	return ColorPicker(color);
}


TankActor::TankActor()
	: Actor("tank", TANK)
{
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

	case GREEN:
	case GRAY:
		break;
	}
}


void TankActor::Debug()
{
	Actor::Debug();

	cout << "\tDebug info:\n";
	cout << "\t\tTeam ID: " << team << '\n';
}


