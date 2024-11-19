#include "homework_1/scene/material.h"


using namespace scene;


Material::Material(
	MaterialType _type,
	std::string _name,
	glm::vec3 _color,
	GLfloat _friction,
	bool _deform
)
	: type(_type)
	, name(_name)
	, color(_color)
	, friction(_friction)
	, deform(_deform)
{
}


Material::Material()
	: type(ERROR)
	, name("err")
	, color(glm::vec3(0))
	, friction(1.0f)
	, deform(true)
{
}


Material::Material(MaterialType material)
	: Material()
{
	type = material;

	switch (material)
	{
	// Grass material
	case GRASS:
		name = "grass";
		color = glm::vec3(44.0 / 255.0, 150.0 / 255.0, 2.0 / 255.0);
		friction = 1.0f;
		deform = true;

		break;

	// Dirt material
	case DIRT:
		name = "dirt";
		color = glm::vec3(119.0 / 255.0, 65.0 / 255.0, 0.0 / 255.0);
		friction = 1.0f;
		deform = true;

		break;

	// Stone material
	case STONE:
		name = "stone";
		color = glm::vec3(112.0 / 255.0, 105.0 / 255.0, 85.0 / 255.0);
		friction = 1.0f;
		deform = false;

		break;

	// Sand material
	case SAND:
		name = "sand";
		color = glm::vec3(246.0 / 255.0, 249.0 / 255.0, 37.0 / 255.0);
		friction = 1.0f;
		deform = true;

		break;

	// Metal material
	case METAL:
		name = "metal";
		color = glm::vec3(130.0 / 255.0, 130.0 / 255.0, 130.0 / 255.0);
		friction = 1.0f;
		deform = false;

		break;

	// Error - something went wrong
	default:
		break;
	}
}


Landmass::Landmass(
	std::function<GLfloat (GLfloat)> baseGen,
	std::function<GLfloat (GLfloat)> heightGen,
	Material materialInfo
)
{
	pointCount = 128;
	material = materialInfo;

	for (GLuint i = 0; i <= pointCount; ++i)
	{
		basePoints.push_back(baseGen(i));
		heightPoints.push_back(heightGen(i));
	}
}


Landmass::~Landmass()
{
	basePoints.clear();
	heightPoints.clear();
}


std::vector<GLfloat>* Landmass::GetBasePoints()
{
	return &basePoints;
}


std::vector<GLfloat>* Landmass::GetHeightPoints()
{
	return &heightPoints;
}

std::string Landmass::GetMaterialName() const
{
	return material.name;
}


bool Landmass::CanBeDeformed() const
{
	return material.deform;
}


