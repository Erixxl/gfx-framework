#pragma once


#include <string>


#include "glm/glm.hpp"


namespace actors
{
	// ActorType

	enum ActorType
	{
		DEFAULT,
		TANK,
		BULLET,
		PROP_OBJECT
	};


	// TankColor

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
		GREEN,
		GRAY
	};

	TankColor GetColor(std::string name);


	// ColorPicker

	struct ColorPicker
	{
		ColorPicker();
		ColorPicker(TankColor _type);

		TankColor type;
		std::string name;
		glm::vec3 main;
		glm::vec3 second;
	};



	// ObjectType

	enum ObjectType
	{
		DEFAULT_OBJ,
		TANK_BODY,
		TANK_BARREL,
		TANK_TRAIL,
		TANK_LIFEBAR,
		BULLET_OBJ
	};
}

