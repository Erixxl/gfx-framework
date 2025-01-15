#include "homework_2/homework2.hpp"


using namespace std;
using namespace hw2;


Homework2::Homework2()
{
	// Class variables initialization
	polygon_mode = GL_FILL;
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
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

	glm::mat4 drone_matrix = glm::translate(glm::scale(glm::mat4(1), glm::vec3(0.1, 0.1, 0.1)), glm::vec3(0, 10, 0));
	glm::mat4 rotor_matrix = glm::translate(glm::scale(glm::mat4(1), glm::vec3(0.1, 0.1, 0.1)), glm::vec3(10, 11.5, 0));

	RenderSimpleMesh(meshes["ground"], shaders["GroundShader"], glm::mat4(1), Engine::GetElapsedTime());
	RenderSimpleMesh(meshes["default_drone"], shaders["VertexColor"], drone_matrix);
	//RenderSimpleMesh(meshes["rotor"], shaders["VertexNormal"], rotor_matrix);
}


void Homework2::FrameEnd()
{

}


void Homework2::OnInputUpdate(float deltaTime, int mods)
{

}


void Homework2::OnKeyPress(int key, int mods)
{
	// For debugging purposes
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygon_mode)
		{
		case GL_POINT:
			polygon_mode = GL_FILL;
			break;
		case GL_LINE:
			polygon_mode = GL_POINT;
			break;
		default:
			polygon_mode = GL_LINE;
			break;
		}
	}
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
		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3(-50, 0, -50)),
			VertexFormat(glm::vec3(-40, 0, -50)),
			VertexFormat(glm::vec3(-30, 0, -50)),
			VertexFormat(glm::vec3(-20, 0, -50)),
			VertexFormat(glm::vec3(-10, 0, -50)),
			VertexFormat(glm::vec3(  0, 0, -50)),
			VertexFormat(glm::vec3( 10, 0, -50)),
			VertexFormat(glm::vec3( 20, 0, -50)),
			VertexFormat(glm::vec3( 30, 0, -50)),
			VertexFormat(glm::vec3( 40, 0, -50)),
			VertexFormat(glm::vec3( 50, 0, -50)),

			VertexFormat(glm::vec3(-50, 0, -40)),
			VertexFormat(glm::vec3(-40, 0, -40)),
			VertexFormat(glm::vec3(-30, 0, -40)),
			VertexFormat(glm::vec3(-20, 0, -40)),
			VertexFormat(glm::vec3(-10, 0, -40)),
			VertexFormat(glm::vec3(  0, 0, -40)),
			VertexFormat(glm::vec3( 10, 0, -40)),
			VertexFormat(glm::vec3( 20, 0, -40)),
			VertexFormat(glm::vec3( 30, 0, -40)),
			VertexFormat(glm::vec3( 40, 0, -40)),
			VertexFormat(glm::vec3( 50, 0, -40)),

			VertexFormat(glm::vec3(-50, 0, -30)),
			VertexFormat(glm::vec3(-40, 0, -30)),
			VertexFormat(glm::vec3(-30, 0, -30)),
			VertexFormat(glm::vec3(-20, 0, -30)),
			VertexFormat(glm::vec3(-10, 0, -30)),
			VertexFormat(glm::vec3(  0, 0, -30)),
			VertexFormat(glm::vec3( 10, 0, -30)),
			VertexFormat(glm::vec3( 20, 0, -30)),
			VertexFormat(glm::vec3( 30, 0, -30)),
			VertexFormat(glm::vec3( 40, 0, -30)),
			VertexFormat(glm::vec3( 50, 0, -30)),

			VertexFormat(glm::vec3(-50, 0, -20)),
			VertexFormat(glm::vec3(-40, 0, -20)),
			VertexFormat(glm::vec3(-30, 0, -20)),
			VertexFormat(glm::vec3(-20, 0, -20)),
			VertexFormat(glm::vec3(-10, 0, -20)),
			VertexFormat(glm::vec3(  0, 0, -20)),
			VertexFormat(glm::vec3( 10, 0, -20)),
			VertexFormat(glm::vec3( 20, 0, -20)),
			VertexFormat(glm::vec3( 30, 0, -20)),
			VertexFormat(glm::vec3( 40, 0, -20)),
			VertexFormat(glm::vec3( 50, 0, -20)),

			VertexFormat(glm::vec3(-50, 0, -10)),
			VertexFormat(glm::vec3(-40, 0, -10)),
			VertexFormat(glm::vec3(-30, 0, -10)),
			VertexFormat(glm::vec3(-20, 0, -10)),
			VertexFormat(glm::vec3(-10, 0, -10)),
			VertexFormat(glm::vec3(  0, 0, -10)),
			VertexFormat(glm::vec3( 10, 0, -10)),
			VertexFormat(glm::vec3( 20, 0, -10)),
			VertexFormat(glm::vec3( 30, 0, -10)),
			VertexFormat(glm::vec3( 40, 0, -10)),
			VertexFormat(glm::vec3( 50, 0, -10)),

			VertexFormat(glm::vec3(-50, 0,   0)),
			VertexFormat(glm::vec3(-40, 0,   0)),
			VertexFormat(glm::vec3(-30, 0,   0)),
			VertexFormat(glm::vec3(-20, 0,   0)),
			VertexFormat(glm::vec3(-10, 0,   0)),
			VertexFormat(glm::vec3(  0, 0,   0)),
			VertexFormat(glm::vec3( 10, 0,   0)),
			VertexFormat(glm::vec3( 20, 0,   0)),
			VertexFormat(glm::vec3( 30, 0,   0)),
			VertexFormat(glm::vec3( 40, 0,   0)),
			VertexFormat(glm::vec3( 50, 0,   0)),

			VertexFormat(glm::vec3(-50, 0,  10)),
			VertexFormat(glm::vec3(-40, 0,  10)),
			VertexFormat(glm::vec3(-30, 0,  10)),
			VertexFormat(glm::vec3(-20, 0,  10)),
			VertexFormat(glm::vec3(-10, 0,  10)),
			VertexFormat(glm::vec3(  0, 0,  10)),
			VertexFormat(glm::vec3( 10, 0,  10)),
			VertexFormat(glm::vec3( 20, 0,  10)),
			VertexFormat(glm::vec3( 30, 0,  10)),
			VertexFormat(glm::vec3( 40, 0,  10)),
			VertexFormat(glm::vec3( 50, 0,  10)),

			VertexFormat(glm::vec3(-50, 0,  20)),
			VertexFormat(glm::vec3(-40, 0,  20)),
			VertexFormat(glm::vec3(-30, 0,  20)),
			VertexFormat(glm::vec3(-20, 0,  20)),
			VertexFormat(glm::vec3(-10, 0,  20)),
			VertexFormat(glm::vec3(  0, 0,  20)),
			VertexFormat(glm::vec3( 10, 0,  20)),
			VertexFormat(glm::vec3( 20, 0,  20)),
			VertexFormat(glm::vec3( 30, 0,  20)),
			VertexFormat(glm::vec3( 40, 0,  20)),
			VertexFormat(glm::vec3( 50, 0,  20)),

			VertexFormat(glm::vec3(-50, 0,  30)),
			VertexFormat(glm::vec3(-40, 0,  30)),
			VertexFormat(glm::vec3(-30, 0,  30)),
			VertexFormat(glm::vec3(-20, 0,  30)),
			VertexFormat(glm::vec3(-10, 0,  30)),
			VertexFormat(glm::vec3(  0, 0,  30)),
			VertexFormat(glm::vec3( 10, 0,  30)),
			VertexFormat(glm::vec3( 20, 0,  30)),
			VertexFormat(glm::vec3( 30, 0,  30)),
			VertexFormat(glm::vec3( 40, 0,  30)),
			VertexFormat(glm::vec3( 50, 0,  30)),

			VertexFormat(glm::vec3(-50, 0,  40)),
			VertexFormat(glm::vec3(-40, 0,  40)),
			VertexFormat(glm::vec3(-30, 0,  40)),
			VertexFormat(glm::vec3(-20, 0,  40)),
			VertexFormat(glm::vec3(-10, 0,  40)),
			VertexFormat(glm::vec3(  0, 0,  40)),
			VertexFormat(glm::vec3( 10, 0,  40)),
			VertexFormat(glm::vec3( 20, 0,  40)),
			VertexFormat(glm::vec3( 30, 0,  40)),
			VertexFormat(glm::vec3( 40, 0,  40)),
			VertexFormat(glm::vec3( 50, 0,  40)),

			VertexFormat(glm::vec3(-50, 0,  50)),
			VertexFormat(glm::vec3(-40, 0,  50)),
			VertexFormat(glm::vec3(-30, 0,  50)),
			VertexFormat(glm::vec3(-20, 0,  50)),
			VertexFormat(glm::vec3(-10, 0,  50)),
			VertexFormat(glm::vec3(  0, 0,  50)),
			VertexFormat(glm::vec3( 10, 0,  50)),
			VertexFormat(glm::vec3( 20, 0,  50)),
			VertexFormat(glm::vec3( 30, 0,  50)),
			VertexFormat(glm::vec3( 40, 0,  50)),
			VertexFormat(glm::vec3( 50, 0,  50))
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
			 15,  16,  26,  26,  16,  27,
			 16,  17,  27,  27,  17,  28,
			 17,  18,  28,  28,  18,  29,
			 18,  19,  29,  29,  19,  30,
			 19,  20,  30,  30,  20,  31,
			 20,  21,  31,  31,  21,  32,

			 22,  23,  33,  33,  23,  34,
			 23,  24,  34,  34,  24,  35,
			 24,  25,  35,  35,  25,  36,
			 25,  26,  36,  36,  26,  37,
			 26,  27,  37,  37,  27,  38,
			 27,  28,  38,  38,  28,  39,
			 28,  29,  39,  39,  29,  40,
			 29,  30,  40,  40,  30,  41,
			 30,  31,  41,  41,  31,  42,
			 31,  32,  42,  42,  32,  43,

			 33,  34,  44,  44,  34,  45,
			 34,  35,  45,  45,  35,  46,
			 35,  36,  46,  46,  36,  47,
			 36,  37,  47,  47,  37,  48,
			 37,  38,  48,  48,  38,  49,
			 38,  39,  49,  49,  39,  50,
			 39,  40,  50,  50,  40,  51,
			 40,  41,  51,  51,  41,  52,
			 41,  42,  52,  52,  42,  53,
			 42,  43,  53,  53,  43,  54,

			 44,  45,  55,  55,  45,  56,
			 45,  46,  56,  56,  46,  57,
			 46,  47,  57,  57,  47,  58,
			 47,  48,  58,  58,  48,  59,
			 48,  49,  59,  59,  49,  60,
			 49,  50,  60,  60,  50,  61,
			 50,  51,  61,  61,  51,  62,
			 51,  52,  62,  62,  52,  63,
			 52,  53,  63,  63,  53,  64,
			 53,  54,  64,  64,  54,  65,

			 55,  56,  66,  66,  56,  67,
			 56,  57,  67,  67,  57,  68,
			 57,  58,  68,  68,  58,  69,
			 58,  59,  69,  69,  59,  70,
			 59,  60,  70,  70,  60,  71,
			 60,  61,  71,  71,  61,  72,
			 61,  62,  72,  72,  62,  73,
			 62,  63,  73,  73,  63,  74,
			 63,  64,  74,  74,  64,  75,
			 64,  65,  75,  75,  65,  76,

			 66,  67,  77,  77,  67,  78,
			 67,  68,  78,  78,  68,  79,
			 68,  69,  79,  79,  69,  80,
			 69,  70,  80,  80,  70,  81,
			 70,  71,  81,  81,  71,  82,
			 71,  72,  82,  82,  72,  83,
			 72,  73,  83,  83,  73,  84,
			 73,  74,  84,  84,  74,  85,
			 74,  75,  85,  85,  75,  86,
			 75,  76,  86,  86,  76,  87,

			 77,  78,  88,  88,  78,  89,
			 78,  79,  89,  89,  79,  90,
			 79,  80,  90,  90,  80,  91,
			 80,  81,  91,  91,  81,  92,
			 81,  82,  92,  92,  82,  93,
			 82,  83,  93,  93,  83,  94,
			 83,  84,  94,  94,  84,  95,
			 84,  85,  95,  95,  85,  96,
			 85,  86,  96,  96,  86,  97,
			 86,  87,  97,  97,  87,  98,

			 88,  89,  99,  99,  89, 100,
			 89,  90, 100, 100,  90, 101,
			 90,  91, 101, 101,  91, 102,
			 91,  92, 102, 102,  92, 103,
			 92,  93, 103, 103,  93, 104,
			 93,  94, 104, 104,  94, 105,
			 94,  95, 105, 105,  95, 106,
			 95,  96, 106, 106,  96, 107,
			 96,  97, 107, 107,  97, 108,
			 97,  98, 108, 108,  98, 109,

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
		glm::vec3 dark = glm::vec3(175.0 / 255.0, 23.0 / 255.0, 64.0 / 255.0);
		glm::vec3 darker = glm::vec3(116.0 / 255.0, 9.0 / 255.0, 56.0 / 255.0);
		glm::vec3 light = glm::vec3(204.0 / 255.0, 43.0 / 255.0, 82.0 / 255.0);

		vector<VertexFormat> vertices = {
			// Upper region
			VertexFormat(glm::vec3(10, 1, 1), dark), // 0
			VertexFormat(glm::vec3(10, 1, -1), dark),
			VertexFormat(glm::vec3(-10, 1, -1), dark),
			VertexFormat(glm::vec3(-10, 1, 1), dark),
			VertexFormat(glm::vec3(-1, 1, 10), dark),
			VertexFormat(glm::vec3(1, 1, 10), dark),
			VertexFormat(glm::vec3(1, 1, -10), dark),
			VertexFormat(glm::vec3(-1, 1, -10), dark),

			// Lower region
			VertexFormat(glm::vec3(10, -1, 1), dark), // 8
			VertexFormat(glm::vec3(10, -1, -1), dark),
			VertexFormat(glm::vec3(-10, -1, -1), dark),
			VertexFormat(glm::vec3(-10, -1, 1), dark),
			VertexFormat(glm::vec3(-1, -1, 10), dark),
			VertexFormat(glm::vec3(1, -1, 10), dark),
			VertexFormat(glm::vec3(1, -1, -10), dark),
			VertexFormat(glm::vec3(-1, -1, -10), dark),

			// Left rotor

			// Top ring
			VertexFormat(glm::vec3(1 + 9, 2, -5), darker), // 16
			VertexFormat(glm::vec3(-1 + 9, 2, -5), darker),
			VertexFormat(glm::vec3(-3 + 9, 2, -4), darker),
			VertexFormat(glm::vec3(-4 + 9, 2, -3), darker),
			VertexFormat(glm::vec3(-5 + 9, 2, -1), darker),
			VertexFormat(glm::vec3(-5 + 9, 2, 1), darker),
			VertexFormat(glm::vec3(-4 + 9, 2, 3), darker),
			VertexFormat(glm::vec3(-3 + 9, 2, 4), darker),
			VertexFormat(glm::vec3(-1 + 9, 2, 5), darker),
			VertexFormat(glm::vec3(1 + 9, 2, 5), darker),
			VertexFormat(glm::vec3(3 + 9, 2, 4), darker),
			VertexFormat(glm::vec3(4 + 9, 2, 3), darker),
			VertexFormat(glm::vec3(5 + 9, 2, 1), darker),
			VertexFormat(glm::vec3(5 + 9, 2, -1), darker),
			VertexFormat(glm::vec3(4 + 9, 2, -3), darker),
			VertexFormat(glm::vec3(3 + 9, 2, -4), darker),

			// Bottom ring
			VertexFormat(glm::vec3(1 + 9, 1, -5), darker), // 32
			VertexFormat(glm::vec3(-1 + 9, 1, -5), darker),
			VertexFormat(glm::vec3(-3 + 9, 1, -4), darker),
			VertexFormat(glm::vec3(-4 + 9, 1, -3), darker),
			VertexFormat(glm::vec3(-5 + 9, 1, -1), darker),
			VertexFormat(glm::vec3(-5 + 9, 1, 1), darker),
			VertexFormat(glm::vec3(-4 + 9, 1, 3), darker),
			VertexFormat(glm::vec3(-3 + 9, 1, 4), darker),
			VertexFormat(glm::vec3(-1 + 9, 1, 5), darker),
			VertexFormat(glm::vec3(1 + 9, 1, 5), darker),
			VertexFormat(glm::vec3(3 + 9, 1, 4), darker),
			VertexFormat(glm::vec3(4 + 9, 1, 3), darker),
			VertexFormat(glm::vec3(5 + 9, 1, 1), darker),
			VertexFormat(glm::vec3(5 + 9, 1, -1), darker),
			VertexFormat(glm::vec3(4 + 9, 1, -3), darker),
			VertexFormat(glm::vec3(3 + 9, 1, -4), darker),

			// Right rotor

			// Top ring
			VertexFormat(glm::vec3(1 - 9, 2, -5), darker), // 48
			VertexFormat(glm::vec3(-1 - 9, 2, -5), darker),
			VertexFormat(glm::vec3(-3 - 9, 2, -4), darker),
			VertexFormat(glm::vec3(-4 - 9, 2, -3), darker),
			VertexFormat(glm::vec3(-5 - 9, 2, -1), darker),
			VertexFormat(glm::vec3(-5 - 9, 2, 1), darker),
			VertexFormat(glm::vec3(-4 - 9, 2, 3), darker),
			VertexFormat(glm::vec3(-3 - 9, 2, 4), darker),
			VertexFormat(glm::vec3(-1 - 9, 2, 5), darker),
			VertexFormat(glm::vec3(1 - 9, 2, 5), darker),
			VertexFormat(glm::vec3(3 - 9, 2, 4), darker),
			VertexFormat(glm::vec3(4 - 9, 2, 3), darker),
			VertexFormat(glm::vec3(5 - 9, 2, 1), darker),
			VertexFormat(glm::vec3(5 - 9, 2, -1), darker),
			VertexFormat(glm::vec3(4 - 9, 2, -3), darker),
			VertexFormat(glm::vec3(3 - 9, 2, -4), darker),

			// Bottom ring
			VertexFormat(glm::vec3(1 - 9, 1, -5), darker), // 64
			VertexFormat(glm::vec3(-1 - 9, 1, -5), darker),
			VertexFormat(glm::vec3(-3 - 9, 1, -4), darker),
			VertexFormat(glm::vec3(-4 - 9, 1, -3), darker),
			VertexFormat(glm::vec3(-5 - 9, 1, -1), darker),
			VertexFormat(glm::vec3(-5 - 9, 1, 1), darker),
			VertexFormat(glm::vec3(-4 - 9, 1, 3), darker),
			VertexFormat(glm::vec3(-3 - 9, 1, 4), darker),
			VertexFormat(glm::vec3(-1 - 9, 1, 5), darker),
			VertexFormat(glm::vec3(1 - 9, 1, 5), darker),
			VertexFormat(glm::vec3(3 - 9, 1, 4), darker),
			VertexFormat(glm::vec3(4 - 9, 1, 3), darker),
			VertexFormat(glm::vec3(5 - 9, 1, 1), darker),
			VertexFormat(glm::vec3(5 - 9, 1, -1), darker),
			VertexFormat(glm::vec3(4 - 9, 1, -3), darker),
			VertexFormat(glm::vec3(3 - 9, 1, -4), darker),

			// Front rotor

			// Top ring
			VertexFormat(glm::vec3(1, 2, -5 + 9), darker), // 80
			VertexFormat(glm::vec3(-1, 2, -5 + 9), darker),
			VertexFormat(glm::vec3(-3, 2, -4 + 9), darker),
			VertexFormat(glm::vec3(-4, 2, -3 + 9), darker),
			VertexFormat(glm::vec3(-5, 2, -1 + 9), darker),
			VertexFormat(glm::vec3(-5, 2, 1 + 9), darker),
			VertexFormat(glm::vec3(-4, 2, 3 + 9), darker),
			VertexFormat(glm::vec3(-3, 2, 4 + 9), darker),
			VertexFormat(glm::vec3(-1, 2, 5 + 9), darker),
			VertexFormat(glm::vec3(1, 2, 5 + 9), darker),
			VertexFormat(glm::vec3(3, 2, 4 + 9), darker),
			VertexFormat(glm::vec3(4, 2, 3 + 9), darker),
			VertexFormat(glm::vec3(5, 2, 1 + 9), darker),
			VertexFormat(glm::vec3(5, 2, -1 + 9), darker),
			VertexFormat(glm::vec3(4, 2, -3 + 9), darker),
			VertexFormat(glm::vec3(3, 2, -4 + 9), darker),

			// Bottom ring
			VertexFormat(glm::vec3(1, 1, -5 + 9), darker), // 96
			VertexFormat(glm::vec3(-1, 1, -5 + 9), darker),
			VertexFormat(glm::vec3(-3, 1, -4 + 9), darker),
			VertexFormat(glm::vec3(-4, 1, -3 + 9), darker),
			VertexFormat(glm::vec3(-5, 1, -1 + 9), darker),
			VertexFormat(glm::vec3(-5, 1, 1 + 9), darker),
			VertexFormat(glm::vec3(-4, 1, 3 + 9), darker),
			VertexFormat(glm::vec3(-3, 1, 4 + 9), darker),
			VertexFormat(glm::vec3(-1, 1, 5 + 9), darker),
			VertexFormat(glm::vec3(1, 1, 5 + 9), darker),
			VertexFormat(glm::vec3(3, 1, 4 + 9), darker),
			VertexFormat(glm::vec3(4, 1, 3 + 9), darker),
			VertexFormat(glm::vec3(5, 1, 1 + 9), darker),
			VertexFormat(glm::vec3(5, 1, -1 + 9), darker),
			VertexFormat(glm::vec3(4, 1, -3 + 9), darker),
			VertexFormat(glm::vec3(3, 1, -4 + 9), darker),

			// Back rotor

			// Top ring
			VertexFormat(glm::vec3(1, 2, -5 - 9), darker), // 112
			VertexFormat(glm::vec3(-1, 2, -5 - 9), darker),
			VertexFormat(glm::vec3(-3, 2, -4 - 9), darker),
			VertexFormat(glm::vec3(-4, 2, -3 - 9), darker),
			VertexFormat(glm::vec3(-5, 2, -1 - 9), darker),
			VertexFormat(glm::vec3(-5, 2, 1 - 9), darker),
			VertexFormat(glm::vec3(-4, 2, 3 - 9), darker),
			VertexFormat(glm::vec3(-3, 2, 4 - 9), darker),
			VertexFormat(glm::vec3(-1, 2, 5 - 9), darker),
			VertexFormat(glm::vec3(1, 2, 5 - 9), darker),
			VertexFormat(glm::vec3(3, 2, 4 - 9), darker),
			VertexFormat(glm::vec3(4, 2, 3 - 9), darker),
			VertexFormat(glm::vec3(5, 2, 1 - 9), darker),
			VertexFormat(glm::vec3(5, 2, -1 - 9), darker),
			VertexFormat(glm::vec3(4, 2, -3 - 9), darker),
			VertexFormat(glm::vec3(3, 2, -4 - 9), darker),

			// Bottom ring
			VertexFormat(glm::vec3(1, 1, -5 - 9), darker), // 128
			VertexFormat(glm::vec3(-1, 1, -5 - 9), darker),
			VertexFormat(glm::vec3(-3, 1, -4 - 9), darker),
			VertexFormat(glm::vec3(-4, 1, -3 - 9), darker),
			VertexFormat(glm::vec3(-5, 1, -1 - 9), darker),
			VertexFormat(glm::vec3(-5, 1, 1 - 9), darker),
			VertexFormat(glm::vec3(-4, 1, 3 - 9), darker),
			VertexFormat(glm::vec3(-3, 1, 4 - 9), darker),
			VertexFormat(glm::vec3(-1, 1, 5 - 9), darker),
			VertexFormat(glm::vec3(1, 1, 5 - 9), darker),
			VertexFormat(glm::vec3(3, 1, 4 - 9), darker),
			VertexFormat(glm::vec3(4, 1, 3 - 9), darker),
			VertexFormat(glm::vec3(5, 1, 1 - 9), darker),
			VertexFormat(glm::vec3(5, 1, -1 - 9), darker),
			VertexFormat(glm::vec3(4, 1, -3 - 9), darker),
			VertexFormat(glm::vec3(3, 1, -4 - 9), darker),

		};

		vector<GLuint> indices = {
			// Main body
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,

			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,

			1, 0, 8, 1, 8, 9,
			2, 1, 9, 2, 9, 10,
			3, 2, 10, 3, 10, 11,
			0, 3, 11, 0, 11, 8,

			5, 4, 12, 5, 12, 13,
			6, 5, 14, 6, 13, 14,
			7, 6, 14, 7, 14, 15,
			4, 7, 15, 4, 15, 12,

			// Left rotor
			0 + 16, 1 + 16, 17 + 16, 0 + 16, 17 + 16, 16 + 16,
			1 + 16, 2 + 16, 18 + 16, 1 + 16, 18 + 16, 17 + 16,
			2 + 16, 3 + 16, 19 + 16, 2 + 16, 19 + 16, 18 + 16,
			3 + 16, 4 + 16, 20 + 16, 3 + 16, 20 + 16, 19 + 16,
			4 + 16, 5 + 16, 21 + 16, 4 + 16, 21 + 16, 20 + 16,
			5 + 16, 6 + 16, 22 + 16, 5 + 16, 22 + 16, 21 + 16,
			6 + 16, 7 + 16, 23 + 16, 6 + 16, 23 + 16, 22 + 16,
			7 + 16, 8 + 16, 24 + 16, 7 + 16, 24 + 16, 23 + 16,
			8 + 16, 9 + 16, 25 + 16, 8 + 16, 25 + 16, 24 + 16,
			9 + 16, 10 + 16, 26 + 16, 9 + 16, 26 + 16, 25 + 16,
			10 + 16, 11 + 16, 27 + 16, 10 + 16, 27 + 16, 26 + 16,
			11 + 16, 12 + 16, 28 + 16, 11 + 16, 28 + 16, 27 + 16,
			12 + 16, 13 + 16, 29 + 16, 12 + 16, 29 + 16, 28 + 16,
			13 + 16, 14 + 16, 30 + 16, 13 + 16, 30 + 16, 29 + 16,
			14 + 16, 15 + 16, 31 + 16, 14 + 16, 31 + 16, 30 + 16,
			15 + 16, 0 + 16, 16 + 16, 15 + 16, 16 + 16, 31 + 16,

			// Right rotor
			0 + 48, 1 + 48, 17 + 48, 0 + 48, 17 + 48, 16 + 48,
			1 + 48, 2 + 48, 18 + 48, 1 + 48, 18 + 48, 17 + 48,
			2 + 48, 3 + 48, 19 + 48, 2 + 48, 19 + 48, 18 + 48,
			3 + 48, 4 + 48, 20 + 48, 3 + 48, 20 + 48, 19 + 48,
			4 + 48, 5 + 48, 21 + 48, 4 + 48, 21 + 48, 20 + 48,
			5 + 48, 6 + 48, 22 + 48, 5 + 48, 22 + 48, 21 + 48,
			6 + 48, 7 + 48, 23 + 48, 6 + 48, 23 + 48, 22 + 48,
			7 + 48, 8 + 48, 24 + 48, 7 + 48, 24 + 48, 23 + 48,
			8 + 48, 9 + 48, 25 + 48, 8 + 48, 25 + 48, 24 + 48,
			9 + 48, 10 + 48, 26 + 48, 9 + 48, 26 + 48, 25 + 48,
			10 + 48, 11 + 48, 27 + 48, 10 + 48, 27 + 48, 26 + 48,
			11 + 48, 12 + 48, 28 + 48, 11 + 48, 28 + 48, 27 + 48,
			12 + 48, 13 + 48, 29 + 48, 12 + 48, 29 + 48, 28 + 48,
			13 + 48, 14 + 48, 30 + 48, 13 + 48, 30 + 48, 29 + 48,
			14 + 48, 15 + 48, 31 + 48, 14 + 48, 31 + 48, 30 + 48,
			15 + 48, 0 + 48, 16 + 48, 15 + 48, 16 + 48, 31 + 48,

			// Front rotor
			0 + 80, 1 + 80, 17 + 80, 0 + 80, 17 + 80, 16 + 80,
			1 + 80, 2 + 80, 18 + 80, 1 + 80, 18 + 80, 17 + 80,
			2 + 80, 3 + 80, 19 + 80, 2 + 80, 19 + 80, 18 + 80,
			3 + 80, 4 + 80, 20 + 80, 3 + 80, 20 + 80, 19 + 80,
			4 + 80, 5 + 80, 21 + 80, 4 + 80, 21 + 80, 20 + 80,
			5 + 80, 6 + 80, 22 + 80, 5 + 80, 22 + 80, 21 + 80,
			6 + 80, 7 + 80, 23 + 80, 6 + 80, 23 + 80, 22 + 80,
			7 + 80, 8 + 80, 24 + 80, 7 + 80, 24 + 80, 23 + 80,
			8 + 80, 9 + 80, 25 + 80, 8 + 80, 25 + 80, 24 + 80,
			9 + 80, 10 + 80, 26 + 80, 9 + 80, 26 + 80, 25 + 80,
			10 + 80, 11 + 80, 27 + 80, 10 + 80, 27 + 80, 26 + 80,
			11 + 80, 12 + 80, 28 + 80, 11 + 80, 28 + 80, 27 + 80,
			12 + 80, 13 + 80, 29 + 80, 12 + 80, 29 + 80, 28 + 80,
			13 + 80, 14 + 80, 30 + 80, 13 + 80, 30 + 80, 29 + 80,
			14 + 80, 15 + 80, 31 + 80, 14 + 80, 31 + 80, 30 + 80,
			15 + 80, 0 + 80, 16 + 80, 15 + 80, 16 + 80, 31 + 80,

			// Back rotor
			0 + 112, 1 + 112, 17 + 112, 0 + 112, 17 + 112, 16 + 112,
			1 + 112, 2 + 112, 18 + 112, 1 + 112, 18 + 112, 17 + 112,
			2 + 112, 3 + 112, 19 + 112, 2 + 112, 19 + 112, 18 + 112,
			3 + 112, 4 + 112, 20 + 112, 3 + 112, 20 + 112, 19 + 112,
			4 + 112, 5 + 112, 21 + 112, 4 + 112, 21 + 112, 20 + 112,
			5 + 112, 6 + 112, 22 + 112, 5 + 112, 22 + 112, 21 + 112,
			6 + 112, 7 + 112, 23 + 112, 6 + 112, 23 + 112, 22 + 112,
			7 + 112, 8 + 112, 24 + 112, 7 + 112, 24 + 112, 23 + 112,
			8 + 112, 9 + 112, 25 + 112, 8 + 112, 25 + 112, 24 + 112,
			9 + 112, 10 + 112, 26 + 112, 9 + 112, 26 + 112, 25 + 112,
			10 + 112, 11 + 112, 27 + 112, 10 + 112, 27 + 112, 26 + 112,
			11 + 112, 12 + 112, 28 + 112, 11 + 112, 28 + 112, 27 + 112,
			12 + 112, 13 + 112, 29 + 112, 12 + 112, 29 + 112, 28 + 112,
			13 + 112, 14 + 112, 30 + 112, 13 + 112, 30 + 112, 29 + 112,
			14 + 112, 15 + 112, 31 + 112, 14 + 112, 31 + 112, 30 + 112,
			15 + 112, 0 + 112, 16 + 112, 15 + 112, 16 + 112, 31 + 112,
		};

		CreateMesh(vertices, indices, "default_drone");
	}

	// Temporary rotor mesh
	{
		vector<VertexFormat> vertices = {
			// Top ring
			VertexFormat(glm::vec3(1, 0.5, -5)),
			VertexFormat(glm::vec3(-1, 0.5, -5)),
			VertexFormat(glm::vec3(-3, 0.5, -4)),
			VertexFormat(glm::vec3(-4, 0.5, -3)),
			VertexFormat(glm::vec3(-5, 0.5, -1)),
			VertexFormat(glm::vec3(-5, 0.5, 1)),
			VertexFormat(glm::vec3(-4, 0.5, 3)),
			VertexFormat(glm::vec3(-3, 0.5, 4)),
			VertexFormat(glm::vec3(-1, 0.5, 5)),
			VertexFormat(glm::vec3(1, 0.5, 5)),
			VertexFormat(glm::vec3(3, 0.5, 4)),
			VertexFormat(glm::vec3(4, 0.5, 3)),
			VertexFormat(glm::vec3(5, 0.5, 1)),
			VertexFormat(glm::vec3(5, 0.5, -1)),
			VertexFormat(glm::vec3(4, 0.5, -3)),
			VertexFormat(glm::vec3(3, 0.5, -4)),

			// Bottom ring
			VertexFormat(glm::vec3(1, -0.5, -5)),
			VertexFormat(glm::vec3(-1, -0.5, -5)),
			VertexFormat(glm::vec3(-3, -0.5, -4)),
			VertexFormat(glm::vec3(-4, -0.5, -3)),
			VertexFormat(glm::vec3(-5, -0.5, -1)),
			VertexFormat(glm::vec3(-5, -0.5, 1)),
			VertexFormat(glm::vec3(-4, -0.5, 3)),
			VertexFormat(glm::vec3(-3, -0.5, 4)),
			VertexFormat(glm::vec3(-1, -0.5, 5)),
			VertexFormat(glm::vec3(1, -0.5, 5)),
			VertexFormat(glm::vec3(3, -0.5, 4)),
			VertexFormat(glm::vec3(4, -0.5, 3)),
			VertexFormat(glm::vec3(5, -0.5, 1)),
			VertexFormat(glm::vec3(5, -0.5, -1)),
			VertexFormat(glm::vec3(4, -0.5, -3)),
			VertexFormat(glm::vec3(3, -0.5, -4)),
		};

		vector<GLuint> indices = {
			0, 1, 17, 0, 17, 16,
			1, 2, 18, 1, 18, 17,
			2, 3, 19, 2, 19, 18,
			3, 4, 20, 3, 20, 19,
			4, 5, 21, 4, 21, 20,
			5, 6, 22, 5, 22, 21,
			6, 7, 23, 6, 23, 22,
			7, 8, 24, 7, 24, 23,
			8, 9, 25, 8, 25, 24,
			9, 10, 26, 9, 26, 25,
			10, 11, 27, 10, 27, 26,
			11, 12, 28, 11, 28, 27,
			12, 13, 29, 12, 29, 28,
			13, 14, 30, 13, 30, 29,
			14, 15, 31, 14, 31, 30,
			15, 0, 16, 15, 16, 31
		};

		CreateMesh(vertices, indices, "rotor");
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



