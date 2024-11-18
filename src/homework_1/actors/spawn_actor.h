#pragma once


#include "homework_1/actors/actor.h"
#include "homework_1/actors/object.h"


namespace actors
{
	class SpawnActor : public Actor
	{
	public:
		SpawnActor();
		SpawnActor(GLuint _team);

		void Debug() override;
		void SetMeshList() override;

		void SetActorPosition(std::pair<GLfloat, GLfloat> coords);
		void SetActorAngle(GLfloat _angle);

		GLfloat GetBarrelAngle() const;
		void SetBarrelAngle(GLfloat _angle);

		Object* GetOutline() const;

	private:
		GLuint team;
		GLfloat barrelAngle;

		Object* outline;
	};
}
