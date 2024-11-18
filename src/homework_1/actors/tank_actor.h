#pragma once


#include <map>
#include <vector>
#include <string>
#include <cmath>


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
		void SetMeshList() override;

		void SetActorPosition(std::pair<GLfloat, GLfloat> coords);
		void SetActorAngle(GLfloat _angle);

		GLfloat GetBarrelAngle() const;
		void SetBarrelAngle(GLfloat newAngle);

		GLfloat GetHitRadius() const;
		GLfloat GetLifepoints() const;
		void SetLifepoints(GLfloat val);

		Object* GetTankBody() const;
		Object* GetTankBarrel() const;
		Object* GetTankLifebar() const;
		std::vector<Object*> GetTankTrail() const;

	private:
		TankColor color;
		GLuint team;

		GLfloat barrelAngle;
		GLfloat lifepoints;
		GLfloat hitRadius;

		Object* tankBody;
		Object* tankBarrel;
		Object* tankLifebar;
		std::vector<Object*> tankTrail;
	};
}
