#include "homework1.h"


/*
	Class constructors and destructors
*/

hw1::Homework1::Homework1()
{
	materialList = std::vector<scene::Material>();
	sceneList = std::map<scene::LevelType, scene::Scene>();
	currentScene = nullptr;
}


hw1::Homework1::~Homework1()
{
}


/*
	Init() function: sets up the camera, runs setup functions
*/

void hw1::Homework1::Init()
{
	// Set all relevant stuff up - this was split into multiple parts for modularization
	debugMode = false;
	PlayerConfig();

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	SceneListSetup();
	MaterialListSetup();
	MeshSetup();
	ActorSetup();
}


/*
	Frame update functions
*/

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

	// Update actors that move 'automatically'
	UpdateActors(deltaTimeSeconds);
}


void hw1::Homework1::FrameEnd()
{
}


/*
	Input update functions
*/

void hw1::Homework1::OnInputUpdate(float deltaTime, int mods)
{
	GLfloat deltaStep = 100.0f;
	GLfloat deltaAngle = AI_MATH_PI / 4;

	GLfloat xOldP1 = player1->GetActorPosition().first;
	GLfloat xOldP2 = player2->GetActorPosition().first;

	GLfloat bAngOldP1 = player1->GetBarrelAngle();
	GLfloat bAngOldP2 = player2->GetBarrelAngle();

	GLfloat xMoveP1 = deltaTime * deltaStep * std::cos(player1->GetActorAngle());
	GLfloat xMoveP2 = deltaTime * deltaStep * std::cos(player2->GetActorAngle());

	GLfloat bAngMove = deltaTime * deltaAngle;

	GLfloat newX, newY, newAngle, newBarrel;

	// Tank movement

	if (window->KeyHold(GLFW_KEY_A))
	{
		// Move player 1 to the left
		newX = xOldP1 - xMoveP1;
		newX = (newX < 50) ? 50 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player1->SetActorPosition({ newX, newY });
		player1->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_D))
	{
		// Move player 1 to the right
		newX = xOldP1 + xMoveP1;
		newX = (newX > 1230) ? 1230 : newX;
		newX = (newX > xOldP2 - 60) ? xOldP2 - 61 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player1->SetActorPosition({ newX, newY });
		player1->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_LEFT))
	{
		// Move player 2 to the left
		newX = xOldP2 - xMoveP2;
		newX = (newX < 50) ? 50 : newX;
		newX = (newX < xOldP1 + 60) ? xOldP1 + 61 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player2->SetActorPosition({ newX, newY });
		player2->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_RIGHT))
	{
		// Move player 2 to the right
		newX = xOldP2 + xMoveP2;
		newX = (newX > 1230) ? 1230 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player2->SetActorPosition({ newX, newY });
		player2->SetActorAngle(newAngle);
	}


	// Barrel movement

	if (window->KeyHold(GLFW_KEY_W))
	{
		// Move player 1's barrel to the left
		newBarrel = bAngOldP1 + bAngMove;

		player1->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		// Move player 1's barrel to the right
		newBarrel = bAngOldP1 - bAngMove;

		player1->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_DOWN))
	{
		// Move player 2's barrel to the left
		newBarrel = bAngOldP2 + bAngMove;

		player2->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_UP))
	{
		// Move player 2's barrel to the right
		newBarrel = bAngOldP2 - bAngMove;

		player2->SetBarrelAngle(newBarrel);
	}

}


