#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // Class variables initialized here
    redVal = 0;
    greenVal = 0;
    blueVal = 0;
    alphaVal = 0;

    meshCycle = "oil";
    meshScaling = 1.0f;
    colorMode = 0;

    moveTarget = 0;
    speed = 2.0f;
    interval = 0.01f;

	smallX = 2.0f;
	smallY = 0.5f;
	smallZ = 0.0f;

	bigX = -2.0f;
	bigY = 0.5f;
	bigZ = 0.0f;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("oil");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "oildrum.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("wall");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "concrete_wall.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("bunny");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer
    glClearColor(redVal, greenVal, blueVal, alphaVal);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render objects
    RenderMesh(meshes["box"], glm::vec3(smallX, smallY, smallZ), glm::vec3(0.5f));

    RenderMesh(meshes["box"], glm::vec3(bigX, bigY, bigZ));

    RenderMesh(meshes[meshCycle], glm::vec3(0, 0.5f, -4), glm::vec3(meshScaling));

    if (CheckCollisionInterval(smallX, smallY, smallZ, bigX, bigY, bigZ, interval)) {
        moveTarget = 1;
    }
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // Move ahead - negative Z
    if (window->KeyHold(GLFW_KEY_W)) {
        if (moveTarget) {
            bigZ -= deltaTime * speed;
        }

        else {
            smallZ -= deltaTime * speed;
        }
    }

    // Move left - negative X
    if (window->KeyHold(GLFW_KEY_A)) {
        if (moveTarget) {
            bigX -= deltaTime * speed;
        }

        else {
            smallX -= deltaTime * speed;
        }
    }

    // Move right - positive X
    if (window->KeyHold(GLFW_KEY_D)) {
        if (moveTarget) {
            bigX += deltaTime * speed;
        }

        else {
            smallX += deltaTime * speed;
        }
    }

    // Move behind - postivie Z
    if (window->KeyHold(GLFW_KEY_S)) {
        if (moveTarget) {
            bigZ += deltaTime * speed;
        }

        else {
            smallZ += deltaTime * speed;
        }
    }

    // Move down - negative Y
    if (window->KeyHold(GLFW_KEY_E)) {
        if (moveTarget) {
            bigY -= deltaTime * speed;
        }

        else {
            smallY -= deltaTime * speed;
        }
    }

    // Move up - positive Y
    if (window->KeyHold(GLFW_KEY_Q)) {
        if (moveTarget) {
            bigY += deltaTime * speed;
        }

        else {
            smallY += deltaTime * speed;
        }
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event

    if (key == GLFW_KEY_J) {
        CycleColorMode();
    }

    if (key == GLFW_KEY_K) {
        CycleObjectMesh();
    }

    if (key == GLFW_KEY_L) {
        CycleMovementSpeed();
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}


bool Lab1::CheckCollisionInterval(float firstX, float firstY, float firstZ,
    float secondX, float secondY, float secondZ, float interval)
{
    float distX = abs(firstX - secondX);
    float distY = abs(firstY - secondY);
    float distZ = abs(firstZ - secondZ);

    if (distX > interval || distY > interval || distZ > interval) {
        return false;
    }

    return true;
}


void Lab1::CycleColorMode()
{
    switch (colorMode)
	{
		case 0:
			redVal = 63;
			greenVal = 0;
			blueVal = 0;
			alphaVal = 1;

			colorMode = 1;
			break;

		case 1:
			redVal = 0;
			greenVal = 63;
			blueVal = 0;
			alphaVal = 1;

			colorMode = 2;
			break;

		case 2:
			redVal = 0;
			greenVal = 0;
			blueVal = 63;
			alphaVal = 1;

			colorMode = 3;
			break;

		case 3:
			redVal = 0;
			greenVal = 0;
			blueVal = 0;
			alphaVal = 1;

			colorMode = 0;
			break;

		default:
			colorMode = 0;
			break;
	}
}


void Lab1::CycleObjectMesh()
{
    if (meshCycle == "oil") {
		meshCycle = "bunny";
		meshScaling = 0.1f;
	}

	else if (meshCycle == "bunny") {
		meshCycle = "wall";
		meshScaling = 0.1f;
	}

	else {
		meshCycle = "oil";
		meshScaling = 1.0f;
	}
}


void Lab1::CycleMovementSpeed()
{
    if (speed == 2.0f) {
        speed = 1.0f;
	}

	else {
		speed = 2.0f;
	}
}
