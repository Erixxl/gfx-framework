#include "sierpinski.h"

#include <vector>
#include <cmath>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "sandbox/transform2D.h"

namespace tf2d = transform2D;

srpk::Sierpinski::Sierpinski()
{
	// Initialize variables here
	startingPoint = glm::vec3(0, -126.795, 0);
	distRatio = 0.5f;

	invert = 1;
	renderOutline = false;
	renderPoints = true;

	cornerCount = 3;
	cornerList = {
		glm::vec3(-300, -300, 0),
		glm::vec3(300, -300, 0),
		glm::vec3(0, 219.615, 0)
	};
	cornerColors = {
		glm::vec3(1 - invert, invert, invert),
		glm::vec3(invert, 1 - invert, invert),
		glm::vec3(invert, invert, 1 - invert)
	};

	windowMiddleX = 0;
	windowMiddleY = 0;

	pointCount = 1000000;
	frameCounter = 0;

	enableTooltip = true;
	translationStep = 100;
	scalingStep = 0.2;
	rotationStep = AI_MATH_PI / 12;
	currAngle = 0;
	currScale = 1;
	matrix = glm::mat3(1);
}


srpk::Sierpinski::~Sierpinski()
{
}


void srpk::Sierpinski::Init()
{
	if (enableTooltip)
	{
		printManual();
	}


	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Screen center
	windowMiddleX = (float)resolution.x / 2;
	windowMiddleY = (float)resolution.y / 2;

	// Chaos game initialization
	srand((unsigned)time(NULL));
	glm::vec3 generator = startingPoint;

	// Generate mesh for corners
	Mesh* corners = new Mesh("corners");
	std::vector<VertexFormat> cornerVertices;
	std::vector<unsigned int> cornerIndices;

	for (int i = 0; i < cornerCount; ++i)
	{
		cornerList[i] += glm::vec3(windowMiddleX, windowMiddleY, 0);

		cornerVertices.push_back(
			VertexFormat(cornerList[i], cornerColors[i])
		);

		cornerIndices.push_back(i);
	}

	corners->SetDrawMode(GL_POINTS);
	corners->InitFromData(cornerVertices, cornerIndices);

	AddMeshToList(corners);

	drawWhiteTriangles(cornerList[0], cornerList[1], cornerList[2]);

	std::vector<VertexFormat> vertices = std::vector<VertexFormat>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();

	// Generate pointCount different meshes
	for (int i = 0; i < pointCount; ++i)
	{
		int randIndex = rand() % cornerCount;
		glm::vec3 point = distRatio * generator + (1 - distRatio) * cornerList[randIndex];
		glm::vec3 color( // This only works for Sierpinski Triangle
			getDistFraction(point, cornerList[0]),
			getDistFraction(point, cornerList[1]),
			getDistFraction(point, cornerList[2])
		);

		vertices.push_back(VertexFormat(point, color));
		indices.push_back(i % 10);

		if (i % 10 == 9)
		{
			Mesh* pointMesh = new Mesh("points" + std::to_string(i / 10));

			pointMesh->SetDrawMode(GL_POINTS);
			pointMesh->InitFromData(vertices, indices);

			AddMeshToList(pointMesh);

			vertices.clear();
			indices.clear();
		}

		generator = point;
	}
}


void srpk::Sierpinski::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}


void srpk::Sierpinski::Update(float deltaTimeSeconds)
{
	RenderMesh2D(meshes["corners"], shaders["VertexColor"], matrix);

	if (renderOutline)
	{
		RenderMesh2D(meshes["triangles"], shaders["VertexColor"], matrix);
	}

	if (!renderPoints)
	{
		return;
	}

	for (int i = 0; i < pointCount / 10 && i < ++frameCounter / 2; i += 10)
	{
		RenderMesh2D(
			meshes["points" + std::to_string(i / 10)],
			shaders["VertexColor"],
			matrix
		);
	}
}


void srpk::Sierpinski::FrameEnd()
{
}


