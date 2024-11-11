#pragma once


#include <iostream>
#include <vector>
#include <map>
#include <string>


#include "components/simple_scene.h"


#include "homework_1/scene/scene.h"
#include "homework_1/utils/transform2D.h"


namespace hw1
{
	// If x - y <= epsilon, then x == y
	static GLfloat epsilon = 0.01f;

	class Homework1 : public gfxc::SimpleScene
	{
	public:
		Homework1();
		~Homework1();

		void Init() override;

	private:
		// Frame rendering functions
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		// Input functions
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// Setup functions
		void SceneListSetup();
		void MaterialListSetup();
		void MeshSetup();
		void ActorSetup();

		// Helper functions
		void RenderScene();
		void RenderLayerSlice(GLuint layerNumber, GLuint k);
		void RenderLayer(GLuint layerNumber);

		// Variables
		std::vector<scene::Material> materialList; // A vector that holds all available materials
		std::map<scene::LevelType, scene::Scene> sceneList; // A map between level types and their corresponding scenes
		scene::Scene *currentScene; // The scene that is loaded and rendered
	};
}


