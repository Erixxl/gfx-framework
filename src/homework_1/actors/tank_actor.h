#pragma once


#include "homework_1/actors/actor.h"
#include "homework_1/utils/transform2D.h"


namespace actors
{
	enum TankColor
	{
		BROWN,
		RED,
		BLUE
	};


	class TankActor : public Actor
	{
	public:
		TankActor();
		TankActor(TankColor color, GLuint tankTeam);

		void Debug() override;

		void SetOrientation(GLfloat angle);

	private:
		glm::vec3 mainColor;
		glm::vec3 secondColor;
		GLuint team;
	};
}
