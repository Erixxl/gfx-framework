#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// Initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// Initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;

	// Initialize angular steps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	// Sets the resolution of the small viewport
	glm::ivec2 resolution = window->GetResolution();
	miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

	viewportScale = 1.1f;
	stopAnimation = false;
	counter = 40;
	dist = 20;

	// Colored Dodecahedron
	{
		GLfloat phi = 1.618f;

		vector<glm::vec3> colors = {
			glm::vec3(1.00f, 1.00f, 0.00f),
			glm::vec3(1.00f, 0.00f, 1.00f),
			glm::vec3(0.00f, 1.00f, 1.00f),
			glm::vec3(1.00f, 0.00f, 0.00f),
			glm::vec3(0.00f, 1.00f, 0.00f),
			glm::vec3(0.00f, 0.00f, 1.00f),
			glm::vec3(1.00f, 0.50f, 0.00f),
			glm::vec3(0.00f, 1.00f, 0.50f),
			glm::vec3(0.50f, 0.00f, 1.00f),
			glm::vec3(1.00f, 0.00f, 0.50f),
			glm::vec3(0.50f, 1.00f, 0.00f),
			glm::vec3(0.00f, 0.50f, 1.00f)
		};

		vector<VertexFormat> vertices = {
			// Face 1:
			VertexFormat( glm::vec3(1, 1, 1),            colors[0]), // A = 0
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[0]), // I = 8
			VertexFormat( glm::vec3(-1, 1, 1),           colors[0]), // B = 1
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[0]), // N = 13
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[0]), // M = 12

			// Face 2:
			VertexFormat( glm::vec3(-1, 1, 1),           colors[1]), // B = 1
			VertexFormat( glm::vec3(-phi, 1 / phi, 0),   colors[1]), // R = 17
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[1]), // T = 19
			VertexFormat( glm::vec3(-1, -1, 1),          colors[1]), // D = 3
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[1]), // N = 13

			// Face 3:
			VertexFormat( glm::vec3(-1, -1, 1),          colors[2]), // D = 3
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[2]), // J = 9
			VertexFormat( glm::vec3(1, -1, 1),           colors[2]), // C = 2
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[2]), // M = 12
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[2]), // N = 13

			// Face 4:
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[3]), // S = 18
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[3]), // Q = 16
			VertexFormat( glm::vec3(1, 1, 1),            colors[3]), // A = 0
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[3]), // M = 12
			VertexFormat( glm::vec3(1, -1, 1),           colors[3]), // C = 2

			// Face 5:
			VertexFormat( glm::vec3(1, 1, -1),           colors[4]), // E = 4
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[4]), // K = 10
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[4]), // I = 8
			VertexFormat( glm::vec3(1, 1, 1),            colors[4]), // A = 0
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[4]), // Q = 16

			// Face 6:
			VertexFormat( glm::vec3(-1, 1, -1),          colors[5]), // F = 5
			VertexFormat(glm::vec3(-phi, 1 / phi, 0),    colors[5]), // R = 17
			VertexFormat( glm::vec3(-1, 1, 1),           colors[5]), // B = 1
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[5]), // I = 8
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[5]), // K = 10

			// Face 7:
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[6]), // P = 15
			VertexFormat( glm::vec3(-1, -1, -1),         colors[6]), // H = 7
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[6]), // T = 19
			VertexFormat( glm::vec3(-phi, 1 / phi, 0),   colors[6]), // R = 17
			VertexFormat( glm::vec3(-1, 1, -1),          colors[6]), // F = 5

			// Face 8:
			VertexFormat( glm::vec3(-1, -1, -1),         colors[7]), // H = 7
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[7]), // L = 11
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[7]), // J = 9
			VertexFormat( glm::vec3(-1, -1, 1),          colors[7]), // D = 3
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[7]), // T = 19

			// Face 9:
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[8]), // L = 11
			VertexFormat( glm::vec3(1, -1, -1),          colors[8]), // G = 6
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[8]), // S = 18
			VertexFormat( glm::vec3(1, -1, 1),           colors[8]), // C = 2
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[8]), // J = 9

			// Face 10:
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[9]), // S = 18
			VertexFormat( glm::vec3(1, -1, -1),          colors[9]), // G = 6
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[9]), // O = 14
			VertexFormat( glm::vec3(1, 1, -1),           colors[9]), // E = 4
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[9]), // Q = 16

			// Face 11:
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[10]), // O = 14
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[10]), // P = 15
			VertexFormat( glm::vec3(-1, 1, -1),          colors[10]), // F = 5
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[10]), // K = 10
			VertexFormat( glm::vec3(1, 1, -1),           colors[10]), // E = 4

			// Face 12:
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[11]), // O = 14
			VertexFormat( glm::vec3(1, -1, -1),          colors[11]), // G = 6
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[11]), // L = 11
			VertexFormat( glm::vec3(-1, -1, -1),         colors[11]), // H = 7
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[11]), // P = 15
		};

		vector<GLuint> indices = {
			// Pentagon to triangles:
			// a b c d e => a b c, a c d, a d e

			// Face 1 - A I B N M
			0, 1, 2, 0, 2, 3, 0, 3, 4,

			// Face 2 - B R T D N
			5, 6, 7, 5, 7, 8, 5, 8, 9,

			// Face 3 - D J C M N
			10, 11, 12, 10, 12, 13, 10, 13, 14,

			// Face 4 - S Q A M C
			15, 16, 17, 15, 17, 18, 15, 18, 19,

			// Face 5 - E K I A Q
			20, 21, 22, 20, 22, 23, 20, 23, 24,

			// Face 6 - F R B I K
			25, 26, 27, 25, 27, 28, 25, 28, 29,

			// Face 7 - P H T R F
			30, 31, 32, 30, 32, 33, 30, 33, 34,

			// Face 8 - H L J D T
			35, 36, 37, 35, 37, 38, 35, 38, 39,

			// Face 9 - L G S C J
			40, 41, 42, 40, 42, 43, 40, 43, 44,

			// Face 10 - S G O E Q
			45, 46, 47, 45, 47, 48, 45, 48, 49,

			// Face 11 - O P F K E
			50, 51, 52, 50, 52, 53, 50, 53, 54,

			// Face 12 - O G L H P
			55, 56, 57, 55, 57, 58, 55, 58, 59
		};

		Mesh* dodeca = new Mesh("twelve");
		dodeca->InitFromData(vertices, indices);
		AddMeshToList(dodeca);
	}
}

