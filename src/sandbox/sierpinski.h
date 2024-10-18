#pragma once


#include <vector>
#include <ctime>


#include "components/simple_scene.h"


namespace srpk
{
	class Sierpinski : public gfxc::SimpleScene
	{
	public:
		Sierpinski();
		~Sierpinski();

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

		float getDistFraction(glm::vec3 point, glm::vec3 origin);
		void drawWhiteTriangles(glm::vec3 up, glm::vec3 left, glm::vec3 right);
		void generatePoints(glm::vec3 up, glm::vec3 left, glm::vec3 right,
			std::vector<VertexFormat>& vertices, int level);

		void printManual();

		int frameCounter;

		int cornerCount;
		std::vector<glm::vec3> cornerList;
		std::vector<glm::vec3> cornerColors;

		int pointCount;
		glm::vec3 startingPoint;
		float distRatio;

		int invert;
		bool renderOutline;
		bool renderPoints;

		float windowMiddleX;
		float windowMiddleY;

		bool enableTooltip;
		int translationStep;
		float rotationStep;
		float scalingStep;
		float currAngle;
		float currScale;
		glm::mat3 matrix;
	};
}

