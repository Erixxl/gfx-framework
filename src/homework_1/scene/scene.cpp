#include "homework_1/scene/scene.h"


using namespace scene;


SceneData::SceneData(
	LevelType _level,
	glm::vec3 _background,
	std::vector<Landmass> _stripes,
	GLuint _stripeCount
)
	: level(_level)
	, background(_background)
	, stripes(_stripes)
	, stripeCount(_stripeCount) { }


SceneData::SceneData()
	: level(ERROR_LEVEL)
	, background(glm::vec3(1))
	, stripes(std::vector<Landmass>())
	, stripeCount(0) { }


Scene::Scene(LevelType _level)
{
	data = SceneData();

	auto baseLayer = [this](GLfloat x) { return LineFunc(x, 0); };
	auto fenceLine = [this](GLfloat x) { return 300 + FenceFunc(x, 1); };

	data.stripes.push_back(Landmass(
		baseLayer,
		baseLayer,
		Material()
	));

	data.level = _level;

	switch (_level)
	{
	case BASIC_LEVEL:
		data.stripes.push_back(Landmass(
			baseLayer,
			fenceLine,
			Material(GRASS)
		));
		data.stripeCount = 1;
		data.background = glm::vec3(0.678f, 0.847f, 0.902f);

		break;

	case GRASS_LEVEL:
		break;

	case DESERT_LEVEL:
		break;

	case BUILDING_LEVEL:
		break;

	case TUNNEL_LEVEL:
		break;

	default:
		break;
	}
}


Scene::Scene()
	: Scene::Scene(ERROR_LEVEL) { }


Scene::~Scene()
{
}


inline GLfloat Scene::LineFunc(GLfloat x, GLfloat a)
{
	return a * x;
}


inline GLfloat Scene::SinFunc(GLfloat x, GLfloat a, GLfloat b)
{
	return b * std::sin(a * x);
}


inline GLfloat Scene::FenceFunc(GLfloat x, GLfloat b)
{
	if ((GLuint)x % 20 < 10)
	{
		return b * (x - (GLuint)x + (GLuint)x % 20);
	}

	return b * (20 - x + (GLuint)x - (GLuint)x % 20);
}


SceneData* Scene::GetSceneData()
{
	return &data;
}


