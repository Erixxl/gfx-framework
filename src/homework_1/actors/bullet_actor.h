#pragma once


#include "homework_1/actors/actor.h"
#include "homework_1/actors/object.h"


namespace actors
{
	class BulletActor : public Actor
	{
	public:
		BulletActor();
		BulletActor(GLuint _team);

		void Debug() override;
		void SetMeshList() override;

		void SetActorPosition(std::pair<GLfloat, GLfloat> coords);
		void SetActorAngle(GLfloat _angle);

		std::pair<GLfloat, GLfloat> GetVelocity() const;
		void SetVelocity(GLfloat xPart, GLfloat yPart);

		GLfloat GetBulletRadius() const;
		GLfloat GetBulletDamage() const;
		void SetBulletDamage(GLfloat val);
		Object* GetBulletObj() const;

	private:
		GLfloat radius;
		GLfloat damage;
		GLuint team;

		std::pair<GLfloat, GLfloat> velocity;
		Object* bulletObj;
	};
}