void hw1::Homework1::OnKeyPress(int key, int mods)
{
	// Shooting

	if (key == GLFW_KEY_SPACE && !renderBullet1)
	{
		// Player 1 shooting
		renderBullet1 = true;
	}

	if (key == GLFW_KEY_ENTER && !renderBullet2)
	{
		// Player 2 shooting
		renderBullet2 = true;
	}


	// Debug

	if (key == GLFW_KEY_COMMA && debugMode)
	{
		player1->Debug();
		player2->Debug();
	}
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


/*
	Menu functions
*/

void hw1::Homework1::PlayerConfig()
{
	std::string color1, color2;

	// TODO
	std::cout << "Welcome to Tank Wars!\n";
	std::cout << "Made by Badescu Andrei-Cristian, Nov. 2024\n";

	std::cout << "\n\n";
	std::cout << "Press [A] and [D]/[Left] and [Right] to move.\n";
	std::cout << "Press [W] and [S]/[Up] and [Down] to aim.\n";
	std::cout << "Press [Space]/[Enter] to shoot.\n";

	std::cout << "\n\n";
	std::cout << "Choose color settings for P1 and P2. Note: if the input is invalid, the color will be set to 'brown'.\n";
	std::cout << "Colors available: brown, red, blue, green, gray.\n";
	std::cout << "<P1_COLOR>: ";
	std::cin >> color1;
	std::cout << "<P2_COLOR>: ";
	std::cin >> color2;

	std::cout << "\n\n";
	std::cout << "Choose level. Note: if the input is invalid, the 'basic' level will be chosen.\n";
	std::cout << "Levels available: basic, hills, sandy, tunnel\n";
	std::cout << "<LEVEL>: ";
	std::cin >> levelName;

	colorP1 = actors::GetColor(color1);
	colorP2 = actors::GetColor(color2);
}


/*
	Setup functions
*/

void hw1::Homework1::SceneListSetup()
{
	sceneList = std::map<scene::LevelType, scene::Scene>();

	// Load all enabled levels
	for (auto type : scene::AllowedLevelTypes)
	{
		scene::Scene* newScene = new scene::Scene(type);
		sceneList.insert({ type, *newScene });
	}

	// TODO: Level setup? Main menu?
	currentScene = SelectLevel(levelName);
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
	glm::vec3 A(0, 0, 0);
	glm::vec3 B(1, 0, 0);
	glm::vec3 C(1, 1, 0);
	glm::vec3 D(0, 1, 0);

	std::vector<GLuint> squareIndices = { 0, 1, 2, 3, 0, 2 };
	std::vector<GLuint> lowLeftIndices = { 0, 1, 3 };
	std::vector<GLuint> lowRightIndices = { 0, 1, 2 };
	std::vector<GLuint> highRightIndices = { 1, 2, 3 };
	std::vector<GLuint> highLeftIndices = { 2, 3, 0 };


	// For each material type, create the geometry associated with it
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


void hw1::Homework1::ActorSetup()
{
	actorList = std::map<std::string, actors::Actor>();
	auto data = currentScene->GetSceneData();
	auto heights = data->stripes[data->stripeCount].getHeightPoints();

	GLfloat anglePlayer1 = GetSceneAngle(data->spawnP1.first);
	GLfloat anglePlayer2 = GetSceneAngle(data->spawnP2.first);


	// Player1-related actors setup
	player1 = new actors::TankActor(colorP1, 1);
	player1->SetActorAngle(anglePlayer1);
	player1->SetActorPosition(data->spawnP1);
	player1->SetBarrelAngle(-AI_MATH_PI / 4);
	actorList[player1->GetActorName()] = *player1;


	// Player2-related actors setup
	player2 = new actors::TankActor(colorP2, 2);
	player2->SetActorAngle(anglePlayer2);
	player2->SetActorPosition(data->spawnP2);
	player2->SetBarrelAngle(AI_MATH_PI / 4);
	actorList[player2->GetActorName()] = *player2;


	// Bullet actors setup
	bullet1 = new actors::BulletActor(1);
	bullet1->SetActorAngle(0);
	bullet1->SetActorPosition({ 0, 0 });
	actorList[bullet1->GetActorName()] = *bullet1;
	bullet2 = new actors::BulletActor(2);
	bullet2->SetActorAngle(0);
	bullet2->SetActorPosition({ 0, 0 });
	actorList[bullet2->GetActorName()] = *bullet2;


	// Mesh list setup
	for (std::pair<std::string, actors::Actor> actor : actorList)
	{
		for (auto mesh : actor.second.GetMeshList())
		{
			AddMeshToList(mesh);
		}
	}

	renderBullet1 = false;
	renderBullet2 = false;
	renderPlayer1 = true;
	renderPlayer2 = true;
}


/*
	Helper functions
*/

void hw1::Homework1::UpdateActors(GLfloat deltaTime)
{
	// Update all bullets
	
}


// Render the current scene. Uses currentScene variable
void hw1::Homework1::RenderScene()
{
	auto sceneData = currentScene->GetSceneData();

	// Render actors
	RenderPlayers();
	RenderBullets();

	// Render layers one by one
	for (int layer = 1; layer <= sceneData->stripeCount; ++layer)
	{
		RenderLayer(layer);
	}
}


void hw1::Homework1::RenderBullets()
{
	if (renderBullet1)
	{
		RenderBullet1();
	}

	if (renderBullet2)
	{
		RenderBullet2();
	}
}


void hw1::Homework1::RenderBullet1()
{
	RenderMesh2D(
		meshes["bullet_1"],
		shaders["VertexColor"],
		bullet1->GetBulletObj()->GetFinalMatrix()
	);
}


void hw1::Homework1::RenderBullet2()
{
	RenderMesh2D(
		meshes["bullet_2"],
		shaders["VertexColor"],
		bullet1->GetBulletObj()->GetFinalMatrix()
	);
}


void hw1::Homework1::RenderPlayers()
{
	if (renderPlayer1)
	{
		RenderPlayer1();
	}

	if (renderPlayer2)
	{
		RenderPlayer2();
	}
}


void hw1::Homework1::RenderPlayer1()
{
	actors::ColorPicker color = actors::ColorPicker(colorP1);

	RenderMesh2D(
		meshes["tank_barrel_1_" + color.name],
		shaders["VertexColor"],
		player1->GetTankBarrel()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_body_1_" + color.name],
		shaders["VertexColor"],
		player1->GetTankBody()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_lifebar_1_" + color.name],
		shaders["VertexColor"],
		player1->GetTankLifebar()->GetFinalMatrix()
	);

	for (int i = 0; i < 20; ++i)
	{
		RenderMesh2D(
			meshes["tank_trail_1_" + color.name + "_" + std::to_string(i)],
			shaders["VertexColor"],
			player1->GetTankTrail()[i]->GetFinalMatrix()
		);
	}
}


void hw1::Homework1::RenderPlayer2()
{
	actors::ColorPicker color = actors::ColorPicker(colorP2);

	RenderMesh2D(
		meshes["tank_barrel_2_" + color.name],
		shaders["VertexColor"],
		player2->GetTankBarrel()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_body_2_" + color.name],
		shaders["VertexColor"],
		player2->GetTankBody()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_lifebar_2_" + color.name],
		shaders["VertexColor"],
		player2->GetTankLifebar()->GetFinalMatrix()
	);

	for (int i = 0; i < 20; ++i)
	{
		RenderMesh2D(
			meshes["tank_trail_2_" + color.name + "_" + std::to_string(i)],
			shaders["VertexColor"],
			player2->GetTankTrail()[i]->GetFinalMatrix()
		);
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


GLfloat hw1::Homework1::GetSceneHeight(GLfloat xPos)
{

	GLfloat heightLeft = GetSceneHeight((GLuint)xPos / 10);
	GLfloat heightRight = GetSceneHeight((GLuint)xPos / 10 + 1);

	GLfloat offset = xPos - (GLuint)xPos;
	GLuint distance = (GLuint)xPos - (GLuint)xPos / 10 * 10;

	GLfloat fraction = distance + offset;

	return heightLeft + (heightRight - heightLeft) * (fraction / 10);
}


GLfloat hw1::Homework1::GetSceneHeight(GLuint index)
{
	auto data = currentScene->GetSceneData();

	for (GLuint i = 1; i <= data->stripeCount; ++i)
	{
		auto height = (*data->stripes[i].getHeightPoints())[index];
		auto base = (*data->stripes[i].getBasePoints())[index];

		if (height - base > epsilon)
		{
			return height;
		}
	}

	return 0;
}


GLfloat hw1::Homework1::GetSceneAngle(GLfloat xPos)
{
	GLuint n = (GLuint)xPos;
	GLuint index = n / 10;


	GLfloat h0 = GetSceneHeight(index - 1);
	GLfloat h1 = GetSceneHeight(index);
	GLfloat h2 = GetSceneHeight(index + 1);

	GLfloat angleFront = utils::GetTerrainAngle(h1, h2);
	GLfloat angleBack = utils::GetTerrainAngle(h0, h1);

	return angleBack;
}


scene::Scene* hw1::Homework1::SelectLevel(std::string name)
{
	return &sceneList[scene::LevelType::BASIC_LEVEL];
}


bool hw1::Homework1::CheckBoxCollision(
	std::pair<GLfloat, GLfloat> a,
	std::pair<GLfloat, GLfloat> b,
	std::pair<GLfloat, GLfloat> d,
	std::pair<GLfloat, GLfloat> m
)
{
	glm::vec2 amVec = glm::vec2(m.first - a.first, m.second - a.second);
	glm::vec2 abVec = glm::vec2(b.first - a.first, b.second - a.second);
	glm::vec2 adVec = glm::vec2(d.first - a.first, d.second - a.second);

	GLfloat am_ab = glm::dot(amVec, abVec);
	GLfloat ab_ab = glm::dot(abVec, abVec);

	GLfloat am_ad = glm::dot(amVec, adVec);
	GLfloat ad_ad = glm::dot(adVec, adVec);

	return (epsilon < am_ab) && (epsilon < ab_ab - am_ab) && (epsilon < am_ad) && (epsilon < ad_ad - am_ad);
}
