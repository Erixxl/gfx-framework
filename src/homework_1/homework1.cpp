#include "homework1.h"


using FloatPair = std::pair<GLfloat, GLfloat>;


/*
	Class constructors and destructors
*/

hw1::Homework1::Homework1()
{
}


hw1::Homework1::~Homework1()
{
}


/*
	Init() function: sets up the camera, runs setup functions
*/

void hw1::Homework1::Init()
{
	std::srand(std::time(NULL));

	bulletDamage = 27.0f;
	initialHealth = 100.0f;
	debugMode = true;
	playing = true;

	PlayerConfig();

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
	ActorSetup();
	TrailSetup();
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
	// Update terrain elements
	UpdateTerrain(deltaTimeSeconds);

	// Start rendering the scene
	RenderScene();

	// Update actors that move 'automatically'
	UpdateActors(deltaTimeSeconds);

	// Show ending text
	if (!playing)
	{
		// TODO
	}
}


void hw1::Homework1::FrameEnd()
{
	if (!(renderPlayer1 && renderPlayer2) && playing)
	{
		playing = false;

		std::cout << "Congratulations, player " << (renderPlayer1 ? 1 : 2) << "! Press [F] to exit.\n";
	}
}


/*
	Input update functions
*/

void hw1::Homework1::OnInputUpdate(float deltaTime, int mods)
{
	// Check if the game has ended
	if (!playing)
	{
		return;
	}

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


	/*
		Tank movement

		The movement of both players is restricted to the
		playable area (x in [50, 1230]) and also by the
		other player's position
	*/

	if (window->KeyHold(GLFW_KEY_A) && renderPlayer1)
	{
		// Move player 1 to the left
		newX = xOldP1 - xMoveP1;
		newX = (newX < 50) ? 50 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player1->SetActorPosition({ newX, newY });
		player1->SetActorAngle(newAngle);

		spawn1->SetActorPosition({ newX, newY });
		spawn1->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_D) && renderPlayer1)
	{
		// Move player 1 to the right
		newX = xOldP1 + xMoveP1;
		newX = (newX > 1230) ? 1230 : newX;
		newX = (newX > xOldP2 - 60) ? xOldP2 - 61 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player1->SetActorPosition({ newX, newY });
		player1->SetActorAngle(newAngle);

		spawn1->SetActorPosition({ newX, newY });
		spawn1->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_LEFT) && renderPlayer2)
	{
		// Move player 2 to the left
		newX = xOldP2 - xMoveP2;
		newX = (newX < 50) ? 50 : newX;
		newX = (newX < xOldP1 + 60) ? xOldP1 + 61 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player2->SetActorPosition({ newX, newY });
		player2->SetActorAngle(newAngle);

		spawn2->SetActorPosition({ newX, newY });
		spawn2->SetActorAngle(newAngle);
	}

	if (window->KeyHold(GLFW_KEY_RIGHT) && renderPlayer2)
	{
		// Move player 2 to the right
		newX = xOldP2 + xMoveP2;
		newX = (newX > 1230) ? 1230 : newX;

		newY = GetSceneHeight(newX);
		newAngle = GetSceneAngle(newX);

		player2->SetActorPosition({ newX, newY });
		player2->SetActorAngle(newAngle);

		spawn2->SetActorPosition({ newX, newY });
		spawn2->SetActorAngle(newAngle);
	}


	/*
		Barrel movement

		The movement of the barrel is restricted
		to the interval [ -3/8 * PI, 3/8 * PI]
	*/

	if (window->KeyHold(GLFW_KEY_W) && renderPlayer1)
	{
		// Move player 1's barrel to the left
		newBarrel = std::min(bAngOldP1 + bAngMove, 0.375f * AI_MATH_PI_F);

		player1->SetBarrelAngle(newBarrel);
		spawn1->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_S) && renderPlayer1)
	{
		// Move player 1's barrel to the right
		newBarrel = std::max(bAngOldP1 - bAngMove, -0.375f * AI_MATH_PI_F);

		player1->SetBarrelAngle(newBarrel);
		spawn1->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_DOWN) && renderPlayer2)
	{
		// Move player 2's barrel to the left
		newBarrel = std::min(bAngOldP2 + bAngMove, 0.375f * AI_MATH_PI_F);

		player2->SetBarrelAngle(newBarrel);
		spawn2->SetBarrelAngle(newBarrel);
	}

	if (window->KeyHold(GLFW_KEY_UP) && renderPlayer2)
	{
		// Move player 2's barrel to the right
		newBarrel = std::max(bAngOldP2 - bAngMove, -0.375f * AI_MATH_PI_F);

		player2->SetBarrelAngle(newBarrel);
		spawn2->SetBarrelAngle(newBarrel);
	}


	/*
		Magnitude adjustment

		Increase/decrease the magnitude used to compute the bullet path
		Magnitude is restricted to [20, 80]
	*/

	if (window->KeyHold(GLFW_KEY_1) && renderPlayer1)
	{
		// Increase magnitude
		newX = spawn1->GetMagnitude();
		newX = std::min(newX + 5, 80.0f);
		spawn1->SetMagnitude(newX);
	}

	if (window->KeyHold(GLFW_KEY_2) && renderPlayer1)
	{
		// Decrease magnitude
		newX = spawn1->GetMagnitude();
		newX = std::max(newX - 5, 20.0f);
		spawn1->SetMagnitude(newX);
	}

	if (window->KeyHold(GLFW_KEY_KP_1) && renderPlayer2)
	{
		// Increase magnitude
		newX = spawn2->GetMagnitude();
		newX = std::min(newX + 5, 80.0f);
		spawn2->SetMagnitude(newX);
	}

	if (window->KeyHold(GLFW_KEY_KP_2) && renderPlayer2)
	{
		// Decrease magnitude
		newX = spawn2->GetMagnitude();
		newX = std::max(newX - 5, 20.0f);
		spawn2->SetMagnitude(newX);
	}
}


