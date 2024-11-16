#include "homework_1/actors/actor_enums.h"


using namespace actors;


ColorPicker::ColorPicker()
	: ColorPicker(BROWN)
{
}


ColorPicker::ColorPicker(TankColor _type)
{
	name = "";
	main = glm::vec3(1);
	second = glm::vec3(0);
	type = _type;

	switch (_type)
	{
		case BROWN:
			name = "brown";
			main = glm::vec3(193.0 / 255.0, 142.0 / 255.0, 40.0 / 255.0);
			second = glm::vec3(209.0 / 255.0, 178.0 / 255.0, 69.0 / 255.0);
			break;

		case RED:
			name = "red";
			main = glm::vec3(127.0 / 255.0, 3.0 / 255.0, 3.0 / 255.0);
			second = glm::vec3(237.0 / 255.0, 87.0 / 255.0, 87.0 / 255.0);
			break;

		case BLUE:
			name = "blue";
			main = glm::vec3(0.0 / 255.0, 33.0 / 255.0, 127.0 / 255.0);
			second = glm::vec3(87.0 / 255.0, 127.0 / 255.0, 237.0 / 255.0);
			break;

		case GREEN:
			name = "green";
			main = glm::vec3(72.0 / 255.0, 145.0 / 255.0, 0.0 / 255.0);
			second = glm::vec3(88.0 / 255.0, 211.0 / 255.0, 0.0 / 255.0);
			break;

		case GRAY:
			name = "gray";
			main = glm::vec3(56.0 / 255.0, 56.0 / 255.0, 56.0 / 255.0);
			second = glm::vec3(104.0 / 255.0, 104.0 / 255.0, 104.0 / 255.0);
			break;
	}
}


TankColor actors::GetColor(std::string name)
{
	if (name == "blue")
	{
		return BLUE;
	}

	if (name == "red")
	{
		return RED;
	}

	if (name == "green")
	{
		return GREEN;
	}

	if (name == "gray")
	{
		return GRAY;
	}

	return BROWN;
}

