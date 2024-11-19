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
	data.level = _level;

	auto baseLayer = [](GLfloat x) { return LineFunc(x, 0); };

	switch (_level)
	{
	case BASIC_LEVEL:
		BasicLevelGen();
		break;

	case GRASS_LEVEL:
		GrassLevelGen();
		break;

	case DESERT_LEVEL:
		DesertLevelGen();
		break;

	case TUNNEL_LEVEL:
		TunnelLevelGen();
		break;

	default:
		break;
	}

	data.stripes.push_back(Landmass(
		baseLayer,
		baseLayer,
		Material()
	));
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


void Scene::GrassLevelGen()
{
	auto height = [](GLfloat x) { return 200 + SinFunc(x, 0.1, 100) + SinFunc(x, 0.2, 50) + CosFunc(x, 1, 10); };

	data.stripes.push_back(Landmass(
		baseLayer,
		height,
		Material(GRASS)
	));

	data.stripeCount = 1;
	data.background = glm::vec3(113.0 / 255.0, 169.0 / 255.0, 252.0 / 255.0);

	data.spawnP1 = { 200, height(20) };
	data.spawnP2 = { 1080, height(108) };
}


void Scene::DesertLevelGen()
{
	auto height = [](GLfloat x) { return 200 + SinFunc(x, 0.2, 100) + CosFunc(x, 0.3, 80); };

	data.stripes.push_back(Landmass(
		baseLayer,
		height,
		Material(SAND)
	));

	data.stripeCount = 1;
	data.background = glm::vec3(113.0 / 255.0, 169.0 / 255.0, 252.0 / 255.0);

	data.spawnP1 = { 200, height(20) };
	data.spawnP2 = { 1080, height(108) };
}


void Scene::TunnelLevelGen()
{
	auto height = [](GLfloat x) { return 50 + LineFunc(x, 2); };
	auto base2 = [](GLfloat x) { return -0.0005 * (10 * x - 640) * (10 * x - 640) + 450; };
	auto ceiling = [](GLfloat x) { return 800; };

	data.stripes.push_back(Landmass(
		baseLayer,
		height,
		Material(METAL)
	));

	data.stripes.push_back(Landmass(
		base2,
		ceiling,
		Material(STONE)
	));

	data.stripeCount = 1;
	data.background = glm::vec3(100.0 / 255.0, 111.0 / 255.0, 127.0 / 255.0);

	data.spawnP1 = { 200, height(20) };
	data.spawnP2 = { 1080, height(108) };
}