void hw1::Homework1::OnKeyPress(int key, int mods)
{
	// Shooting
	GLfloat angle;
	GLfloat magnitude;

	// Player 1 shooting
	if (key == GLFW_KEY_SPACE && !renderBullet1 && playing)
	{
		magnitude = spawn1->GetMagnitude();

		renderBullet1 = true;
		angle = AI_MATH_HALF_PI + spawn1->GetActorAngle() + spawn1->GetBarrelAngle();

		bullet1->SetActorPosition(spawn1->GetSpawnCoords());
		bullet1->SetVelocity(magnitude * std::cos(angle), magnitude * std::sin(angle));
		bullet1->SetBulletDamage(bulletDamage);
	}

	// Player 2 shooting
	if (key == GLFW_KEY_ENTER && !renderBullet2 && playing)
	{
		magnitude = spawn2->GetMagnitude();

		renderBullet2 = true;
		angle = AI_MATH_HALF_PI + spawn2->GetActorAngle() + spawn2->GetBarrelAngle();

		bullet2->SetActorPosition(spawn2->GetSpawnCoords());
		bullet2->SetVelocity(magnitude * std::cos(angle), magnitude * std::sin(angle));
		bullet2->SetBulletDamage(bulletDamage);
	}

	// Exit the game after winning
	if (key == GLFW_KEY_F && !playing)
	{
		Exit();
		return;
	}


	// Enable/disable debug mode
	if (key == GLFW_KEY_P)
	{
		debugMode = !debugMode;

		std::cout << "Debug mode changed to " << (debugMode ? "ON" : "OFF");
		std::cout << "\n\n";
	}

	// Print debug text
	if (key == GLFW_KEY_COMMA && debugMode)
	{
		std::cout << "Printing debug info:\n";
		std::cout << ">> List of actors and whether they are being rendered:\n";

		std::cout << "\n>> Player1: " << (renderPlayer1 ? "" : "not ") << "rendering\n";
		player1->Debug();

		std::cout << "\n>> Bullet1: " << (renderBullet1 ? "" : "not ") << "rendering\n";
		bullet1->Debug();

		std::cout << "\n>> Spawn1: " << (debugMode ? "" : "not ") << "rendering\n";
		spawn1->Debug();

		std::cout << "\n>> Player2: " << (renderPlayer2 ? "" : "not ") << "rendering\n";
		player2->Debug();

		std::cout << "\n>> Bullet2: " << (renderBullet2 ? "" : "not ") << "rendering\n";
		bullet2->Debug();

		std::cout << "\n>> Spawn2: " << (debugMode ? "" : "not ") << "rendering\n";
		spawn2->Debug();

		std::cout << '\n';
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
	std::cout << "Press [P] to enable the debug mode (disabled by default).\n";
	std::cout << "Press [,] in debug mode to print debug info.\n";

	std::cout << "\n\n";
	std::cout << "Choose color settings for P1 and P2. Note: if the input is invalid, the color will be set to 'brown'.\n";
	std::cout << "Colors available: brown, red, blue, green, gray.\n";
	std::cout << "<P1_COLOR>: ";
	std::cin >> color1;
	std::cout << "<P2_COLOR>: ";
	std::cin >> color2;

	std::cout << "\n\n";
	std::cout << "Choose level. Note: if the input is invalid, the 'hills' level will be chosen.\n";
	std::cout << "Levels available: hills, desert, tunnel, layers\n";
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
	auto heights = data->stripes[data->stripeCount].GetHeightPoints();

	GLfloat anglePlayer1 = GetSceneAngle(data->spawnP1.first);
	GLfloat anglePlayer2 = GetSceneAngle(data->spawnP2.first);


	// Player1-related actors setup
	player1 = new actors::TankActor(colorP1, 1);
	player1->SetActorAngle(anglePlayer1);
	player1->SetActorPosition(data->spawnP1);
	player1->SetBarrelAngle(-AI_MATH_PI / 4);
	player1->SetLifepoints(initialHealth);
	actorList[player1->GetActorName()] = *player1;


	// Player2-related actors setup
	player2 = new actors::TankActor(colorP2, 2);
	player2->SetActorAngle(anglePlayer2);
	player2->SetActorPosition(data->spawnP2);
	player2->SetBarrelAngle(AI_MATH_PI / 4);
	player2->SetLifepoints(initialHealth);
	actorList[player2->GetActorName()] = *player2;


	// Bullet spawnpoint setup
	spawn1 = new actors::SpawnActor(1);
	spawn1->SetActorAngle(anglePlayer1);
	spawn1->SetBarrelAngle(-AI_MATH_PI / 4);
	spawn1->SetActorPosition(data->spawnP1);
	actorList[spawn1->GetActorName()] = *spawn1;

	spawn2 = new actors::SpawnActor(2);
	spawn2->SetActorAngle(anglePlayer2);
	spawn2->SetBarrelAngle(AI_MATH_PI / 4);
	spawn2->SetActorPosition(data->spawnP2);
	actorList[spawn2->GetActorName()] = *spawn2;


	// Bullet actors setup
	bullet1 = new actors::BulletActor(1);
	bullet1->SetActorAngle(0);
	bullet1->SetActorPosition({ 0, 0 });
	bullet1->SetBulletDamage(bulletDamage);
	actorList[bullet1->GetActorName()] = *bullet1;

	bullet2 = new actors::BulletActor(2);
	bullet2->SetActorAngle(0);
	bullet2->SetActorPosition({ 0, 0 });
	bullet2->SetBulletDamage(bulletDamage);
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


void hw1::Homework1::TrailSetup()
{
	Mesh* trail1 = new Mesh("trail_1");
	Mesh* trail2 = new Mesh("trail_2");

	std::vector<VertexFormat> vertices1 = {
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.5, 0.5, 0.5)),
	};

	std::vector<VertexFormat> vertices2 = {
		VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0.5, 0.5, 0.5)),
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5)),
	};

	std::vector<GLuint> indices1 = { 0, 1 };
	std::vector<GLuint> indices2 = { 0, 1 };

	trail1->SetDrawMode(GL_LINES);
	trail2->SetDrawMode(GL_LINES);

	trail1->InitFromData(vertices1, indices1);
	trail2->InitFromData(vertices2, indices2);

	AddMeshToList(trail1);
	AddMeshToList(trail2);
}


