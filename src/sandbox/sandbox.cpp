#include "sandbox.h"

#include <vector>
#include <cmath>

#include "core/engine.h"
#include "utils/gl_utils.h"


sb::Sandbox::Sandbox()
{
}


sb::Sandbox::~Sandbox()
{
}


void sb::Sandbox::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
}


void sb::Sandbox::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}


void sb::Sandbox::Update(float deltaTimeSeconds)
{
}


void sb::Sandbox::FrameEnd()
{
}


void sb::Sandbox::OnInputUpdate(float deltaTime, int mod)
{
}


void sb::Sandbox::OnKeyPress(int key, int mods)
{
}


void sb::Sandbox::OnKeyRelease(int key, int mods)
{
}


void sb::Sandbox::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void sb::Sandbox::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void sb::Sandbox::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void sb::Sandbox::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void sb::Sandbox::OnWindowResize(int width, int height)
{
}
