#pragma once


#include <map>
#include <vector>
#include <string>


#include "homework_1/actors/actor.h"
#include "homework_1/actors/object.h"
#include "homework_1/utils/transform2D.h"


namespace actors
{
	class TankActor : public Actor
	{
	public:
		TankActor();
		TankActor(TankColor _color, GLuint _team);

		void Debug() override;

	private:
		TankColor color;
		GLuint team;

		GLfloat xPos;
		GLfloat yPos;
		GLfloat angle;
		GLfloat barrelAngle;
		GLfloat lifepoints;

		Object* tankBody;
		Object* tankBarrel;
		Object* tankLifebar;
		std::vector<Object*> tankTrail;
	};
}