/*
	Render functions
*/

// Render the current scene. Uses currentScene variable
void hw1::Homework1::RenderScene()
{
	auto sceneData = currentScene->GetSceneData();

	// Render actors
	RenderPlayers();
	RenderBullets();

	// Render layers one by one
	for (int layer = 0; layer <= sceneData->stripeCount; ++layer)
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
		bullet2->GetBulletObj()->GetFinalMatrix()
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

	if (debugMode)
	{
		RenderSpawns();
	}
}


void hw1::Homework1::RenderPlayer1()
{
	GLfloat scale = player1->GetLifepoints();

	RenderMesh2D(
		meshes["tank_body_1"],
		shaders["VertexColor"],
		player1->GetTankBody()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_barrel_1"],
		shaders["VertexColor"],
		player1->GetTankBarrel()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_lifebar_1"],
		shaders["VertexColor"],
		player1->GetTankLifebar()->GetFinalMatrix() * utils::Scale(scale, 1)
	);

	RenderMesh2D(
		meshes["tank_lifebar_bkg_1"],
		shaders["VertexColor"],
		player1->GetTankLifebar()->GetFinalMatrix()
	);
}


void hw1::Homework1::RenderPlayer2()
{
	GLfloat scale = player2->GetLifepoints();

	RenderMesh2D(
		meshes["tank_body_2"],
		shaders["VertexColor"],
		player2->GetTankBody()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_barrel_2"],
		shaders["VertexColor"],
		player2->GetTankBarrel()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["tank_lifebar_2"],
		shaders["VertexColor"],
		player2->GetTankLifebar()->GetFinalMatrix() * utils::Scale(scale, 1)
	);

	RenderMesh2D(
		meshes["tank_lifebar_bkg_2"],
		shaders["VertexColor"],
		player2->GetTankLifebar()->GetFinalMatrix()
	);
}


