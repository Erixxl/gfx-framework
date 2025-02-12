#include "shaders.hpp"


using namespace std;
using namespace hw2_shaders;


void hw2_shaders::InitProjectShaders(unordered_map<string, Shader*>& shaders, string path)
{
	// Ground shader
	{
		Shader* shader = new Shader("GroundShader");
		shader->AddShader(PATH_JOIN(path, "ground.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "ground.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Drone shader
	{
		Shader* shader = new Shader("DroneShader");
		shader->AddShader(PATH_JOIN(path, "drone.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "drone.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Collision shader
	{
		Shader* shader = new Shader("CollisionShader");
		shader->AddShader(PATH_JOIN(path, "collision.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "collision.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Tree shader
	{
		Shader* shader = new Shader("TreeShader");
		shader->AddShader(PATH_JOIN(path, "tree.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "tree.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Building shader
	{
		Shader* shader = new Shader("HouseShader");
		shader->AddShader(PATH_JOIN(path, "house.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "house.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Gate shader
	{
		Shader* shader = new Shader("GateShader");
		shader->AddShader(PATH_JOIN(path, "gate.vert"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(path, "gate.frag"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}
