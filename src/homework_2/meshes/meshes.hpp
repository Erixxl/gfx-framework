#pragma once


#include "components/simple_scene.h"


using namespace std;


namespace hw2_meshes
{
	void InsertNewMesh(vector<VertexFormat> vertices, vector<GLuint> indices, string name, unordered_map<string, Mesh*>& meshes);
	void InitProjectMeshes(unordered_map<string, Mesh*>& meshes);
}
