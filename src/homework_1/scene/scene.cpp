#include "homework_1/scene/scene.h"


using namespace scene;
using namespace utils;


SceneData::SceneData(
	LevelType _level,
	glm::vec3 _background,
	std::vector<Landmass> _stripes,
	GLuint _stripeCount,
	std::pair<GLfloat, GLfloat> _spawnP1,
	std::pair<GLfloat, GLfloat> _spawnP2
)
	: level(_level)
	, background(_background)
	, stripes(_stripes)
	, stripeCount(_stripeCount)
	, spawnP1(_spawnP1)
	, spawnP2(_spawnP2)
{
}


SceneData::SceneData()
	: level(ERROR_LEVEL)
	, background(glm::vec3(1))
	, stripes(std::vector<Landmass>())
	, stripeCount(0)
	, spawnP1({ 40, 200 })
	, spawnP2({ 1240, 200 })
{
}


Scene::Scene(LevelType _level)
{
	data = SceneData();

	auto baseLayer = [](GLfloat x) { return LineFunc(x, 0); };

	data.stripes.push_back(Landmass(
		baseLayer,
		baseLayer,
		Material()
	));

	data.level = _level;

	switch (_level)
	{
	case BASIC_LEVEL:
		BasicLevelGen();
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
	: Scene::Scene(ERROR_LEVEL)
{
}


Scene::~Scene()
{
}


SceneData* Scene::GetSceneData()
{
	return &data;
}


void Scene::BasicLevelGen()
{
	auto baseLayer = [](GLfloat x) { return LineFunc(x, 0); };
	auto fenceLine = [](GLfloat x) { return 300 + FenceFunc(x, 4.0f); };

	auto test1 = [](GLfloat x) { return 400.0 + CosFunc(x, 0.24, 25); };
	auto test2 = [](GLfloat x) { return 100 + LineFunc(x, 1.5) + SinFunc(x, 0.05, 50); };
	auto test3 = [](GLfloat x) { return 50 + abs(LineFunc(x, -0.5)); };

	data.stripes.push_back(Landmass(
		test2,
		test1,
		Material(GRASS)
	));

	data.stripes.push_back(Landmass(
		test3,
		test2,
		Material(DIRT)
	));

	data.stripes.push_back(Landmass(
		baseLayer,
		test3,
		Material(STONE)
	));

	data.stripeCount = 3;
	data.background = glm::vec3(0.678f, 0.847f, 0.902f);

	data.spawnP1 = { 350, test1(35) };
	data.spawnP2 = { 930, test1(93) };
}


