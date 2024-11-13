#pragma once


#include <map>


#include "homework_1/actors/actor.h"
#include "homework_1/actors/object.h"
#include "homework_1/utils/transform2D.h"


namespace actors
{
	enum TankColor
	{
		BROWN,
		RED,
		BLUE,
		GREEN,
		GRAY
	};


	static TankColor AllTankColors[] = {
		BROWN,
		RED,
		BLUE,
	//	GREEN,
	//	GRAY
	};


	struct ColorPicker
	{
		ColorPicker();
		ColorPicker(TankColor _type);

		TankColor type;
		std::string name;
		glm::vec3 main;
		glm::vec3 second;
	};


	static ColorPicker GetPalette(TankColor color);


	class TankActor : public Actor
	{
	public:
		TankActor();
		TankActor(TankColor color, GLuint tankTeam);

		void Debug() override;

	private:
		glm::vec3 mainColor;
		glm::vec3 secondColor;
		GLuint team;

		GLfloat xPos;
		GLfloat yPos;
		GLfloat angle;
		GLfloat barrelAngle;
		GLfloat lifepoints;

		Object body;
		Object barrel;
		Object trail;
		Object lifebar;
	};
}