void srpk::Sierpinski::OnInputUpdate(float deltaTime, int mod)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		matrix = tf2d::Translate(
			0,
			translationStep * deltaTime
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_A))
	{
		matrix = tf2d::Translate(
			-translationStep * deltaTime,
			0
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		matrix = tf2d::Translate(
			0,
			-translationStep * deltaTime
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_D))
	{
		matrix = tf2d::Translate(
			translationStep * deltaTime,
			0
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_G))
	{
		matrix = tf2d::ScaleFrom(
			windowMiddleX,
			windowMiddleY,
			scalingStep /* * deltaTime */,
			scalingStep /* * deltaTime */
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_H))
	{
		matrix = tf2d::ScaleFrom(
			windowMiddleX,
			windowMiddleY,
			1.0 / (scalingStep /* * deltaTime */ ),
			1.0 / (scalingStep /* * deltaTime */ )
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_J))
	{
		matrix = tf2d::RotateFrom(
			windowMiddleX,
			windowMiddleY,
			rotationStep * deltaTime
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_K))
	{
		matrix = tf2d::RotateFrom(
			windowMiddleX,
			windowMiddleY,
			-rotationStep * deltaTime
		) * matrix;
	}

	if (window->KeyHold(GLFW_KEY_LEFT_CONTROL))
	{
		matrix = glm::mat3(1);
	}
}


void srpk::Sierpinski::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C)
	{
		renderOutline = !renderOutline;
	}

	if (key == GLFW_KEY_V)
	{
		renderPoints = !renderPoints;
	}
}


void srpk::Sierpinski::OnKeyRelease(int key, int mods)
{
}


void srpk::Sierpinski::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void srpk::Sierpinski::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void srpk::Sierpinski::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void srpk::Sierpinski::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void srpk::Sierpinski::OnWindowResize(int width, int height)
{
}


float srpk::Sierpinski::getDistFraction(glm::vec3 point, glm::vec3 origin)
{
	float distX = (point.x - origin.x) * (point.x - origin.x);
	float distY = (point.y - origin.y) * (point.y - origin.y);

	return sqrt(distX + distY) / 600;
}


void srpk::Sierpinski::generatePoints(glm::vec3 up, glm::vec3 left, glm::vec3 right,
	std::vector<VertexFormat>& vertices, int level)
{
	if (level == 0)
	{
		return;
	}

	glm::vec3 a = 0.5f * up + 0.5f * left;
	glm::vec3 b = 0.5f * up + 0.5f * right;
	glm::vec3 c = 0.5f * right + 0.5f * left;
	glm::vec3 color(1, 1, 1);

	vertices.push_back(VertexFormat(a, color));
	vertices.push_back(VertexFormat(b, color));
	vertices.push_back(VertexFormat(c, color));

	generatePoints(up, a, b, vertices, level - 1);
	generatePoints(a, left, c, vertices, level - 1);
	generatePoints(b, c, right, vertices, level - 1);
}


void srpk::Sierpinski::drawWhiteTriangles(glm::vec3 up, glm::vec3 left, glm::vec3 right)
{
	Mesh* triangles = new Mesh("triangles");
	glm::vec3 white(1, 1, 1);

	std::vector<VertexFormat> vertices = {
		// Outside triangle
		VertexFormat(up, white),
		VertexFormat(left, white),
		VertexFormat(right, white)
	};
	std::vector<unsigned int> indices = std::vector<unsigned int>();


	generatePoints(up, left, right, vertices, 7);

	for (int i = 0; i < 1094; ++i)
	{
		indices.push_back(3 * i);
		indices.push_back(3 * i + 1);
		indices.push_back(3 * i + 1);
		indices.push_back(3 * i + 2);
		indices.push_back(3 * i + 2);
		indices.push_back(3 * i);
	}

	triangles->SetDrawMode(GL_LINES);
	triangles->InitFromData(vertices, indices);

	AddMeshToList(triangles);
}


void srpk::Sierpinski::printManual()
{
	std::cout << "\n\nCOMMANDS:\n"

		<< "[C]: Show white outlines     (default: OFF)\n"
		<< "[V]: Show points             (default: ON)\n\n"

		<< "[W]: Move image up           (increment: " << translationStep << " px)\n"
		<< "[A]: Move image left         (increment: " << translationStep << " px)\n"
		<< "[S]: Move image down         (increment: " << translationStep << " px)\n"
		<< "[D]: Move image right        (increment: " << translationStep << " px)\n\n"

		<< "[G]: Scale image up          (increment: " << scalingStep << ")\n"
		<< "[H]: Scale image down        (increment: " << scalingStep << ")\n\n"

		<< "[J]: Rotate image left       (increment: " << rotationStep << " rad)\n"
		<< "[K]: Rotate image right      (increment: " << rotationStep << " rad)\n\n"

		<< "[L_CTRL]: Reset\n\n";
}