void Lab4::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::RenderScene() {
	modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
	modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= transform3D::RotateOX(angularStepOX);
	modelMatrix *= transform3D::RotateOY(angularStepOY);
	modelMatrix *= transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::RenderBonus(float deltaTimeSeconds)
{
	modelMatrix = glm::mat4(1);

	dist = counter / 2;

	if (!stopAnimation)
	{
		modelMatrix *= transform3D::Translate(
			dist * cos(counter),
			0.5 * counter,
			dist * sin(counter)
		);

		counter -= 2 * deltaTimeSeconds;

		if (counter < 0) counter = 0;

		if (counter == 0)
			stopAnimation = true;
	}

	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	RenderBonus(deltaTimeSeconds);
	DrawCoordinateSystem();

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

	// TODO(student): render the scene again, in the new viewport
	DrawCoordinateSystem();
	RenderScene();
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
	// Movement
	if (window->KeyHold(GLFW_KEY_W))
	{
		translateZ -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		translateZ += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_A))
	{
		translateX -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_D))
	{
		translateX += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_F))
	{
		translateY -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_R))
	{
		translateY += deltaTime;
	}

	// Scaling
	if (window->KeyHold(GLFW_KEY_1))
	{
		scaleX += 0.5 * deltaTime;
		scaleY += 0.5 * deltaTime;
		scaleZ += 0.5 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_2))
	{
		scaleX -= 0.5 * deltaTime;
		scaleY -= 0.5 * deltaTime;
		scaleZ -= 0.5 * deltaTime;
	}

	// Rotation
	if (window->KeyHold(GLFW_KEY_3))
	{
		angularStepOX += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_4))
	{
		angularStepOX -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_5))
	{
		angularStepOY += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_6))
	{
		angularStepOY -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_7))
	{
		angularStepOZ += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_8))
	{
		angularStepOZ -= deltaTime;
	}
}


void Lab4::OnKeyPress(int key, int mods)
{
	GLfloat vpHeightDif = miniViewportArea.height / 10.0;
	GLfloat vpWidthDif = miniViewportArea.width / 10.0;

	// Add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}

	if (key == GLFW_KEY_I)
	{
		miniViewportArea.y += 5;
	}

	if (key == GLFW_KEY_J)
	{
		miniViewportArea.x -= 5;
	}

	if (key == GLFW_KEY_K)
	{
		miniViewportArea.y -= 5;
	}

	if (key == GLFW_KEY_L)
	{
		miniViewportArea.x += 5;
	}

	if (key == GLFW_KEY_U)
	{
		miniViewportArea.height /= viewportScale;
		miniViewportArea.width /= viewportScale;

		miniViewportArea.x += vpWidthDif / 2;
		miniViewportArea.y += vpHeightDif / 2;
	}

	if (key == GLFW_KEY_O)
	{
		miniViewportArea.height *= viewportScale;
		miniViewportArea.width *= viewportScale;

		miniViewportArea.x -= vpWidthDif / 2;
		miniViewportArea.y -= vpHeightDif / 2;
	}
}


void Lab4::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
