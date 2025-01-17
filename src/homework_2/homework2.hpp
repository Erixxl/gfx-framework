#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <random>


#include "components/simple_scene.h"
#include "components/transform.h"


#include "homework_2/meshes/meshes.hpp"
#include "homework_2/shaders/shaders.hpp"
#include "homework_2/utils/utils.hpp"


using namespace std;


namespace hw2
{
	static const glm::vec3 gravity = glm::vec3(0, -5, 0);


	class Homework2 : public gfxc::SimpleScene
	{
	public:
		Homework2();
		~Homework2();


		void Init() override;


	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;


		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;


		void RenderSimpleMesh(Mesh* mesh, Shader* shader, glm::mat4 modelMatrix, GLfloat fAux = 1.0f, glm::vec3 vecAux = glm::vec3(0));


		bool debug;
		bool enable_boxes;
		random_device rand_val;


		hw2_utils::Camera* drone_camera;
		hw2_utils::Camera* scene_camera;


		GLenum polygon_mode;
		GLfloat blade_speed;
		GLfloat blade_angle;
		glm::mat4 drone_matrix;
		glm::vec3 drone_position;
		glm::vec3 drone_velocity;
		glm::vec3 drone_acceleration;
		GLfloat drone_angle;
	};
}


