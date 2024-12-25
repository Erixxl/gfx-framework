#include "lab_m1/lab2/lab2.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab2::Lab2()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;
}


Lab2::~Lab2()
{
}


void Lab2::Init()
{
	// Custom shader init
	{
		Shader* shader = new Shader("TestShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab2", "shaders", "test.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab2", "shaders", "test.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			// TODO(student): Complete the vertices data for the cube mesh

			// Vertex 0
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 1)),

			// Vertex 1
			VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(0, 0, 1)),

			// Vertex 2
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0)),

			// Vertex 3
			VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(0, 0, 0)),

			// Vertex 4
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)),

			// Vertex 5
			VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(0, 1, 1)),

			// Vertex 6
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0)),

			// Vertex 7
			VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(0, 1, 0)),
		};

		vector<GLuint> indices =
		{
			// TODO(student): Complete indices data for the cube mesh
			0, 1, 2,
			1, 3, 2,
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4
		};

		meshes["cube_A"] = new Mesh("generated cube 1");
		meshes["cube_A"]->InitFromData(vertices, indices);

		// Actually create the mesh from the data
		CreateMesh("cube_B", vertices, indices);
	}

	// TODO(student): Create a tetrahedron mesh. You can create it with
	// only 4 vertices, or you can choose the harder route and create it
	// with 12 vertices. Think about it, why would you want that, and how
	// would you do it? After all, a tetrahedron has only 4 vertices
	// by definition!

	{
		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3( 0.943f, -0.333f,  0.000f), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-0.471f, -0.333f,  0.816f), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-0.471f, -0.333f, -0.816f), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3( 0.000f,  1.000f,  0.000f), glm::vec3(1, 1, 1))
		};

		vector<GLuint> indices = {
			0, 1, 2,
			0, 3, 1,
			1, 3, 2,
			2, 3, 0
		};

		CreateMesh("tetra", vertices, indices);
	}

	// TODO(student): Create a square using two triangles with
	// opposing vertex orientations.
	{
		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3(-1, -1, 0), glm::vec3(1)),
			VertexFormat(glm::vec3( 1, -1, 0), glm::vec3(1)),
			VertexFormat(glm::vec3( 1,  1, 0), glm::vec3(1)),
			VertexFormat(glm::vec3(-1,  1, 0), glm::vec3(1)),
		};

		vector<GLuint> indices = {
			0, 1, 2,
			0, 3, 2
		};

		CreateMesh("square", vertices, indices);
	}

	// Dodecahedron
	{
		GLfloat phi = 1.618f;

		vector<VertexFormat> vertices = {
			VertexFormat( glm::vec3(1, 1, 1),            glm::vec3(1.00) ), // A = 0
			VertexFormat( glm::vec3(-1, 1, 1),           glm::vec3(0.95) ), // B = 1
			VertexFormat( glm::vec3(1, -1, 1),           glm::vec3(0.90) ), // C = 2
			VertexFormat( glm::vec3(-1, -1, 1),          glm::vec3(0.85) ), // D = 3
			VertexFormat( glm::vec3(1, 1, -1),           glm::vec3(0.80) ), // E = 4
			VertexFormat( glm::vec3(-1, 1, -1),          glm::vec3(0.75) ), // F = 5
			VertexFormat( glm::vec3(1, -1, -1),          glm::vec3(0.70) ), // G = 6
			VertexFormat( glm::vec3(-1, -1, -1),         glm::vec3(0.65) ), // H = 7
			VertexFormat( glm::vec3(0, phi, 1 / phi),    glm::vec3(0.60) ), // I = 8
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   glm::vec3(0.55) ), // J = 9
			VertexFormat( glm::vec3(0, phi, -1 / phi),   glm::vec3(0.50) ), // K = 10
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  glm::vec3(0.45) ), // L = 11
			VertexFormat( glm::vec3(1 / phi, 0, phi),    glm::vec3(0.40) ), // M = 12
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   glm::vec3(0.35) ), // N = 13
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   glm::vec3(0.30) ), // O = 14
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  glm::vec3(0.25) ), // P = 15
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    glm::vec3(0.20) ), // Q = 16
			VertexFormat( glm::vec3(-phi, 1 / phi, 0),   glm::vec3(0.15) ), // R = 17
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   glm::vec3(0.10) ), // S = 18
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  glm::vec3(0.05) ), // T = 19
		};

		vector<GLuint> indices = {
			// Pentagon to triangles:
			// a b c d e => a b c, a c d, a d e

			// Face 1 - A I B N M
			0, 8, 1, 0, 1, 13, 0, 13, 12,

			// Face 2 - B R T D N
			1, 17, 19, 1, 19, 3, 1, 3, 13,

			// Face 3 - D J C M N
			3, 9, 2, 3, 2, 12, 3, 12, 13,

			// Face 4 - S Q A M C
			18, 16, 0, 18, 0, 12, 18, 12, 2,

			// Face 5 - E K I A Q
			4, 10, 8, 4, 8, 0, 4, 0, 16,

			// Face 6 - F R B I K
			5, 17, 1, 5, 1, 8, 5, 8, 10,

			// Face 7 - P H T R F
			15, 7, 19, 15, 19, 17, 15, 17, 5,

			// Face 8 - H L J D T
			7, 11, 9, 7, 9, 3, 7, 3, 19,

			// Face 9 - L G S C J
			11, 6, 18, 11, 18, 2, 11, 2, 9,

			// Face 10 - S G O E Q
			18, 6, 14, 18, 14, 4, 18, 4, 16,

			// Face 11 - O P F K E
			14, 15, 5, 14, 5, 10, 14, 10, 4,

			// Face 12 - O G L H P
			14, 6, 11, 14, 11, 7, 14, 7, 15
		};

		CreateMesh("dodecahedron", vertices, indices);
	}

	// Colored Dodecahedron
	{
		GLfloat phi = 1.618f;

		vector<glm::vec3> colors = {
			glm::vec3(1.00f, 1.00f, 0.00f),
			glm::vec3(1.00f, 0.00f, 1.00f),
			glm::vec3(0.00f, 1.00f, 1.00f),
			glm::vec3(1.00f, 0.00f, 0.00f),
			glm::vec3(0.00f, 1.00f, 0.00f),
			glm::vec3(0.00f, 0.00f, 1.00f),
			glm::vec3(1.00f, 0.50f, 0.00f),
			glm::vec3(0.00f, 1.00f, 0.50f),
			glm::vec3(0.50f, 0.00f, 1.00f),
			glm::vec3(1.00f, 0.00f, 0.50f),
			glm::vec3(0.50f, 1.00f, 0.00f),
			glm::vec3(0.00f, 0.50f, 1.00f)
		};

		vector<VertexFormat> vertices = {
			// Face 1:
			VertexFormat( glm::vec3(1, 1, 1),            colors[0]), // A = 0
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[0]), // I = 8
			VertexFormat( glm::vec3(-1, 1, 1),           colors[0]), // B = 1
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[0]), // N = 13
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[0]), // M = 12

			// Face 2:
			VertexFormat( glm::vec3(-1, 1, 1),           colors[1]), // B = 1
			VertexFormat( glm::vec3(-phi, 1 / phi, 0),   colors[1]), // R = 17
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[1]), // T = 19
			VertexFormat( glm::vec3(-1, -1, 1),          colors[1]), // D = 3
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[1]), // N = 13

			// Face 3:
			VertexFormat( glm::vec3(-1, -1, 1),          colors[2]), // D = 3
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[2]), // J = 9
			VertexFormat( glm::vec3(1, -1, 1),           colors[2]), // C = 2
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[2]), // M = 12
			VertexFormat( glm::vec3(-1 / phi, 0, phi),   colors[2]), // N = 13

			// Face 4:
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[3]), // S = 18
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[3]), // Q = 16
			VertexFormat( glm::vec3(1, 1, 1),            colors[3]), // A = 0
			VertexFormat( glm::vec3(1 / phi, 0, phi),    colors[3]), // M = 12
			VertexFormat( glm::vec3(1, -1, 1),           colors[3]), // C = 2

			// Face 5:
			VertexFormat( glm::vec3(1, 1, -1),           colors[4]), // E = 4
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[4]), // K = 10
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[4]), // I = 8
			VertexFormat( glm::vec3(1, 1, 1),            colors[4]), // A = 0
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[4]), // Q = 16

			// Face 6:
			VertexFormat( glm::vec3(-1, 1, -1),          colors[5]), // F = 5
			VertexFormat(glm::vec3(-phi, 1 / phi, 0),    colors[5]), // R = 17
			VertexFormat( glm::vec3(-1, 1, 1),           colors[5]), // B = 1
			VertexFormat( glm::vec3(0, phi, 1 / phi),    colors[5]), // I = 8
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[5]), // K = 10

			// Face 7:
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[6]), // P = 15
			VertexFormat( glm::vec3(-1, -1, -1),         colors[6]), // H = 7
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[6]), // T = 19
			VertexFormat( glm::vec3(-phi, 1 / phi, 0),   colors[6]), // R = 17
			VertexFormat( glm::vec3(-1, 1, -1),          colors[6]), // F = 5

			// Face 8:
			VertexFormat( glm::vec3(-1, -1, -1),         colors[7]), // H = 7
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[7]), // L = 11
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[7]), // J = 9
			VertexFormat( glm::vec3(-1, -1, 1),          colors[7]), // D = 3
			VertexFormat( glm::vec3(-phi, -1 / phi, 0),  colors[7]), // T = 19

			// Face 9:
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[8]), // L = 11
			VertexFormat( glm::vec3(1, -1, -1),          colors[8]), // G = 6
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[8]), // S = 18
			VertexFormat( glm::vec3(1, -1, 1),           colors[8]), // C = 2
			VertexFormat( glm::vec3(0, -phi, 1 / phi),   colors[8]), // J = 9

			// Face 10:
			VertexFormat( glm::vec3(phi, -1 / phi, 0),   colors[9]), // S = 18
			VertexFormat( glm::vec3(1, -1, -1),          colors[9]), // G = 6
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[9]), // O = 14
			VertexFormat( glm::vec3(1, 1, -1),           colors[9]), // E = 4
			VertexFormat( glm::vec3(phi, 1 / phi, 0),    colors[9]), // Q = 16

			// Face 11:
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[10]), // O = 14
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[10]), // P = 15
			VertexFormat( glm::vec3(-1, 1, -1),          colors[10]), // F = 5
			VertexFormat( glm::vec3(0, phi, -1 / phi),   colors[10]), // K = 10
			VertexFormat( glm::vec3(1, 1, -1),           colors[10]), // E = 4

			// Face 12:
			VertexFormat( glm::vec3(1 / phi, 0, -phi),   colors[11]), // O = 14
			VertexFormat( glm::vec3(1, -1, -1),          colors[11]), // G = 6
			VertexFormat( glm::vec3(0, -phi, -1 / phi),  colors[11]), // L = 11
			VertexFormat( glm::vec3(-1, -1, -1),         colors[11]), // H = 7
			VertexFormat( glm::vec3(-1 / phi, 0, -phi),  colors[11]), // P = 15
		};

		vector<GLuint> indices = {
			// Pentagon to triangles:
			// a b c d e => a b c, a c d, a d e

			// Face 1 - A I B N M
			0, 1, 2, 0, 2, 3, 0, 3, 4,

			// Face 2 - B R T D N
			5, 6, 7, 5, 7, 8, 5, 8, 9,

			// Face 3 - D J C M N
			10, 11, 12, 10, 12, 13, 10, 13, 14,

			// Face 4 - S Q A M C
			15, 16, 17, 15, 17, 18, 15, 18, 19,

			// Face 5 - E K I A Q
			20, 21, 22, 20, 22, 23, 20, 23, 24,

			// Face 6 - F R B I K
			25, 26, 27, 25, 27, 28, 25, 28, 29,

			// Face 7 - P H T R F
			30, 31, 32, 30, 32, 33, 30, 33, 34,

			// Face 8 - H L J D T
			35, 36, 37, 35, 37, 38, 35, 38, 39,

			// Face 9 - L G S C J
			40, 41, 42, 40, 42, 43, 40, 43, 44,

			// Face 10 - S G O E Q
			45, 46, 47, 45, 47, 48, 45, 48, 49,

			// Face 11 - O P F K E
			50, 51, 52, 50, 52, 53, 50, 53, 54,

			// Face 12 - O G L H P
			55, 56, 57, 55, 57, 58, 55, 58, 59
		};

		CreateMesh("twelve", vertices, indices);
	}

	{
		vector<VertexFormat> vertices = {
			// Face 1
			VertexFormat(glm::vec3( 0.943f, -0.333f,  0.000f), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-0.471f, -0.333f,  0.816f), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-0.471f, -0.333f, -0.816f), glm::vec3(1, 1, 1)),

			// Face 2
			VertexFormat(glm::vec3( 0.943f, -0.333f,  0.000f), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3( 0.000f,  1.000f,  0.000f), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-0.471f, -0.333f,  0.816f), glm::vec3(1, 1, 0)),

			// Face 3
			VertexFormat(glm::vec3(-0.471f, -0.333f,  0.816f), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3( 0.000f,  1.000f,  0.000f), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-0.471f, -0.333f, -0.816f), glm::vec3(1, 0, 1)),

			// Face 4
			VertexFormat(glm::vec3(-0.471f, -0.333f, -0.816f), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3( 0.000f,  1.000f,  0.000f), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3( 0.943f, -0.333f,  0.000f), glm::vec3(0, 1, 1)),

		};

		vector<GLuint> indices = {
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11
		};

		CreateMesh("full_color", vertices, indices);
	}
}


