#include <ctime>
#include <iostream>

#include "core/engine.h"
#include "components/simple_scene.h"

#if defined(WITH_LAB_M1)
#   include "lab_m1/lab_list.h"
#endif

#if defined(WITH_LAB_M2)
#   include "lab_m2/lab_list.h"
#endif

#if defined(WITH_LAB_EXTRA)
#   include "lab_extra/lab_list.h"
#endif

#ifdef _WIN32
	PREFER_DISCRETE_GPU_NVIDIA;
	PREFER_DISCRETE_GPU_AMD;
#endif


#include "sandbox/sierpinski.h"
#include "homework_2/homework2.hpp"


std::string GetParentDir(const std::string &filePath)
{
	size_t pos = filePath.find_last_of("\\/");
	return (std::string::npos == pos) ? "." : filePath.substr(0, pos);
}


int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	// Create a window property structure
	WindowProperties wp;
	wp.resolution = glm::ivec2(1280, 720);
	wp.vSync = true;
	wp.selfDir = GetParentDir(std::string(argv[0]));

	// Init the Engine and create a new window with the defined properties
	(void)Engine::Init(wp);

	// Create a new 3D world and start running it
	// World *world = new m1::Lab6();
	// World *world = new m1::Lab7();
	// World *world = new m1::Lab8();
	// World *world = new m1::Lab3_Vis2D();

	World* world = new hw2::Homework2();

	world->Init();
	world->Run();

	// Signals to the Engine to release the OpenGL context
	Engine::Exit();

	return 0;
}
