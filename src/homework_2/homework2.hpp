#pragma once


#include <vector>
#include <string>


#include "components/simple_scene.h"
#include "components/transform.h"


using namespace std;


namespace hw2
{
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

		void InitMeshLoad();
		void InitShaderLoad();

		Mesh* CreateMesh(vector<VertexFormat> vertices, vector<GLuint> indices, string name);
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, glm::mat4 modelMatrix, GLfloat fAux = 1.0f);

		GLenum polygon_mode;
	};
}


