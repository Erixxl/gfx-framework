#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <vector>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
	cx = 0.0f;
	cy = 0.0f;

	modelMatrix = glm::mat3(1);

	// Initialize tx and ty (the translation steps)
	translateX = 0.0f;
	translateY = 0.0f;

	// Initialize sx and sy (the scale factors)
	scaleX = 1.0f;
	scaleY = 1.0f;

	// Initialize angularStep
	angularStep = 0.0f;

	// Choice of animation
	choice = 0;

	// Translation limits
	lowerLimit = 0;
	upperLimit = 0;

	// Position used for animations
	xPos = 0;
	yPos = 0;

	step = 0;
	stage = 0;
	scaleSize = 1;
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	centerX = (float)resolution.x / 2;
	centerY = (float)resolution.y / 2;


	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// Square coordinates
	cx = 0.5f * (corner.x + squareSide);
	cy = 0.5f * (corner.y + squareSide);

	// Translation limits based on resolution
	lowerLimit = 1.0 * (float)resolution.y / 10;
	upperLimit = 9.0 * (float)resolution.y / 10;

	Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* triangle = new Mesh("triangle");

	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-100, -100, 0), glm::vec3(1, 0, 1)),
		VertexFormat(glm::vec3( 100, -100, 0), glm::vec3(1, 0, 1)),
		VertexFormat(glm::vec3(   0,  100, 0), glm::vec3(0, 0, 1))
	};

	vector<GLuint> indices = {
		0, 1, 2
	};

	triangle->SetDrawMode(GL_TRIANGLES);
	triangle->InitFromData(vertices, indices);

	AddMeshToList(triangle);
}


void Lab3::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
	glm::mat3 transformation;

	switch (choice)
	{
		// Idle - bonus
		case 0:
			for (int i = 0; i < 5; ++i)
			{
				transformation = transform2D::Translate(centerX, centerY)
					* transform2D::Rotate(i * AI_MATH_TWO_PI / 5)
					* transform2D::Translate(0, 237);


				RenderMesh2D(meshes["triangle"], shaders["VertexColor"], transformation);
			}

			break;

		// Translation
		case 1:
			yPos += deltaTimeSeconds * step;

			modelMatrix = transform2D::Translate(xPos, yPos);

			RenderMesh2D(meshes["square1"], shaders["VertexColor"],
				modelMatrix);


			if (yPos > upperLimit - 100) // squareSide
			{
				yPos = upperLimit - 100;
				step = -step;
			}

			if (yPos < lowerLimit)
			{
				yPos = lowerLimit;
				step = -step;
			}

			break;

		// Scaling
		case 2:
			switch (stage)
			{
				case 0:
					modelMatrix = transform2D::Translate(xPos, yPos)
						* transform2D::Scale(scaleSize, scaleSize);

					scaleSize += 2 * deltaTimeSeconds;
					if (scaleSize >= 5.0f)
					{
						scaleSize = 5.0f;
						stage = 1;
					}

					break;

				// square side = 100
				// max scale = 5

				// scale = 5 => colt ( xPos + 0, yPos + 0)
				// scale = 1 => colt ( xPos + 400, yPos + 400)
				case 1:
					modelMatrix = transform2D::Translate(xPos + 100 * (5 - scaleSize), yPos + 100 * (5 - scaleSize))
						* transform2D::Scale(scaleSize, scaleSize);

					scaleSize -= 2 * deltaTimeSeconds;
					if (scaleSize <= 1.0f)
					{
						scaleSize = 1.0f;
						stage = 2;
					}

					break;

				case 2:
					modelMatrix = transform2D::Translate(xPos + 100 * (5 - scaleSize), yPos + 100 * (5 - scaleSize))
						* transform2D::Scale(scaleSize, scaleSize);

					scaleSize += 2 * deltaTimeSeconds;
					if (scaleSize >= 5.0f)
					{
						scaleSize = 5.0f;
						stage = 3;
					}

					break;



				case 3:
					modelMatrix = transform2D::Translate(xPos, yPos)
						* transform2D::Scale(scaleSize, scaleSize);

					scaleSize -= 2 * deltaTimeSeconds;
					if (scaleSize <= 1.0f)
					{
						scaleSize = 1.0f;
						stage = 0;
					}

					break;


			}

			RenderMesh2D(meshes["square1"], shaders["VertexColor"],
				modelMatrix);

			break;

		// Rotation
		case 3:
			modelMatrix = glm::mat3(1);


			modelMatrix *= transform2D::RotateFrom(
				xPos, yPos,
				angularStep * AI_MATH_PI / 12
			);

			angularStep += deltaTimeSeconds * 5;

			modelMatrix *= transform2D::Translate(300, 300);

			RenderMesh2D(meshes["square1"], shaders["VertexColor"],
				modelMatrix);

			RenderMesh2D(
				meshes["square2"], shaders["VertexColor"],
				transform2D::Translate(xPos - cx, yPos - cy) * transform2D::RotateFrom(cx, cy, angularStep)
			);

			break;

		// Combined
		case 4:
			modelMatrix = glm::mat3(1);

			//modelMatrix *= transform2D::Shear(5, 7);
			modelMatrix *= transform2D::MirrorSlope(-1, 500);

			modelMatrix *= transform2D::ScaleFrom(-cx, -cy, 2, 1);

			//modelMatrix *= transform2D::Translate(200, 0);

			RenderMesh2D(meshes["square1"], shaders["VertexColor"], transform2D::ScaleFrom(-cx, -cy, 2, 1));
			RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

			break;

		default:
			break;
	}
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_C) {
		// Cycle through animations
		switch (choice)
		{
			// Update to translation
			case 0:
				xPos = 400;
				yPos = lowerLimit;

				modelMatrix = transform2D::Translate(xPos, yPos);

				step = 150;

				choice = 1;
				break;

			// Update to scaling
			case 1:
				xPos = 100;
				yPos = 100;

				stage = 0;
				scaleSize = 1.0f;

				modelMatrix = glm::mat3(1);

				choice = 2;
				break;

			// Update to rotation
			case 2:
				xPos = centerX - cx / 2;
				yPos = centerY - cy / 2;

				modelMatrix = glm::mat3(1);

				angularStep = 1.0f;

				choice = 3;
				break;

			default:
				modelMatrix = glm::mat3(1);

				xPos = 0;
				yPos = 0;

				choice = (choice + 1) % 5;
				break;
		}
	}
}


void Lab3::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