void hw1::Homework1::RenderSpawns()
{
	RenderMesh2D(
		meshes["spawn_bullet_1"],
		shaders["VertexColor"],
		spawn1->GetOutline()->GetFinalMatrix()
	);

	RenderMesh2D(
		meshes["spawn_bullet_2"],
		shaders["VertexColor"],
		spawn2->GetOutline()->GetFinalMatrix()
	);
}


void hw1::Homework1::RenderTrails()
{
	if (renderPlayer1)
	{
		RenderTrail1();
	}

	if (renderPlayer2)
	{
		RenderTrail2();
	}
}


void hw1::Homework1::RenderTrail1()
{
	// Render first 20 segments
	FloatPair a, b;
	GLfloat mag = spawn1->GetMagnitude();
	GLfloat angle = AI_MATH_HALF_PI + spawn1->GetActorAngle() + spawn1->GetBarrelAngle();

	a = spawn1->GetSpawnCoords();
	b = { a.first, a.second };

	for (int i = 0; i < 20; ++i)
	{

	}
}


void hw1::Homework1::RenderTrail2()
{
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
	auto* bases = sceneData->stripes[layerNumber].GetBasePoints();
	auto* heights = sceneData->stripes[layerNumber].GetHeightPoints();

	std::string materialName = sceneData->stripes[layerNumber].GetMaterialName();


	// If slice is too narrow, treat it as missing ground
	if (std::abs((*heights)[k + 1] - (*bases)[k + 1]) <= epsilon &&
		std::abs((*heights)[k] - (*bases)[k]) <= epsilon)
	{
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


/*
	Update functions
*/

// Update actors that move without player input
void hw1::Homework1::UpdateActors(GLfloat deltaTime)
{
	GLfloat lifeLeft;
	FloatPair currPosition;
	FloatPair currVelocity;
	GLuint check = std::rand() % 100;


	// Update all bullets

	if (renderBullet1)
	{
		// Delete bullet, register damage
		if (CheckForCollision(
			bullet1->GetActorPosition(),
			player2->GetActorPosition(),
			bullet1->GetBulletRadius(),
			player2->GetHitRadius()
		))
		{
			renderBullet1 = false;
			bullet1->SetActorPosition({ 0, 0 });

			lifeLeft = player2->GetLifepoints() - bullet1->GetBulletDamage();

			if (debugMode)
			{
				std::cout << ">> Player 2 hit for " << bullet1->GetBulletDamage() << " damage.\n";
			}

			// Player 2 defeated
			if (lifeLeft < 0)
			{
				renderPlayer2 = false;
			}
			// Give player 2 a small boost the first time their hp drops below 10
			else if (lifeLeft < 10 && grazePlayer2)
			{
				grazePlayer2 = false;
				player2->SetLifepoints(10.0f);
			}
			else
			{
				player2->SetLifepoints(lifeLeft);
			}
		}
		// Modify position and velocity of bullet
		else
		{
			currPosition = bullet1->GetActorPosition();
			currVelocity = bullet1->GetVelocity();

			if (currPosition.second < 0)
			{
				renderBullet1 = false;
			}

			// Update position
			currPosition.first += currVelocity.first * deltaTime * 3;
			currPosition.second += currVelocity.second * deltaTime * 3;
			bullet1->SetActorPosition(currPosition);

			// Update velocity
			currVelocity.first -= gravity.first * deltaTime * 3;
			currVelocity.second -= gravity.second * deltaTime * 3;
			bullet1->SetVelocity(currVelocity.first, currVelocity.second);

			// Add a spinning visual effect
			bullet1->SetActorAngle(bullet1->GetActorAngle() + deltaTime);

			// Randomly decrease the damage of the bullet
			if (check >= 80 && bullet1->GetBulletDamage() > 5)
			{
				bullet1->SetBulletDamage(bullet1->GetBulletDamage() - check % 2);
			}
		}
	}

	if (renderBullet2)
	{
		// Delete bullet, register damage
		if (CheckForCollision(
			bullet2->GetActorPosition(),
			player1->GetActorPosition(),
			bullet2->GetBulletRadius(),
			player1->GetHitRadius()
		))
		{
			renderBullet2 = false;
			bullet2->SetActorPosition({ 0, 0 });

			lifeLeft = player1->GetLifepoints() - bullet2->GetBulletDamage();

			if (debugMode)
			{
				std::cout << ">> Player 1 hit for " << bullet1->GetBulletDamage() << " damage.\n";
			}

			// Player 1 defeated
			if (lifeLeft < 0)
			{
				renderPlayer1 = false;
			}
			// Give player 1 a small boost the first time their hp drops below 10
			else if (lifeLeft < 10 && grazePlayer1)
			{
				grazePlayer1 = false;
				player1->SetLifepoints(10.0f);
			}
			else
			{
				player1->SetLifepoints(lifeLeft);
			}
		}
		// Modify position and velocity of bullet
		else
		{
			currPosition = bullet2->GetActorPosition();
			currVelocity = bullet2->GetVelocity();

			if (currPosition.second < 0)
			{
				renderBullet2 = false;
			}

			// Update position
			currPosition.first += currVelocity.first * deltaTime * 3;
			currPosition.second += currVelocity.second * deltaTime * 3;
			bullet2->SetActorPosition(currPosition);

			// Update velocity
			currVelocity.first -= gravity.first * deltaTime * 3;
			currVelocity.second -= gravity.second * deltaTime * 3;
			bullet2->SetVelocity(currVelocity.first, currVelocity.second);

			// Add a spinning visual effect
			bullet2->SetActorAngle(bullet2->GetActorAngle() + deltaTime);

			// Randomly decrease the damage of the bullet
			if (check >= 80 && bullet2->GetBulletDamage() > 5)
			{
				bullet2->SetBulletDamage(bullet2->GetBulletDamage() - check % 2);
			}
		}
	}
}


void hw1::Homework1::UpdateTerrain(GLfloat deltaTime)
{
	UpdateTerrainHeights(deltaTime);

	if (renderBullet1)
	{
		UpdateTerrainHit(1);
	}

	if (renderBullet2)
	{
		UpdateTerrainHit(2);
	}
}


void hw1::Homework1::UpdateTerrainHeights(GLfloat deltaTime)
{
	auto data = currentScene->GetSceneData();

	GLfloat heightCenter, heightLeft, heightRight;

	for (GLuint i = 1; i <= 127; ++i)
	{
		heightLeft = GetSceneHeight(i - 1);
		heightCenter = GetSceneHeight(i);
		heightRight = GetSceneHeight(i + 1);

		if (heightCenter - heightLeft > 5.0f)
		{
			heightCenter -= deltaTime;
			heightLeft += deltaTime;
		}

		if (heightCenter - heightRight > 5.0f)
		{
			heightCenter -= deltaTime;
			heightRight += deltaTime;
		}

		SetSceneHeight(i - 1, heightLeft);
		SetSceneHeight(i, heightCenter);
		SetSceneHeight(i + 1, heightRight);
	}
}


void hw1::Homework1::UpdateTerrainHit(GLfloat bulletID)
{
	if (bulletID != 1 && bulletID != 2)
	{
		std::cout << "Error: bad bullet ID\n";
		return;
	}

	actors::BulletActor* bullet = bulletID == 1 ? bullet1 : bullet2;

	bool* render = bulletID == 1 ? &renderBullet1 : &renderBullet2;
	FloatPair pos = bullet->GetActorPosition();
	GLfloat radius = bullet->GetTerrainRadius();

	GLuint terrRadius = (GLuint)radius / 10;
	GLuint index = (GLuint)pos.first / 10;

	GLuint leftIndex, rightIndex;
	GLfloat newHeight;


	// Registered hit
	if (pos.second - GetSceneHeight(pos.first) < epsilon)
	{
		*render = false;

		leftIndex = (index > terrRadius ? index - terrRadius : 1);
		rightIndex = (index + terrRadius < 128 ? index + terrRadius : 127);

		std::cout << leftIndex << ' ' << rightIndex << '\n';

		// Update each terrain slice
		for (GLuint i = leftIndex + 1; i <= rightIndex; ++i)
		{
			newHeight = pos.second - std::sqrt(radius * radius - (i * 10 - pos.first) * (i * 10 - pos.first));
			newHeight = std::min(newHeight, GetSceneHeight(i));
			SetSceneHeight(i, newHeight);
		}
	}
}


/*
	Helper functions
*/

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

	for (GLuint i = 0; i <= data->stripeCount; ++i)
	{
		GLfloat height = (*data->stripes[i].GetHeightPoints())[index];
		GLfloat base = (*data->stripes[i].GetBasePoints())[index];

		if (height - base > epsilon)
		{
			return height;
		}
	}

	return 0;
}


void hw1::Homework1::SetSceneHeight(GLuint index, GLfloat newVal)
{
	auto data = currentScene->GetSceneData();

	for (GLuint i = 0; i <= data->stripeCount; ++i)
	{
		GLfloat height = (*data->stripes[i].GetHeightPoints())[index];
		GLfloat base = (*data->stripes[i].GetBasePoints())[index];

		if (height - base > epsilon && data->stripes[i].CanBeDeformed())
		{
			(*data->stripes[i].GetHeightPoints())[index] = std::max(newVal, base);
			return;
		}
	}
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
	if (name == "hills")
	{
		return &sceneList[scene::LevelType::GRASS_LEVEL];
	}

	if (name == "desert")
	{
		return &sceneList[scene::LevelType::DESERT_LEVEL];
	}

	if (name == "tunnel")
	{
		return &sceneList[scene::LevelType::TUNNEL_LEVEL];
	}

	if (name == "layers")
	{
		return &sceneList[scene::LevelType::BASIC_LEVEL];
	}

	return &sceneList[scene::LevelType::GRASS_LEVEL];
}


// Returns true if two objects should collide
bool hw1::Homework1::CheckForCollision(
	FloatPair aCenter,
	FloatPair bCenter,
	GLfloat aRad,
	GLfloat bRad
)
{
	GLfloat dist = std::sqrt((aCenter.first - bCenter.first) * (aCenter.first - bCenter.first)
		+ (aCenter.second - bCenter.second) * (aCenter.second - bCenter.second));

	return (aRad + bRad - dist > epsilon);
}


bool hw1::Homework1::CheckForGround(
	FloatPair center,
	GLfloat radius,
	GLfloat height,
	GLfloat width
)
{
	GLfloat dist = std::sqrt((center.first - width) * (center.first - width)
		+ (center.second - height) * (center.second - height));

	return (radius - dist > epsilon);
}

