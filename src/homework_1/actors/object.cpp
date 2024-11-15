#include "homework_1/actors/object.h"


using namespace glm;
using namespace std;
using namespace actors;


Object::Object()
	: Object(DEFAULT_OBJ)
{
}


Object::Object(ObjectType _type)
	: type(_type)
	, objectMesh(nullptr)
	, posMatrix(mat3(1))
	, rotMatrix(mat3(1))
	, sclMatrix(mat3(1))
{
}


void Object::TankMeshSetup(TankColor color, GLuint team, GLuint index)
{
	ColorPicker objColor = ColorPicker(color);
	vector<VertexFormat> vertices = vector<VertexFormat>();
	vector<GLuint> indices = vector<GLuint>();

	switch (type)
	{
	case TANK_BODY:
		objectMesh = new Mesh("tank_body_" + to_string(team) + "_" + objColor.name);

		vertices = {
			// Tank track
			VertexFormat(vec3(3, 0, 0), objColor.second),
			VertexFormat(vec3(4, 1, 0), objColor.second),
			VertexFormat(vec3(-4, 1, 0), objColor.second),
			VertexFormat(vec3(-3, 0, 0), objColor.second),

			// Tank hull
			VertexFormat(vec3(6, 1, 0), objColor.main),
			VertexFormat(vec3(4, 3, 0), objColor.main),
			VertexFormat(vec3(-4, 3, 0), objColor.main),
			VertexFormat(vec3(-6, 1, 0), objColor.main),

			// Tank cupola
			VertexFormat(vec3(0, 4, 0), objColor.main),
			VertexFormat(vec3(cos(0 * AI_MATH_PI / 20), 4 + sin(0 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(1 * AI_MATH_PI / 20), 4 + sin(1 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(2 * AI_MATH_PI / 20), 4 + sin(2 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(3 * AI_MATH_PI / 20), 4 + sin(3 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(4 * AI_MATH_PI / 20), 4 + sin(4 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(5 * AI_MATH_PI / 20), 4 + sin(5 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(6 * AI_MATH_PI / 20), 4 + sin(6 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(7 * AI_MATH_PI / 20), 4 + sin(7 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(8 * AI_MATH_PI / 20), 4 + sin(8 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(9 * AI_MATH_PI / 20), 4 + sin(9 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(10 * AI_MATH_PI / 20), 4 + sin(10 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(11 * AI_MATH_PI / 20), 4 + sin(11 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(12 * AI_MATH_PI / 20), 4 + sin(12 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(13 * AI_MATH_PI / 20), 4 + sin(13 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(14 * AI_MATH_PI / 20), 4 + sin(14 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(15 * AI_MATH_PI / 20), 4 + sin(15 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(16 * AI_MATH_PI / 20), 4 + sin(16 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(17 * AI_MATH_PI / 20), 4 + sin(17 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(18 * AI_MATH_PI / 20), 4 + sin(18 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(19 * AI_MATH_PI / 20), 4 + sin(19 * AI_MATH_PI / 20), 0), objColor.main),
			VertexFormat(vec3(cos(20 * AI_MATH_PI / 20), 4 + sin(20 * AI_MATH_PI / 20), 0), objColor.main),
		};

		indices = {
			// Tank trail
			0, 1, 2, 0, 2, 3,

			// Tank hull
			4, 5, 6, 4, 6, 7,

			// Tank cupola
			9, 10, 11, 9, 11, 12,
			9, 12, 13, 9, 13, 14,
			9, 14, 15, 9, 15, 16,
			9, 16, 17, 9, 17, 18,
			9, 18, 19, 9, 19, 20,
			9, 20, 21, 9, 21, 22,
			9, 22, 23, 9, 23, 24,
			9, 24, 25, 9, 25, 26,
			9, 26, 27, 9, 27, 28,
			9, 28, 29, 9, 29, 30
		};

		posMatrix = mat3(1);
		rotMatrix = mat3(1);
		sclMatrix = mat3(1);

		objectMesh->SetDrawMode(GL_TRIANGLES);
		objectMesh->InitFromData(vertices, indices);

		break;

	case TANK_BARREL:
		objectMesh = new Mesh("tank_barrel_" + objColor.name);

		vertices = {
			VertexFormat(vec3(1, 0, 0), objColor.second),
			VertexFormat(vec3(1, 8, 0), objColor.second),
			VertexFormat(vec3(-1, 8, 0), objColor.second),
			VertexFormat(vec3(-1, 0, 0), objColor.second)
		};

		indices = {
			0, 1, 2, 0, 2, 3
		};

		posMatrix = mat3(1);
		rotMatrix = mat3(1);
		sclMatrix = utils::Scale(0.5, 0.5);

		objectMesh->SetDrawMode(GL_TRIANGLES);
		objectMesh->InitFromData(vertices, indices);

		break;

	case TANK_TRAIL:
		objectMesh = new Mesh("tank_trail_" + objColor.name + "_" + to_string(index));

		vertices = {
			VertexFormat(vec3(0, 0, 0), objColor.second),
			VertexFormat(vec3(1, 0, 0), objColor.second),
		};

		indices = {
			0, 1
		};

		posMatrix = mat3(1);
		rotMatrix = mat3(1);
		sclMatrix = mat3(1);

		objectMesh->SetDrawMode(GL_LINES);
		objectMesh->InitFromData(vertices, indices);

		break;

	case TANK_LIFEBAR:
		objectMesh = new Mesh("tank_lifebar_" + objColor.name);

		vertices = {
			VertexFormat(vec3(0, 0, 0), objColor.main),
			VertexFormat(vec3(1, 0, 0), objColor.main),
			VertexFormat(vec3(1, 1, 0), objColor.main),
			VertexFormat(vec3(0, 1, 0), objColor.main),
		};

		indices = {
			0, 1, 2, 0, 2, 3
		};

		objectMesh->SetDrawMode(GL_TRIANGLES);
		objectMesh->InitFromData(vertices, indices);

		break;
	}
}

