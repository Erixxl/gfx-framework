#include "WindowObject.h"

#include <iostream>
#include <include/gl.h>
#include <include/utils.h>

#include "../Engine.h"
#include "WindowCallbacks.h"
#include "InputController.h"

#include <include/gl.h>

using namespace std;

WindowProperties::WindowProperties()
{
	name = "WindowName";
	resolution = glm::ivec2(1280, 720);
	aspectRatio = 1280.0f / 720.0f;
	cursorPos = resolution / 2;
	position = glm::ivec2(0);
	resizable = true;
	centered = true;
	fullScreen = false;
	visible = true;
	hideOnClose = false;
	vSync = true;
}

WindowObject::WindowObject(WindowProperties properties)
	: props(properties)
{
	window = nullptr;

	resizeEvent = false;
	scrollEvent = false;
	mouseMoveEvent = false;

	frameID = 0;
	deltaFrameTime = 0;
	props.aspectRatio = float(props.resolution.x) / props.resolution.y;

	// Set context version
	glfwWindowHint(GLFW_VISIBLE, props.visible);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Init OpenGL Window
	props.fullScreen ? FullScreen() : WindowMode();

	SetVSync(props.vSync);

	CheckOpenGLError();

	// Set default state
	mouseButtonAction = 0;
	mouseButtonStates = 0;
	registeredKeyEvents = 0;
	memset(keyStates, 0, 384);
	memset(keyScanCode, 0, 512);

	SetWindowCallbacks();
}

WindowObject::~WindowObject()
{
	glfwDestroyWindow(window);
}

void WindowObject::Show()
{
	props.visible = true;
	glfwShowWindow(window);
	MakeCurrentContext();
}

void WindowObject::Hide()
{
	props.visible = false;
	glfwHideWindow(window);
}

void WindowObject::SetVSync(bool state)
{
	props.vSync = state;
	glfwSwapInterval(state);
}

bool WindowObject::ToggleVSync()
{
	SetVSync(!props.vSync);
	return props.vSync;
}

void WindowObject::Close()
{
	props.hideOnClose ? Hide() : glfwSetWindowShouldClose(window, 1);
}

int WindowObject::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

