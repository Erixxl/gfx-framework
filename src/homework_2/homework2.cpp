#include "homework_2/homework2.hpp"


using namespace std;
using namespace hw2;


Homework2::Homework2()
{

}


Homework2::~Homework2()
{

}


void Homework2::Init()
{
	// TODO: Setup some shit I dunno
	InitMeshLoad();
	InitShaderLoad();
}


void Homework2::FrameStart()
{
	glClearColor(0.529, 0.808, 0.922, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}


void Homework2::Update(float deltaTimeSeconds)
{
	RenderSimpleMesh(meshes["ground"], shaders["GroundShader"], glm::mat4(1));
	RenderSimpleMesh(meshes["default_drone"], shaders["VertexColor"], glm::translate(glm::mat4(1), glm::vec3(0, 10, 0)));
}


void Homework2::FrameEnd()
{

}


void Homework2::OnInputUpdate(float deltaTime, int mods)
{

}


void Homework2::OnKeyPress(int key, int mods)
{

}


void Homework2::OnKeyRelease(int key, int mods)
{

}


void Homework2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}


void Homework2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}


void Homework2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}


void Homework2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}


void Homework2::OnWindowResize(int width, int height)
{

}


void Homework2::InitMeshLoad()
{
	// Ground mesh
	{
		glm::vec3 green(0, 1, 0.5);

		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3(-50, 0, -50),  green),
			VertexFormat(glm::vec3(-40, 0, -50),  green),
			VertexFormat(glm::vec3(-30, 0, -50),  green),
			VertexFormat(glm::vec3(-20, 0, -50),  green),
			VertexFormat(glm::vec3(-10, 0, -50),  green),
			VertexFormat(glm::vec3(  0, 0, -50),  green),
			VertexFormat(glm::vec3( 10, 0, -50),  green),
			VertexFormat(glm::vec3( 20, 0, -50),  green),
			VertexFormat(glm::vec3( 30, 0, -50),  green),
			VertexFormat(glm::vec3( 40, 0, -50),  green),
			VertexFormat(glm::vec3( 50, 0, -50),  green),

			VertexFormat(glm::vec3(-50, 0, -40),  green),
			VertexFormat(glm::vec3(-40, 0, -40),  green),
			VertexFormat(glm::vec3(-30, 0, -40),  green),
			VertexFormat(glm::vec3(-20, 0, -40),  green),
			VertexFormat(glm::vec3(-10, 0, -40),  green),
			VertexFormat(glm::vec3(  0, 0, -40),  green),
			VertexFormat(glm::vec3( 10, 0, -40),  green),
			VertexFormat(glm::vec3( 20, 0, -40),  green),
			VertexFormat(glm::vec3( 30, 0, -40),  green),
			VertexFormat(glm::vec3( 40, 0, -40),  green),
			VertexFormat(glm::vec3( 50, 0, -40),  green),

			VertexFormat(glm::vec3(-50, 0, -30),  green),
			VertexFormat(glm::vec3(-40, 0, -30),  green),
			VertexFormat(glm::vec3(-30, 0, -30),  green),
			VertexFormat(glm::vec3(-20, 0, -30),  green),
			VertexFormat(glm::vec3(-10, 0, -30),  green),
			VertexFormat(glm::vec3(  0, 0, -30),  green),
			VertexFormat(glm::vec3( 10, 0, -30),  green),
			VertexFormat(glm::vec3( 20, 0, -30),  green),
			VertexFormat(glm::vec3( 30, 0, -30),  green),
			VertexFormat(glm::vec3( 40, 0, -30),  green),
			VertexFormat(glm::vec3( 50, 0, -30),  green),

			VertexFormat(glm::vec3(-50, 0, -20),  green),
			VertexFormat(glm::vec3(-40, 0, -20),  green),
			VertexFormat(glm::vec3(-30, 0, -20),  green),
			VertexFormat(glm::vec3(-20, 0, -20),  green),
			VertexFormat(glm::vec3(-10, 0, -20),  green),
			VertexFormat(glm::vec3(  0, 0, -20),  green),
			VertexFormat(glm::vec3( 10, 0, -20),  green),
			VertexFormat(glm::vec3( 20, 0, -20),  green),
			VertexFormat(glm::vec3( 30, 0, -20),  green),
			VertexFormat(glm::vec3( 40, 0, -20),  green),
			VertexFormat(glm::vec3( 50, 0, -20),  green),

			VertexFormat(glm::vec3(-50, 0, -10),  green),
			VertexFormat(glm::vec3(-40, 0, -10),  green),
			VertexFormat(glm::vec3(-30, 0, -10),  green),
			VertexFormat(glm::vec3(-20, 0, -10),  green),
			VertexFormat(glm::vec3(-10, 0, -10),  green),
			VertexFormat(glm::vec3(  0, 0, -10),  green),
			VertexFormat(glm::vec3( 10, 0, -10),  green),
			VertexFormat(glm::vec3( 20, 0, -10),  green),
			VertexFormat(glm::vec3( 30, 0, -10),  green),
			VertexFormat(glm::vec3( 40, 0, -10),  green),
			VertexFormat(glm::vec3( 50, 0, -10),  green),

			VertexFormat(glm::vec3(-50, 0,   0),  green),
			VertexFormat(glm::vec3(-40, 0,   0),  green),
			VertexFormat(glm::vec3(-30, 0,   0),  green),
			VertexFormat(glm::vec3(-20, 0,   0),  green),
			VertexFormat(glm::vec3(-10, 0,   0),  green),
			VertexFormat(glm::vec3(  0, 0,   0),  green),
			VertexFormat(glm::vec3( 10, 0,   0),  green),
			VertexFormat(glm::vec3( 20, 0,   0),  green),
			VertexFormat(glm::vec3( 30, 0,   0),  green),
			VertexFormat(glm::vec3( 40, 0,   0),  green),
			VertexFormat(glm::vec3( 50, 0,   0),  green),

			VertexFormat(glm::vec3(-50, 0,  10),  green),
			VertexFormat(glm::vec3(-40, 0,  10),  green),
			VertexFormat(glm::vec3(-30, 0,  10),  green),
			VertexFormat(glm::vec3(-20, 0,  10),  green),
			VertexFormat(glm::vec3(-10, 0,  10),  green),
			VertexFormat(glm::vec3(  0, 0,  10),  green),
			VertexFormat(glm::vec3( 10, 0,  10),  green),
			VertexFormat(glm::vec3( 20, 0,  10),  green),
			VertexFormat(glm::vec3( 30, 0,  10),  green),
			VertexFormat(glm::vec3( 40, 0,  10),  green),
			VertexFormat(glm::vec3( 50, 0,  10),  green),

			VertexFormat(glm::vec3(-50, 0,  20),  green),
			VertexFormat(glm::vec3(-40, 0,  20),  green),
			VertexFormat(glm::vec3(-30, 0,  20),  green),
			VertexFormat(glm::vec3(-20, 0,  20),  green),
			VertexFormat(glm::vec3(-10, 0,  20),  green),
			VertexFormat(glm::vec3(  0, 0,  20),  green),
			VertexFormat(glm::vec3( 10, 0,  20),  green),
			VertexFormat(glm::vec3( 20, 0,  20),  green),
			VertexFormat(glm::vec3( 30, 0,  20),  green),
			VertexFormat(glm::vec3( 40, 0,  20),  green),
			VertexFormat(glm::vec3( 50, 0,  20),  green),

			VertexFormat(glm::vec3(-50, 0,  30),  green),
			VertexFormat(glm::vec3(-40, 0,  30),  green),
			VertexFormat(glm::vec3(-30, 0,  30),  green),
			VertexFormat(glm::vec3(-20, 0,  30),  green),
			VertexFormat(glm::vec3(-10, 0,  30),  green),
			VertexFormat(glm::vec3(  0, 0,  30),  green),
			VertexFormat(glm::vec3( 10, 0,  30),  green),
			VertexFormat(glm::vec3( 20, 0,  30),  green),
			VertexFormat(glm::vec3( 30, 0,  30),  green),
			VertexFormat(glm::vec3( 40, 0,  30),  green),
			VertexFormat(glm::vec3( 50, 0,  30),  green),

			VertexFormat(glm::vec3(-50, 0,  40),  green),
			VertexFormat(glm::vec3(-40, 0,  40),  green),
			VertexFormat(glm::vec3(-30, 0,  40),  green),
			VertexFormat(glm::vec3(-20, 0,  40),  green),
			VertexFormat(glm::vec3(-10, 0,  40),  green),
			VertexFormat(glm::vec3(  0, 0,  40),  green),
			VertexFormat(glm::vec3( 10, 0,  40),  green),
			VertexFormat(glm::vec3( 20, 0,  40),  green),
			VertexFormat(glm::vec3( 30, 0,  40),  green),
			VertexFormat(glm::vec3( 40, 0,  40),  green),
			VertexFormat(glm::vec3( 50, 0,  40),  green),

			VertexFormat(glm::vec3(-50, 0,  50),  green),
			VertexFormat(glm::vec3(-40, 0,  50),  green),
			VertexFormat(glm::vec3(-30, 0,  50),  green),
			VertexFormat(glm::vec3(-20, 0,  50),  green),
			VertexFormat(glm::vec3(-10, 0,  50),  green),
			VertexFormat(glm::vec3(  0, 0,  50),  green),
			VertexFormat(glm::vec3( 10, 0,  50),  green),
			VertexFormat(glm::vec3( 20, 0,  50),  green),
			VertexFormat(glm::vec3( 30, 0,  50),  green),
			VertexFormat(glm::vec3( 40, 0,  50),  green),
			VertexFormat(glm::vec3( 50, 0,  50),  green)
		};

		vector<GLuint> indices = {
			  0,   1,  11,  11,   1,  12,
			  1,   2,  12,  12,   2,  13,
			  2,   3,  13,  13,   3,  14,
			  3,   4,  14,  14,   4,  15,
			  4,   5,  15,  15,   5,  16,
			  5,   6,  16,  16,   6,  17,
			  6,   7,  17,  17,   7,  18,
			  7,   8,  18,  18,   8,  19,
			  8,   9,  19,  19,   9,  20,
			  9,  10,  20,  20,  10,  21,

			 11,  12,  22,  22,  12,  23,
			 12,  13,  23,  23,  13,  24,
			 13,  14,  24,  24,  14,  25,
			 14,  15,  25,  25,  15,  26,
			 15, 16, 26, 26, 16, 27,
				 16, 17, 27, 27, 17, 28,
				 17, 18, 28, 28, 18, 29,
				 18, 19, 29, 29, 19, 30,
				 19, 20, 30, 30, 20, 31,
				 20, 21, 31, 31, 21, 32,

				 22, 23, 33, 33, 23, 34,
				 23, 24, 34, 34, 24, 35,
				 24, 25, 35, 35, 25, 36,
				 25, 26, 36, 36, 26, 37,
				 26, 27, 37, 37, 27, 38,
				 27, 28, 38, 38, 28, 39,
				 28, 29, 39, 39, 29, 40,
				 29, 30, 40, 40, 30, 41,
				 30, 31, 41, 41, 31, 42,
				 31, 32, 42, 42, 32, 43,

				 33, 34, 44, 44, 34, 45,
				 34, 35, 45, 45, 35, 46,
				 35, 36, 46, 46, 36, 47,
				 36, 37, 47, 47, 37, 48,
				 37, 38, 48, 48, 38, 49,
				 38, 39, 49, 49, 39, 50,
				 39, 40, 50, 50, 40, 51,
				 40, 41, 51, 51, 41, 52,
				 41, 42, 52, 52, 42, 53,
				 42, 43, 53, 53, 43, 54,

				 44, 45, 55, 55, 45, 56,
				 45, 46, 56, 56, 46, 57,
				 46, 47, 57, 57, 47, 58,
				 47, 48, 58, 58, 48, 59,
				 48, 49, 59, 59, 49, 60,
				 49, 50, 60, 60, 50, 61,
				 50, 51, 61, 61, 51, 62,
				 51, 52, 62, 62, 52, 63,
				 52, 53, 63, 63, 53, 64,
				 53, 54, 64, 64, 54, 65,

				 55, 56, 66, 66, 56, 67,
				 56, 57, 67, 67, 57, 68,
				 57, 58, 68, 68, 58, 69,
				 58, 59, 69, 69, 59, 70,
				 59, 60, 70, 70, 60, 71,
				 60, 61, 71, 71, 61, 72,
				 61, 62, 72, 72, 62, 73,
				 62, 63, 73, 73, 63, 74,
				 63, 64, 74, 74, 64, 75,
				 64, 65, 75, 75, 65, 76,

				 66, 67, 77, 77, 67, 78,
				 67, 68, 78, 78, 68, 79,
				 68, 69, 79, 79, 69, 80,
				 69, 70, 80, 80, 70, 81,
				 70, 71, 81, 81, 71, 82,
				 71, 72, 82, 82, 72, 83,
				 72, 73, 83, 83, 73, 84,
				 73, 74, 84, 84, 74, 85,
				 74, 75, 85, 85, 75, 86,
				 75, 76, 86, 86, 76, 87,

				 77, 78, 88, 88, 78, 89,
				 78, 79, 89, 89, 79, 90,
				 79, 80, 90, 90, 80, 91,
				 80, 81, 91, 91, 81, 92,
				 81, 82, 92, 92, 82, 93,
				 82, 83, 93, 93, 83, 94,
				 83, 84, 94, 94, 84, 95,
				 84, 85, 95, 95, 85, 96,
				 85, 86, 96, 96, 86, 97,
				 86, 87, 97, 97, 87, 98,

				 88, 89, 99, 99, 89, 100,
				 89, 90, 100, 100, 90, 101,
				 90, 91, 101, 101, 91, 102,
				 91, 92, 102, 102, 92, 103,
				 92, 93, 103, 103, 93, 104,
				 93, 94, 104, 104, 94, 105,
				 94, 95, 105, 105, 95, 106,
				 95, 96, 106, 106, 96, 107,
				 96, 97, 107, 107, 97, 108,
				 97, 98, 108, 108, 98, 109,

				 99, 100, 110, 110, 100, 111,
				 100, 101, 111, 111, 101, 112,
				 101, 102, 112, 112, 102, 113,
				 102, 103, 113, 113, 103, 114,
				 103, 104, 114, 114, 104, 115,
				 104, 105, 115, 115, 105, 116,
				 105, 106, 116, 116, 106, 117,
				 106, 107, 117, 117, 107, 118,
				 107, 108, 118, 118, 108, 119,
				 108, 109, 119, 119, 109, 120
		};

		CreateMesh(vertices, indices, "ground");
	}

	// Default drone mesh
	{
		// Warning: ugly af

		glm::vec3 gray = glm::vec3(0.8);
		glm::vec3 dark = glm::vec3(0.2);

		vector<VertexFormat> vertices = {
			// Upper region
			VertexFormat(glm::vec3(-0.50,  0.0,  3.50), gray),
			VertexFormat(glm::vec3(0.50,  0.0,  3.50), gray),
			VertexFormat(glm::vec3(-3.50,  0.0,  0.50), gray),
			VertexFormat(glm::vec3(-0.50,  0.0,  0.50), gray),
			VertexFormat(glm::vec3(0.50,  0.0,  0.50), gray),
			VertexFormat(glm::vec3(3.50,  0.0,  0.50), gray),
			VertexFormat(glm::vec3(-3.50,  0.0, -0.50), gray),
			VertexFormat(glm::vec3(-0.50,  0.0, -0.50), gray),
			VertexFormat(glm::vec3(0.50,  0.0, -0.50), gray),
			VertexFormat(glm::vec3(3.50,  0.0, -0.50), gray),
			VertexFormat(glm::vec3(-0.50,  0.0, -3.50), gray),
			VertexFormat(glm::vec3(0.50,  0.0, -3.50), gray),

			// Lower region
			VertexFormat(glm::vec3(-0.50, -0.2,  3.50), gray),
			VertexFormat(glm::vec3(0.50, -0.2,  3.50), gray),
			VertexFormat(glm::vec3(-3.50, -0.2,  0.50), gray),
			VertexFormat(glm::vec3(-0.50, -0.2,  0.50), gray),
			VertexFormat(glm::vec3(0.50, -0.2,  0.50), gray),
			VertexFormat(glm::vec3(3.50, -0.2,  0.50), gray),
			VertexFormat(glm::vec3(-3.50, -0.2, -0.50), gray),
			VertexFormat(glm::vec3(-0.50, -0.2, -0.50), gray),
			VertexFormat(glm::vec3(0.50, -0.2, -0.50), gray),
			VertexFormat(glm::vec3(3.50, -0.2, -0.50), gray),
			VertexFormat(glm::vec3(-0.50, -0.2, -3.50), gray),
			VertexFormat(glm::vec3(0.50, -0.2, -3.50), gray),

			// Upper spinning blade
			VertexFormat(glm::vec3(0.00,  0.3,  3.00), dark),
			VertexFormat(glm::vec3(-0.10,  0.0,  2.90), dark),
			VertexFormat(glm::vec3(-0.10,  0.0,  3.10), dark),
			VertexFormat(glm::vec3(0.10,  0.0,  3.10), dark),
			VertexFormat(glm::vec3(0.10,  0.0,  2.90), dark),
			VertexFormat(glm::vec3(0.00,  0.3,  4.00), dark),
			VertexFormat(glm::vec3(-0.15,  0.2,  3.25), dark),
			VertexFormat(glm::vec3(0.00,  0.3,  2.00), dark),
			VertexFormat(glm::vec3(0.15,  0.2,  2.75), dark),

			// Right spinning blade
			VertexFormat(glm::vec3(3.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(2.90,  0.0, -0.10), dark),
			VertexFormat(glm::vec3(2.90,  0.0,  0.10), dark),
			VertexFormat(glm::vec3(3.10,  0.0,  0.10), dark),
			VertexFormat(glm::vec3(3.10,  0.0, -0.10), dark),
			VertexFormat(glm::vec3(4.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(3.25,  0.1, -0.25), dark),
			VertexFormat(glm::vec3(2.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(2.75,  0.1,  0.25), dark),

			// Lower spinning blade
			VertexFormat(glm::vec3(0.00,  0.3, -3.00), dark),
			VertexFormat(glm::vec3(-0.10,  0.0, -3.10), dark),
			VertexFormat(glm::vec3(-0.10,  0.0, -2.90), dark),
			VertexFormat(glm::vec3(0.10,  0.0, -2.90), dark),
			VertexFormat(glm::vec3(0.10,  0.0, -3.10), dark),
			VertexFormat(glm::vec3(0.00,  0.3, -2.00), dark),
			VertexFormat(glm::vec3(-0.15,  0.2, -2.75), dark),
			VertexFormat(glm::vec3(0.00,  0.3, -4.00), dark),
			VertexFormat(glm::vec3(0.15,  0.2, -3.25), dark),

			// Left spinning blade
			VertexFormat(glm::vec3(-3.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(-3.10,  0.0, -0.10), dark),
			VertexFormat(glm::vec3(-3.10,  0.0,  0.10), dark),
			VertexFormat(glm::vec3(-2.90,  0.0,  0.10), dark),
			VertexFormat(glm::vec3(-2.90,  0.0, -0.10), dark),
			VertexFormat(glm::vec3(-2.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(-2.75,  0.1, -0.25), dark),
			VertexFormat(glm::vec3(-4.00,  0.3,  0.00), dark),
			VertexFormat(glm::vec3(-3.25,  0.1,  0.25), dark),
		};

		vector<GLuint> indices = {
			// Up body side
			0, 1, 4, 0, 4, 3,
			4, 5, 9, 4, 9, 8,
			8, 11, 10, 8, 10, 7,
			7, 6, 2, 7, 2, 3,
			3, 4, 8, 3, 8, 7,

			// Low body side
			12, 13, 16, 12, 16, 15,
			16, 17, 21, 16, 21, 20,
			20, 23, 22, 20, 22, 19,
			19, 18, 14, 19, 14, 15,
			15, 16, 20, 15, 20, 19,

			// Margins - upper arm
			0, 3, 15, 0, 15, 12,
			1, 0, 12, 1, 12, 13,
			4, 1, 13, 4, 13, 16,

			// Margins - right arm
			5, 4, 16, 5, 16, 17,
			9, 5, 17, 9, 17, 21,
			8, 9, 21, 8, 21, 20,

			// Margins - lower arm
			11, 8, 20, 11, 20, 23,
			10, 11, 23, 10, 23, 22,
			7, 10, 22, 7, 22, 19,

			// Margins - left arm
			6, 7, 19, 6, 19, 18,
			2, 6, 18, 2, 18, 14,
			3, 2, 14, 3, 14, 15,

			// Spinning blade - upper arm
			24, 25, 26, 24, 26, 27,
			24, 27, 28, 24, 28, 25,
			24, 29, 30, 24, 31, 32,

			// Spinning blade - right arm
			33, 34, 35, 33, 35, 36,
			33, 36, 37, 33, 37, 34,
			33, 38, 39, 33, 40, 41,

			// Spinning blade - lower arm
			42, 43, 44, 42, 44, 45,
			42, 45, 46, 42, 46, 43,
			42, 47, 48, 42, 49, 50,

			// Spinning blade - left arm
			51, 52, 53, 51, 53, 54,
			51, 54, 55, 51, 55, 52,
			51, 56, 57, 51, 58, 59
		};

		CreateMesh(vertices, indices, "default_drone");
	}
}


void Homework2::InitShaderLoad()
{
	// Ground shader
	{
		Shader* shader = new Shader("GroundShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "homework_2", "shaders", "ground.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "homework_2", "shaders", "ground.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}


Mesh* Homework2::CreateMesh(vector<VertexFormat> vertices, vector<GLuint> indices, string name)
{
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
	CheckOpenGLError();

	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<GLuint>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;

	return meshes[name];
}


void Homework2::RenderSimpleMesh(Mesh* mesh, Shader* shader, glm::mat4 modelMatrix, GLfloat fAux)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	glUseProgram(shader->program);

	GLint locModel = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint locView = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));

	GLint locProjection = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));

	GLint locFloatAux = glGetUniformLocation(shader->program, "v_float_aux");
	glUniform1f(locFloatAux, fAux);

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}



