#include "homework1.h"


hw1::Homework1::Homework1()
{
}


hw1::Homework1::~Homework1()
{
}


void hw1::Homework1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Set all relevant stuff up - this was split into multiple parts for modularization
	SceneListSetup();
	MaterialListSetup();
	MeshSetup();

	// TODO: Level setup? Main menu?
	currentScene = &sceneList[scene::LevelType::BASIC_LEVEL];
}


void hw1::Homework1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	auto bgColor = currentScene->GetSceneData()->background;
	glClearColor(bgColor.r, bgColor.g, bgColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void hw1::Homework1::Update(float deltaTimeSeconds)
{
	// Start rendering the scene
	RenderScene();

	auto mat = utils::Scale(100, 100);
//	RenderMesh2D(meshes["grass_highRight"], shaders["VertexColor"], mat);
}


void hw1::Homework1::FrameEnd()
{
}


void hw1::Homework1::OnInputUpdate(float deltaTime, int mods)
{
}


void hw1::Homework1::OnKeyPress(int key, int mods)
{
}


void hw1::Homework1::OnKeyRelease(int key, int mods)
{
}


void hw1::Homework1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void hw1::Homework1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void hw1::Homework1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void hw1::Homework1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void hw1::Homework1::OnWindowResize(int width, int height)
{
}


void hw1::Homework1::SceneListSetup()
{
	sceneList = std::map<scene::LevelType, scene::Scene>();

	// Load all enabled levels
	for (auto type : scene::AllowedLevelTypes)
	{
		scene::Scene* newScene = new scene::Scene(type);
		sceneList.insert({ type, *newScene });
	}
}


void hw1::Homework1::MaterialListSetup()
{
	materialList = std::vector<scene::Material>();

	// Load all materials
	for (auto type : scene::AllMaterialTypes)
	{
		materialList.push_back(scene::Material(type));
	}
}


void hw1::Homework1::MeshSetup()
{
	// Mesh boundry - 1x1 square with lower left corner in (0, 0)
	glm::vec3 A(0, 0, 0), B(1, 0, 0), C(1, 1, 0), D(0, 1, 0);

	std::vector<GLuint> squareIndices = { 0, 1, 2, 3, 0, 2 };
	std::vector<GLuint> lowLeftIndices = { 0, 1, 3 };
	std::vector<GLuint> lowRightIndices = { 0, 1, 2 };
	std::vector<GLuint> highRightIndices = { 1, 2, 3 };
	std::vector<GLuint> highLeftIndices = { 2, 3, 0 };

	for (auto iter = materialList.begin(); iter != materialList.end(); ++iter)
	{
		Mesh* square = new Mesh(iter->name + "_square");
		Mesh* lowLeft = new Mesh(iter->name + "_lowLeft");
		Mesh* lowRight = new Mesh(iter->name + "_lowRight");
		Mesh* highRight = new Mesh(iter->name + "_highRight");
		Mesh* highLeft = new Mesh(iter->name + "_highLeft");

		std::vector<VertexFormat> vertices = {
			VertexFormat(A, iter->color),
			VertexFormat(B, iter->color),
			VertexFormat(C, iter->color),
			VertexFormat(D, iter->color)
		};

		square->InitFromData(vertices, squareIndices);
		lowLeft->InitFromData(vertices, lowLeftIndices);
		lowRight->InitFromData(vertices, lowRightIndices);
		highRight->InitFromData(vertices, highRightIndices);
		highLeft->InitFromData(vertices, highLeftIndices);

		AddMeshToList(square);
		AddMeshToList(lowLeft);
		AddMeshToList(lowRight);
		AddMeshToList(highRight);
		AddMeshToList(highLeft);
	}
}


// Render the current scene. Uses currentScene variable
void hw1::Homework1::RenderScene()
{
	auto sceneData = currentScene->GetSceneData();

	// Render layers one by one
	for (int layer = 1; layer <= sceneData->stripeCount; ++layer)
	{
		RenderLayer(layer);
	}
}


// Render an entire layer, slice by slice.
void hw1::Homework1::RenderLayer(GLuint layerNumber)
{
	for (GLuint i = 0; i < 128; ++i)
	{
		RenderLayerSlice(layerNumber, i);
	}
}


// Render the layer slice between widths k and k + 1.
void hw1::Homework1::RenderLayerSlice(GLuint layerNumber, GLuint k)
{
	auto sceneData = currentScene->GetSceneData();

	// Guard if clause
	if (k >= 128 || layerNumber > sceneData->stripeCount)
	{
		std::cout << "Error: trying to render invalid data\n";
		return;
	}


	// Might need rework to enable resets...
	auto* bases = sceneData->stripes[layerNumber].getBasePoints();
	auto* heights = sceneData->stripes[layerNumber].getHeightPoints();

	std::string materialName = sceneData->stripes[layerNumber].getMaterialName();


	// If slice is too narrow, treat it as missing ground
	if (std::abs((*heights)[k + 1] - (*bases)[k + 1]) <= epsilon &&
		std::abs((*heights)[k] - (*bases)[k]) <= epsilon)
	{
		// Comment after testing
		std::cout << "Layer " << layerNumber << ", slice [" << k
			<< "-" << k + 1 << "]: too small to render\n";
		return;
	}


	// Get the min, max and difference between heights and bases
	GLuint minHeight = std::min((*heights)[k], (*heights)[k + 1]);
	GLuint maxHeight = std::max((*heights)[k], (*heights)[k + 1]);
	GLuint deltaHeight = maxHeight - minHeight;

	GLuint minBase = std::min((*bases)[k], (*bases)[k + 1]);
	GLuint maxBase = std::max((*bases)[k], (*bases)[k + 1]);
	GLuint deltaBase = maxBase - minBase;

	GLuint rectSide = minHeight - maxBase;


	// Render material slice using provided meshes
	bool highRising = ((*heights)[k] < (*heights)[k + 1]);
	bool lowRising = ((*bases)[k] < (*bases)[k + 1]);
	glm::mat3 modelMatrix;


	// Upper triangle. Render if slope is noticeable enough.
	if (deltaHeight > epsilon)
	{
		modelMatrix = utils::Translate(k * 10, minHeight);
		modelMatrix = modelMatrix * utils::Scale(10, deltaHeight);

		if (highRising)
		{
			RenderMesh2D(meshes[materialName + "_lowRight"], shaders["VertexColor"], modelMatrix);
		}
		else
		{
			RenderMesh2D(meshes[materialName + "_lowLeft"], shaders["VertexColor"], modelMatrix);
		}
	}


	// Lower triangle. Render if slope is noticeable enough.
	if (deltaBase > epsilon)
	{
		modelMatrix = utils::Translate(k * 10, maxBase);
		modelMatrix = modelMatrix * utils::Scale(10, deltaBase);
		modelMatrix = modelMatrix * utils::Translate(0, -1);

		if (lowRising)
		{
			RenderMesh2D(meshes[materialName + "_highLeft"], shaders["VertexColor"], modelMatrix);
		}
		else
		{
			RenderMesh2D(meshes[materialName + "_highRight"], shaders["VertexColor"], modelMatrix);
		}
	}


	// Main rectangle. Render if there is enough space.
	if (rectSide > epsilon)
	{
		modelMatrix = utils::Translate(k * 10, maxBase);
		modelMatrix = modelMatrix * utils::Scale(10, rectSide);

		RenderMesh2D(meshes[materialName + "_square"], shaders["VertexColor"], modelMatrix);
	}
}


