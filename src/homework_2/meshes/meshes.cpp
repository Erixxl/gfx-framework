#include "homework_2/meshes/meshes.hpp"


using namespace std;
using namespace hw2_meshes;


void hw2_meshes::InsertNewMesh(vector<VertexFormat> vertices, vector<GLuint> indices, string name, unordered_map<string, Mesh*>& meshes)
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
}


void hw2_meshes::InitProjectMeshes(unordered_map<string, Mesh*>& meshes)
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

			VertexFormat(glm::vec3(-45, 0, -45)),
			VertexFormat(glm::vec3(-35, 0, -45)),
			VertexFormat(glm::vec3(-25, 0, -45)),
			VertexFormat(glm::vec3(-15, 0, -45)),
			VertexFormat(glm::vec3( -5, 0, -45)),
			VertexFormat(glm::vec3(  5, 0, -45)),
			VertexFormat(glm::vec3( 15, 0, -45)),
			VertexFormat(glm::vec3( 25, 0, -45)),
			VertexFormat(glm::vec3( 35, 0, -45)),
			VertexFormat(glm::vec3( 45, 0, -45)),

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

			VertexFormat(glm::vec3(-45, 0, -35)),
			VertexFormat(glm::vec3(-35, 0, -35)),
			VertexFormat(glm::vec3(-25, 0, -35)),
			VertexFormat(glm::vec3(-15, 0, -35)),
			VertexFormat(glm::vec3( -5, 0, -35)),
			VertexFormat(glm::vec3(  5, 0, -35)),
			VertexFormat(glm::vec3( 15, 0, -35)),
			VertexFormat(glm::vec3( 25, 0, -35)),
			VertexFormat(glm::vec3( 35, 0, -35)),
			VertexFormat(glm::vec3( 45, 0, -35)),

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

			VertexFormat(glm::vec3(-45, 0, -25)),
			VertexFormat(glm::vec3(-35, 0, -25)),
			VertexFormat(glm::vec3(-25, 0, -25)),
			VertexFormat(glm::vec3(-15, 0, -25)),
			VertexFormat(glm::vec3( -5, 0, -25)),
			VertexFormat(glm::vec3(  5, 0, -25)),
			VertexFormat(glm::vec3( 15, 0, -25)),
			VertexFormat(glm::vec3( 25, 0, -25)),
			VertexFormat(glm::vec3( 35, 0, -25)),
			VertexFormat(glm::vec3( 45, 0, -25)),

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

			VertexFormat(glm::vec3(-45, 0, -15)),
			VertexFormat(glm::vec3(-35, 0, -15)),
			VertexFormat(glm::vec3(-25, 0, -15)),
			VertexFormat(glm::vec3(-15, 0, -15)),
			VertexFormat(glm::vec3( -5, 0, -15)),
			VertexFormat(glm::vec3(  5, 0, -15)),
			VertexFormat(glm::vec3( 15, 0, -15)),
			VertexFormat(glm::vec3( 25, 0, -15)),
			VertexFormat(glm::vec3( 35, 0, -15)),
			VertexFormat(glm::vec3( 45, 0, -15)),

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

			VertexFormat(glm::vec3(-45, 0,  -5)),
			VertexFormat(glm::vec3(-35, 0,  -5)),
			VertexFormat(glm::vec3(-25, 0,  -5)),
			VertexFormat(glm::vec3(-15, 0,  -5)),
			VertexFormat(glm::vec3( -5, 0,  -5)),
			VertexFormat(glm::vec3(  5, 0,  -5)),
			VertexFormat(glm::vec3( 15, 0,  -5)),
			VertexFormat(glm::vec3( 25, 0,  -5)),
			VertexFormat(glm::vec3( 35, 0,  -5)),
			VertexFormat(glm::vec3( 45, 0,  -5)),

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

			VertexFormat(glm::vec3(-45, 0,   5)),
			VertexFormat(glm::vec3(-35, 0,   5)),
			VertexFormat(glm::vec3(-25, 0,   5)),
			VertexFormat(glm::vec3(-15, 0,   5)),
			VertexFormat(glm::vec3( -5, 0,   5)),
			VertexFormat(glm::vec3(  5, 0,   5)),
			VertexFormat(glm::vec3( 15, 0,   5)),
			VertexFormat(glm::vec3( 25, 0,   5)),
			VertexFormat(glm::vec3( 35, 0,   5)),
			VertexFormat(glm::vec3( 45, 0,   5)),

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

			VertexFormat(glm::vec3(-45, 0,  15)),
			VertexFormat(glm::vec3(-35, 0,  15)),
			VertexFormat(glm::vec3(-25, 0,  15)),
			VertexFormat(glm::vec3(-15, 0,  15)),
			VertexFormat(glm::vec3( -5, 0,  15)),
			VertexFormat(glm::vec3(  5, 0,  15)),
			VertexFormat(glm::vec3( 15, 0,  15)),
			VertexFormat(glm::vec3( 25, 0,  15)),
			VertexFormat(glm::vec3( 35, 0,  15)),
			VertexFormat(glm::vec3( 45, 0,  15)),

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

			VertexFormat(glm::vec3(-45, 0,  25)),
			VertexFormat(glm::vec3(-35, 0,  25)),
			VertexFormat(glm::vec3(-25, 0,  25)),
			VertexFormat(glm::vec3(-15, 0,  25)),
			VertexFormat(glm::vec3( -5, 0,  25)),
			VertexFormat(glm::vec3(  5, 0,  25)),
			VertexFormat(glm::vec3( 15, 0,  25)),
			VertexFormat(glm::vec3( 25, 0,  25)),
			VertexFormat(glm::vec3( 35, 0,  25)),
			VertexFormat(glm::vec3( 45, 0,  25)),

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

			VertexFormat(glm::vec3(-45, 0,  35)),
			VertexFormat(glm::vec3(-35, 0,  35)),
			VertexFormat(glm::vec3(-25, 0,  35)),
			VertexFormat(glm::vec3(-15, 0,  35)),
			VertexFormat(glm::vec3( -5, 0,  35)),
			VertexFormat(glm::vec3(  5, 0,  35)),
			VertexFormat(glm::vec3( 15, 0,  35)),
			VertexFormat(glm::vec3( 25, 0,  35)),
			VertexFormat(glm::vec3( 35, 0,  35)),
			VertexFormat(glm::vec3( 45, 0,  35)),

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

			VertexFormat(glm::vec3(-45, 0,  45)),
			VertexFormat(glm::vec3(-35, 0,  45)),
			VertexFormat(glm::vec3(-25, 0,  45)),
			VertexFormat(glm::vec3(-15, 0,  45)),
			VertexFormat(glm::vec3( -5, 0,  45)),
			VertexFormat(glm::vec3(  5, 0,  45)),
			VertexFormat(glm::vec3( 15, 0,  45)),
			VertexFormat(glm::vec3( 25, 0,  45)),
			VertexFormat(glm::vec3( 35, 0,  45)),
			VertexFormat(glm::vec3( 45, 0,  45)),

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
			0, 11, 1, 1, 12, 2, 2, 13, 3, 3, 14, 4, 4, 15, 5, 5, 16, 6, 6, 17, 7, 7, 18, 8, 8, 19, 9, 9, 20, 10,
			0, 21, 11, 1, 22, 12, 2, 23, 13, 3, 24, 14, 4, 25, 15, 5, 26, 16, 6, 27, 17, 7, 28, 18, 8, 29, 19, 9, 30, 20,
			21, 22, 11, 22, 23, 12, 23, 24, 13, 24, 25, 14, 25, 26, 15, 26, 27, 16, 27, 28, 17, 28, 29, 18, 29, 30, 19, 30, 31, 20,
			1, 11, 22, 2, 12, 23, 3, 13, 24, 4, 14, 25, 5, 15, 26, 6, 16, 27, 7, 17, 28, 8, 18, 29, 9, 19, 30, 10, 20, 31,

			21, 32, 22, 22, 33, 23, 23, 34, 24, 24, 35, 25, 25, 36, 26, 26, 37, 27, 27, 38, 28, 28, 39, 29, 29, 40, 30, 30, 41, 31,
			21, 42, 32, 22, 43, 33, 23, 44, 34, 24, 45, 35, 25, 46, 36, 26, 47, 37, 27, 48, 38, 28, 49, 39, 29, 50, 40, 30, 51, 41,
			42, 43, 32, 43, 44, 33, 44, 45, 34, 45, 46, 35, 46, 47, 36, 47, 48, 37, 48, 49, 38, 49, 50, 39, 50, 51, 40, 51, 52, 41,
			22, 32, 43, 23, 33, 44, 24, 34, 45, 25, 35, 46, 26, 36, 47, 27, 37, 48, 28, 38, 49, 29, 39, 50, 30, 40, 51, 31, 41, 52,

			42, 53, 43, 43, 54, 44, 44, 55, 45, 45, 56, 46, 46, 57, 47, 47, 58, 48, 48, 59, 49, 49, 60, 50, 50, 61, 51, 51, 62, 52,
			42, 63, 53, 43, 64, 54, 44, 65, 55, 45, 66, 56, 46, 67, 57, 47, 68, 58, 48, 69, 59, 49, 70, 60, 50, 71, 61, 51, 72, 62,
			63, 64, 53, 64, 65, 54, 65, 66, 55, 66, 67, 56, 67, 68, 57, 68, 69, 58, 69, 70, 59, 70, 71, 60, 71, 72, 61, 72, 73, 62,
			43, 53, 64, 44, 54, 65, 45, 55, 66, 46, 56, 67, 47, 57, 68, 48, 58, 69, 49, 59, 70, 50, 60, 71, 51, 61, 72, 52, 62, 73,

			63, 74, 64, 64, 75, 65, 65, 76, 66, 66, 77, 67, 67, 78, 68, 68, 79, 69, 69, 80, 70, 70, 81, 71, 71, 82, 72, 72, 83, 73,
			63, 84, 74, 64, 85, 75, 65, 86, 76, 66, 87, 77, 67, 88, 78, 68, 89, 79, 69, 90, 80, 70, 91, 81, 71, 92, 82, 72, 93, 83,
			84, 85, 74, 85, 86, 75, 86, 87, 76, 87, 88, 77, 88, 89, 78, 89, 90, 79, 90, 91, 80, 91, 92, 81, 92, 93, 82, 93, 94, 83,
			64, 74, 85, 65, 75, 86, 66, 76, 87, 67, 77, 88, 68, 78, 89, 69, 79, 90, 70, 80, 91, 71, 81, 92, 72, 82, 93, 73, 83, 94,

			84, 95, 85, 85, 96, 86, 86, 97, 87, 87, 98, 88, 88, 99, 89, 89, 100, 90, 90, 101, 91, 91, 102, 92, 92, 103, 93, 93, 104, 94,
			84, 105, 95, 85, 106, 96, 86, 107, 97, 87, 108, 98, 88, 109, 99, 89, 110, 100, 90, 111, 101, 91, 112, 102, 92, 113, 103, 93, 114, 104,
			105, 106, 95, 106, 107, 96, 107, 108, 97, 108, 109, 98, 109, 110, 99, 110, 111, 100, 111, 112, 101, 112, 113, 102, 113, 114, 103, 114, 115, 104,
			85, 95, 106, 86, 96, 107, 87, 97, 108, 88, 98, 109, 89, 99, 110, 90, 100, 111, 91, 101, 112, 92, 102, 113, 93, 103, 114, 94, 104, 115,

			105, 116, 106, 106, 117, 107, 107, 118, 108, 108, 119, 109, 109, 120, 110, 110, 121, 111, 111, 122, 112, 112, 123, 113, 113, 124, 114, 114, 125, 115,
			105, 126, 116, 106, 127, 117, 107, 128, 118, 108, 129, 119, 109, 130, 120, 110, 131, 121, 111, 132, 122, 112, 133, 123, 113, 134, 124, 114, 135, 125,
			126, 127, 116, 127, 128, 117, 128, 129, 118, 129, 130, 119, 130, 131, 120, 131, 132, 121, 132, 133, 122, 133, 134, 123, 134, 135, 124, 135, 136, 125,
			106, 116, 127, 107, 117, 128, 108, 118, 129, 109, 119, 130, 110, 120, 131, 111, 121, 132, 112, 122, 133, 113, 123, 134, 114, 124, 135, 115, 125, 136,
		};

		InsertNewMesh(vertices, indices, "ground", meshes);
	}

	// Default drone mesh
	{
		glm::vec3 dark = glm::vec3(175.0 / 255.0, 23.0 / 255.0, 64.0 / 255.0);
		glm::vec3 darker = glm::vec3(116.0 / 255.0, 9.0 / 255.0, 56.0 / 255.0);
		glm::vec3 light = glm::vec3(204.0 / 255.0, 43.0 / 255.0, 82.0 / 255.0);

		vector<VertexFormat> vertices = {
			// Upper region
			VertexFormat(glm::vec3(10, 0.99, 1), dark), // 0
			VertexFormat(glm::vec3(10, 0.99, -1), dark),
			VertexFormat(glm::vec3(-10, 0.99, -1), dark),
			VertexFormat(glm::vec3(-10, 0.99, 1), dark),
			VertexFormat(glm::vec3(-1, 0.99, 10), dark),
			VertexFormat(glm::vec3(1, 0.99, 10), dark),
			VertexFormat(glm::vec3(1, 0.99, -10), dark),
			VertexFormat(glm::vec3(-1, 0.99, -10), dark),

			// Lower region
			VertexFormat(glm::vec3(10, -1.01, 1), dark), // 8
			VertexFormat(glm::vec3(10, -1.01, -1), dark),
			VertexFormat(glm::vec3(-10, -1.01, -1), dark),
			VertexFormat(glm::vec3(-10, -1.01, 1), dark),
			VertexFormat(glm::vec3(-1, -1.01, 10), dark),
			VertexFormat(glm::vec3(1, -1.01, 10), dark),
			VertexFormat(glm::vec3(1, -1.01, -10), dark),
			VertexFormat(glm::vec3(-1, -1.01, -10), dark),

			// Right rotor

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

			// Left rotor

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

			// Right spinning blades
			VertexFormat(glm::vec3(0 + 9, 1.01, 1), darker), // 144
			VertexFormat(glm::vec3(0 + 9, 1.01, -1), darker),
			VertexFormat(glm::vec3(0 + 9, 1.99, -1), darker),
			VertexFormat(glm::vec3(0 + 9, 1.99, 1), darker),
			VertexFormat(glm::vec3(0.01 + 9, 1.01, 1), light),
			VertexFormat(glm::vec3(-0.01 + 9, 1.01, -1), light),
			VertexFormat(glm::vec3(0.01 + 9, 1.99, -1), light),
			VertexFormat(glm::vec3(-0.01 + 9, 1.99, 1), light),
			VertexFormat(glm::vec3(4.5 + 9, 1.01, 1), light),
			VertexFormat(glm::vec3(-4.5 + 9, 1.01, -1), light),
			VertexFormat(glm::vec3(4.5 + 9, 1.99, -1), light),
			VertexFormat(glm::vec3(-4.5 + 9, 1.99, 1), light),

			// Left spinning blades
			VertexFormat(glm::vec3(0 - 9, 1.01, 1), darker), // 156
			VertexFormat(glm::vec3(0 - 9, 1.01, -1), darker),
			VertexFormat(glm::vec3(0 - 9, 1.99, -1), darker),
			VertexFormat(glm::vec3(0 - 9, 1.99, 1), darker),
			VertexFormat(glm::vec3(0.01 - 9, 1.01, 1), light),
			VertexFormat(glm::vec3(-0.01 - 9, 1.01, -1), light),
			VertexFormat(glm::vec3(0.01 - 9, 1.99, -1), light),
			VertexFormat(glm::vec3(-0.01 - 9, 1.99, 1), light),
			VertexFormat(glm::vec3(4.5 - 9, 1.01, 1), light),
			VertexFormat(glm::vec3(-4.5 - 9, 1.01, -1), light),
			VertexFormat(glm::vec3(4.5 - 9, 1.99, -1), light),
			VertexFormat(glm::vec3(-4.5 - 9, 1.99, 1), light),

			// Front spinning blades
			VertexFormat(glm::vec3(1, 1.01, 0 + 9), darker), // 168
			VertexFormat(glm::vec3(-1, 1.01, 0 + 9), darker),
			VertexFormat(glm::vec3(-1, 1.99, 0 + 9), darker),
			VertexFormat(glm::vec3(1, 1.99, 0 + 9), darker),
			VertexFormat(glm::vec3(1, 1.01, 0.01 + 9), light),
			VertexFormat(glm::vec3(-1, 1.01, -0.01 + 9), light),
			VertexFormat(glm::vec3(-1, 1.99, 0.01 + 9), light),
			VertexFormat(glm::vec3(1, 1.99, -0.01 + 9), light),
			VertexFormat(glm::vec3(1, 1.01, 4.5 + 9), light),
			VertexFormat(glm::vec3(-1, 1.01, -4.5 + 9), light),
			VertexFormat(glm::vec3(-1, 1.99, 4.5 + 9), light),
			VertexFormat(glm::vec3(1, 1.99, -4.5 + 9), light),

			// Back spinning blades
			VertexFormat(glm::vec3(1, 1.01, 0 - 9), darker), // 180
			VertexFormat(glm::vec3(-1, 1.01, 0 - 9), darker),
			VertexFormat(glm::vec3(-1, 1.99, 0 - 9), darker),
			VertexFormat(glm::vec3(1, 1.99, 0 - 9), darker),
			VertexFormat(glm::vec3(1, 1.01, 0.01 - 9), light),
			VertexFormat(glm::vec3(-1, 1.01, -0.01 - 9), light),
			VertexFormat(glm::vec3(-1, 1.99, 0.01 - 9), light),
			VertexFormat(glm::vec3(1, 1.99, -0.01 - 9), light),
			VertexFormat(glm::vec3(1, 1.01, 4.5 - 9), light),
			VertexFormat(glm::vec3(-1, 1.01, -4.5 - 9), light),
			VertexFormat(glm::vec3(-1, 1.99, 4.5 - 9), light),
			VertexFormat(glm::vec3(1, 1.99, -4.5 - 9), light),
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

			// Right rotor
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

			// Left rotor
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

			// Details
			4 + 80, 5 + 80, 12 + 80, 4 + 80, 12 + 80, 13 + 80,
			20 + 80, 21 + 80, 28 + 80, 20 + 80, 28 + 80, 29 + 80,

			4 + 112, 5 + 112, 12 + 112, 4 + 112, 12 + 112, 13 + 112,
			20 + 112, 21 + 112, 28 + 112, 20 + 112, 28 + 112, 29 + 112,

			0 + 16, 1 + 16, 8 + 16, 0 + 16, 8 + 16, 9 + 16,
			16 + 16, 17 + 16, 24 + 16, 16 + 16, 24 + 16, 25 + 16,

			0 + 48, 1 + 48, 8 + 48, 0 + 48, 8 + 48, 9 + 48,
			16 + 48, 17 + 48, 24 + 48, 16 + 48, 24 + 48, 25 + 48,

			// Right spinning blade
			0 + 144, 1 + 144, 2 + 144, 0 + 144, 2 + 144, 3 + 144,
			4 + 144, 8 + 144, 10 + 144, 4 + 144, 10 + 144, 6 + 144,
			5 + 144, 9 + 144, 11 + 144, 5 + 144, 11 + 144, 7 + 144,

			// Left spinning blade
			0 + 156, 1 + 156, 2 + 156, 0 + 156, 2 + 156, 3 + 156,
			4 + 156, 8 + 156, 10 + 156, 4 + 156, 10 + 156, 6 + 156,
			5 + 156, 9 + 156, 11 + 156, 5 + 156, 11 + 156, 7 + 156,

			// Front spinning blade
			0 + 168, 1 + 168, 2 + 168, 0 + 168, 2 + 168, 3 + 168,
			4 + 168, 8 + 168, 10 + 168, 4 + 168, 10 + 168, 6 + 168,
			5 + 168, 9 + 168, 11 + 168, 5 + 168, 11 + 168, 7 + 168,

			// Back spinning blade
			0 + 180, 1 + 180, 2 + 180, 0 + 180, 2 + 180, 3 + 180,
			4 + 180, 8 + 180, 10 + 180, 4 + 180, 10 + 180, 6 + 180,
			5 + 180, 9 + 180, 11 + 180, 5 + 180, 11 + 180, 7 + 180,

		};

		InsertNewMesh(vertices, indices, "red_drone", meshes);
	}

	// Drone collision box
	{
		vector<VertexFormat> vertices = {
			VertexFormat(glm::vec3(14.01, 2.01, 14.01)),
			VertexFormat(glm::vec3(14.01, 2.01, -14.01)),
			VertexFormat(glm::vec3(-14.01, 2.01, -14.01)),
			VertexFormat(glm::vec3(-14.01, 2.01, 14.01)),

			VertexFormat(glm::vec3(14.01, -1.02, 14.01)),
			VertexFormat(glm::vec3(14.01, -1.02, -14.01)),
			VertexFormat(glm::vec3(-14.01, -1.02, -14.01)),
			VertexFormat(glm::vec3(-14.01, -1.02, 14.01)),
		};

		vector<GLuint> indices = {
			0, 1, 2, 0, 2, 3,
			0, 1, 5, 0, 5, 4,
			1, 2, 6, 1, 6, 5,
			2, 3, 7, 2, 7, 6,
			3, 0, 4, 3, 4, 7,
			4, 5, 6, 4, 6, 7,
		};

		InsertNewMesh(vertices, indices, "drone_collision_box", meshes);
	}
}


