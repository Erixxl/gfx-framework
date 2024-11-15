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

	tankBody = new Object(TANK_BODY);
	tankBody->TankMeshSetup(_color, _team);

	tankBarrel = new Object(TANK_BARREL);
	tankBarrel->TankMeshSetup(_color, _team);

	tankLifebar = new Object(TANK_LIFEBAR);
	tankLifebar->TankMeshSetup(_color, _team);

	tankTrail = vector<Object*>();
	for (int i = 0; i < 20; ++i)
	{
		tankTrail.push_back(new Object(TANK_TRAIL));
		tankTrail[i]->TankMeshSetup(_color, _team, i);
	}
}


void TankActor::Debug()
{
	Actor::Debug();

	cout << "\tDebug info:\n";
	cout << "\t\tTeam ID: " << team << '\n';
}