void WindowObject::ShowPointer()
{
	hiddenPointer = false;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void WindowObject::HidePointer()
{
	hiddenPointer = true;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void WindowObject::DisablePointer()
{
	hiddenPointer = true;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowObject::SetWindowPosition(glm::ivec2 position)
{
	props.position = position;
	glfwSetWindowPos(window, position.x, position.y);
}

void WindowObject::CenterWindow()
{
	props.centered = true;

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *videoDisplay = glfwGetVideoMode(monitor);
	auto screenSize = glm::ivec2(videoDisplay->width, videoDisplay->height);

	SetWindowPosition((screenSize - props.resolution) / 2);
}

void WindowObject::CenterPointer()
{
	props.cursorPos.x = props.resolution.x / 2;
	props.cursorPos.y = props.resolution.y / 2;
	glfwSetCursorPos(window, props.cursorPos.x, props.cursorPos.y);
}

void WindowObject::SetPointerPosition(int mousePosX, int mousePosY)
{
	props.cursorPos.x = mousePosX;
	props.cursorPos.y = mousePosY;
	glfwSetCursorPos(window, mousePosX, mousePosY);
}

void WindowObject::PollEvents() const
{
	glfwPollEvents();
}

void WindowObject::ComputeFrameTime()
{
	frameID++;
	double currentTime = Engine::GetElapsedTime();
	deltaFrameTime = currentTime - elapsedTime;
	elapsedTime = currentTime;
}

void WindowObject::FullScreen()
{
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *videoDisplay = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(videoDisplay->width, videoDisplay->height, props.name.c_str(), monitor, NULL);
	assert(window != nullptr);

	glfwMakeContextCurrent(window);
	SetSize(videoDisplay->width, videoDisplay->height);
	resizeEvent = false;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void WindowObject::WindowMode()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) { fprintf(stderr, "Failed to initialize GLFW\n"); } 
	window = glfwCreateWindow(props.resolution.x, props.resolution.y, props.name.c_str(), NULL, NULL);
	assert(window != nullptr);
	glfwMakeContextCurrent(window);

	// Centers the window on the primary display
	if (props.centered) {
		CenterWindow();
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode *videoDisplay = glfwGetVideoMode(monitor);
		auto screenSize = glm::ivec2(videoDisplay->width, videoDisplay->height);
		props.position = (screenSize - props.resolution) / 2;
	}

	SetSize(props.resolution.x, props.resolution.y);
	resizeEvent = false;
}

void WindowObject::SubscribeToEvents(InputController * IC)
{
	observers.push_back(IC);
}

void WindowObject::UnsubscribeFromEvents(InputController * IC)
{
	observers.remove(IC);
}

void WindowObject::SetWindowCallbacks()
{
	glfwSetWindowCloseCallback(window, WindowCallbacks::OnClose);
	glfwSetWindowSizeCallback(window, WindowCallbacks::OnResize);
	glfwSetKeyCallback(window, WindowCallbacks::KeyCallback);
	glfwSetMouseButtonCallback(window, WindowCallbacks::MouseClick);
	glfwSetCursorPosCallback(window, WindowCallbacks::CursorMove);
	glfwSetScrollCallback(window, WindowCallbacks::MouseScroll);
}

GLFWwindow * WindowObject::GetGLFWWindow() const
{
	return window;
}

bool WindowObject::KeyHold(int keyCode) const
{
	return keyStates[keyCode];
}

bool WindowObject::MouseHold(int button) const
{
	return IS_BIT_SET(mouseButtonStates, button);
}

int WindowObject::GetSpecialKeyState() const
{
	return keyMods;
}

glm::ivec2 WindowObject::GetCursorPosition() const
{
	return props.cursorPos;
}

void WindowObject::KeyCallback(int key, int scanCode, int action, int mods)
{
	keyMods = mods;
	if (keyStates[key] == (action ? true : false))
		return;
	keyStates[key] = action ? true : false;
	keyEvents[registeredKeyEvents] = key;
	registeredKeyEvents++;
}

void WindowObject::MouseButtonCallback(int button, int action, int mods)
{
	// Only button events and mods are kept
	// Mouse position is the current frame position
	keyMods = mods;
	SET_BIT(mouseButtonAction, button);
	action ? SET_BIT(mouseButtonStates, button) : CLEAR_BIT(mouseButtonStates, button);
}

void WindowObject::MouseMove(int posX, int posY)
{
	// Save information for processing later on the Update thread
	if (mouseMoveEvent) {
		mouseDeltaX += posX - props.cursorPos.x;
		mouseDeltaY += posY - props.cursorPos.y;
	}
	else {
		mouseMoveEvent = true;
		mouseDeltaX = posX - props.cursorPos.x;
		mouseDeltaY = posY - props.cursorPos.y;
	}
	props.cursorPos = glm::ivec2(posX, posY);
}

void WindowObject::MouseScroll(double offsetX, double offsetY)
{
	mouseScrollDeltaX = (int)offsetX;
	mouseScrollDeltaY = (int)offsetY;
}

void WindowObject::UpdateObservers()
{
	ComputeFrameTime();

	// Signal window resize
	if (resizeEvent)
	{
		resizeEvent = false;
		for (auto obs : observers) {
			obs->OnWindowResize(props.resolution.x, props.resolution.y);
		}
	}

	// Signal mouse move event
	if (mouseMoveEvent)
	{
		mouseMoveEvent = false;
		for (auto obs : observers) {
			obs->OnMouseMove(props.cursorPos.x, props.cursorPos.y, mouseDeltaX, mouseDeltaY);
		}
	}

	// Signal mouse button press event
	auto pressEvent = mouseButtonAction & mouseButtonStates;
	if (pressEvent)
	{
		for (auto obs : observers) {
			obs->OnMouseBtnPress(props.cursorPos.x, props.cursorPos.y, pressEvent, keyMods);
		}
	}

	// Signal mouse button release event
	auto releaseEvent = mouseButtonAction & (~mouseButtonStates);
	if (releaseEvent)
	{
		for (auto obs : observers) {
			obs->OnMouseBtnRelease(props.cursorPos.x, props.cursorPos.y, releaseEvent, keyMods);
		}
	}

	// Signal mouse scroll event
	if (scrollEvent) {
		scrollEvent = false;
		for (auto obs : observers) {
			obs->OnMouseScroll(props.cursorPos.x, props.cursorPos.y, mouseScrollDeltaX, mouseScrollDeltaY);
		}
	}

	// Signal key events
	if (registeredKeyEvents)
	{
		for (int i = 0; i < registeredKeyEvents; i++) {
			for (auto obs : observers)
				keyStates[keyEvents[i]] ? obs->OnKeyPress(keyEvents[i], keyMods) : obs->OnKeyRelease(keyEvents[i], keyMods);
		}
		registeredKeyEvents = 0;
	}

	// Continuous events
	for (auto obs : observers) {
			obs->OnInputUpdate(static_cast<float>(deltaFrameTime), keyMods);
	}

	mouseButtonAction = 0;
}

void WindowObject::MakeCurrentContext() const
{
	glfwMakeContextCurrent(window);
	CheckOpenGLError();
}

void WindowObject::SetSize(int width, int height)
{
	glfwSetWindowSize(window, width, height);
	glViewport(0, 0, width, height);

	props.resolution = glm::ivec2(width, height);
	props.aspectRatio = float(width) / height;
	resizeEvent = true;
}

glm::ivec2 WindowObject::GetResolution() const
{
	return props.resolution;
}

void WindowObject::SwapBuffers() const
{
	glfwSwapBuffers(window);
	CheckOpenGLError();
}