void Lab2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<GLuint> &indices)
{
	GLuint VAO = 0;
	// TODO(student): Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO = 0;
	// TODO(student): Create the VBO and bind it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO(student): Send vertices data into the VBO buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices[0]) * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW
	);

	GLuint IBO = 0;
	// TODO(student): Create the IBO and bind it
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO(student): Send indices data into the IBO buffer
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices[0]) * indices.size(),
		&indices[0],
		GL_STATIC_DRAW
	);

	// ========================================================================
	// This section demonstrates how the GPU vertex shader program
	// receives data. It will be learned later, when GLSL shaders will be
	// introduced. For the moment, just think that each property value from
	// our vertex format needs to be sent to a certain channel, in order to
	// know how to receive it in the GLSL vertex shader.

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO(student): Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
		cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
	}

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<GLuint>(indices.size()));
}


void Lab2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Lab2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// TODO(student): Enable face culling
	glEnable(GL_CULL_FACE);

	// TODO(student): Set face custom culling. Use the `cullFace` variable.
	glCullFace(cullFace);

	// Render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -3.5f), glm::vec3(0.75f));

	// Render an object using colors from vertex
	glm::mat4 mesh_matrix = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-3.5f, 0.5f, 0)), glm::vec3(0.25f));
	GLfloat var = Engine::GetElapsedTime();
	RenderSimpleMesh(meshes["cube_A"], shaders["TestShader"], mesh_matrix, glm::vec3(sin(2 * var + AI_MATH_PI) / 2 + 0.5));

	// TODO(student): Draw the mesh that was created with `CreateMesh()`
	RenderMesh(meshes["cube_B"], shaders["VertexColor"], glm::vec3(3.5f, 0.5f, 0), glm::vec3(0.25f));

	// TODO(student): Draw the tetrahedron
	RenderMesh(meshes["tetra"], shaders["VertexColor"], glm::vec3(0, 0, 0), glm::vec3(1));

	// TODO(student): Draw the square
	RenderMesh(meshes["square"], shaders["VertexColor"], glm::vec3(0, 5.5f, 0), glm::vec3(1));

	// Bonus
	RenderMesh(meshes["full_color"], shaders["VertexColor"], glm::vec3(0, 0.5f, 5));
	RenderMesh(meshes["dodecahedron"], shaders["VertexColor"], glm::vec3(-10, 0, -10));
	RenderMesh(meshes["twelve"], shaders["VertexColor"], glm::vec3(10, 0, -10));

	// TODO(student): Disable face culling
	glDisable(GL_CULL_FACE);
}


void Lab2::FrameEnd()
{
	DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab2::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab2::OnKeyPress(int key, int mods)
{
	// TODO(student): Switch between GL_FRONT and GL_BACK culling.
	// Save the state in `cullFace` variable and apply it in the
	// `Update()` method, NOT here!

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}

	if (key == GLFW_KEY_F2)
	{
		switch (cullFace)
		{
		case GL_FRONT:
			cullFace = GL_BACK;
			break;
		default:
			cullFace = GL_FRONT;
			break;
		}
	}
}


void Lab2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Lab2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Lab2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Lab2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Lab2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab2::OnWindowResize(int width, int height)
{
}


void Lab2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(0))
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint loc_object_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc_object_color, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}
