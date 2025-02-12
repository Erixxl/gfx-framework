#include "homework_2/homework2.hpp"


using namespace std;
using namespace hw2;


Homework2::Homework2()
{
	// Class variables initialization
	polygon_mode = GL_FILL;
	blade_speed = 7;
	blade_angle = 0;

	drone_position = glm::vec3(0, 10, 0);
	drone_rotation = glm::mat4(1);
	drone_matrix = glm::translate(glm::mat4(1), drone_position);
	drone_matrix = glm::scale(drone_matrix, glm::vec3(1.0 / 40.0));
	drone_velocity = glm::vec3(0, 0, 0);
	drone_acceleration = gravity;
	drone_angle = 0;


	drone_camera = new hw2_utils::Camera();
	drone_camera->Set(drone_position + glm::vec3(0, 1, -2), drone_position, glm::vec3(0, 1, 0));
	scene_camera = new hw2_utils::Camera();
	scene_camera->Set(glm::vec3(0), glm::vec3(0), glm::vec3(0, 1, 0));

	forward = glm::normalize(glm::vec3(drone_camera->forward.x, 0, drone_camera->forward.z));
	right = drone_camera->right;

	debug = true;
	enable_boxes = false;
	running = true;
}


Homework2::~Homework2()
{

}


void Homework2::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	hw2_meshes::InitProjectMeshes(meshes);
	hw2_shaders::InitProjectShaders(shaders, PATH_JOIN(window->props.selfDir, "src", "homework_2", "shaders"));

	buildings = vector<glm::mat4>(3, glm::mat4(1));
	trees = vector<glm::mat4>(5, glm::mat4(1));
	gates = vector<glm::mat4>(3, glm::mat4(1));
	gate_status = vector<GLuint>(3, 0);

	building_radius = 2.5;
	tree_radius = 2.0;
	gate_radius = 2.0;

	for (int i = 0; i < 3; ++i)
	{
		buildings[i] = glm::translate(
			glm::rotate(
				glm::mat4(1),
				angle_list[rand_val() % 5],
				glm::vec3(0, 1, 0)
			),
			glm::vec3(-30, 0, i * 10)
		);
	}

	for (int i = 0; i < 5; ++i)
	{
		trees[i] = glm::translate(
			glm::rotate(
				glm::mat4(1),
				angle_list[rand_val() % 4],
				glm::vec3(0, 1, 0)
			),
			glm::vec3(20 + rand_val() % 10, 0, i * 10)
		);
	}

	for (int i = 0; i < 3; ++i)
	{
		pair<GLfloat, GLfloat> pos = possible_places[rand_val() % 5];

		gates[i] = glm::translate(
			glm::rotate(
				glm::mat4(1),
				angle_list[rand_val() % 4],
				glm::vec3(0, 1, 0)
			),
			glm::vec3(pos.first, 6, pos.second)
		);

		gate_status[i] = i;
	}
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
	if (!running)
	{
		return;
	}

	glEnable(GL_CULL_FACE);
	blade_angle += blade_speed * deltaTimeSeconds;

	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

	drone_matrix = glm::translate(drone_rotation, drone_position);
	drone_matrix = glm::scale(drone_matrix, glm::vec3(1.0 / 40.0));

	glm::mat4 tree_mat = glm::translate(glm::mat4(1), glm::vec3(10, 0, 0));
	glm::mat4 house_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	glm::mat4 gate_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0, 10));

	RenderSimpleMesh(meshes["ground"], shaders["GroundShader"], glm::scale(glm::mat4(1), glm::vec3(1)), 0, drone_camera->position);

	glDisable(GL_CULL_FACE);

	RenderSimpleMesh(meshes["red_drone"], shaders["DroneShader"], drone_matrix, blade_angle, glm::vec3(drone_camera->distanceToTarget));

	for (int i = 0; i < 3; ++i)
	{
		RenderSimpleMesh(
			meshes["gate"],
			shaders["GateShader"],
			gates[i],
			gate_status[i],
			drone_camera->position
		);
	}

	glEnable(GL_CULL_FACE);

	for (int i = 0; i < 5; ++i)
	{
		RenderSimpleMesh(
			meshes["pine_tree"],
			shaders["TreeShader"],
			trees[i],
			0,
			drone_camera->position
		);
	}

	for (int i = 0; i < 3; ++i)
	{
		RenderSimpleMesh(
			meshes["house"],
			shaders["HouseShader"],
			buildings[i],
			0,
			drone_camera->position
		);
	}

	glDisable(GL_CULL_FACE);
}


void Homework2::FrameEnd()
{

}


void Homework2::OnInputUpdate(float deltaTime, int mods)
{
	GLfloat step = 300.0f * deltaTime;
	glm::vec3 new_position = drone_position;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_W))
		{
			new_position += forward * (deltaTime * step);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->MoveForward(deltaTime * step);
			drone_position = new_position;
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			new_position += right * (-1 * deltaTime * step);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->TranslateRight(-1 * deltaTime * step);
			drone_position = new_position;
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			new_position += forward * (-1 * deltaTime * step);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->MoveForward(-1 * deltaTime * step);
			drone_position = new_position;
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			new_position += right * (deltaTime * step);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->TranslateRight(deltaTime * step);
			drone_position = new_position;
		}

		if (window->KeyHold(GLFW_KEY_Q))
		{
			new_position += glm::vec3(0, deltaTime * step, 0);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->position += glm::vec3(0, deltaTime * step, 0);
			drone_position = new_position;
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
			new_position += glm::vec3(0, -1 * deltaTime * step, 0);

			if (CollisionCheck(new_position))
			{
				return;
			}

			drone_camera->position += glm::vec3(0, -1 * deltaTime * step, 0);
			drone_position = new_position;
		}
	}
}


void Homework2::OnKeyPress(int key, int mods)
{
	// For debugging purposes
	if (key == GLFW_KEY_SPACE && debug)
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

	if (key == GLFW_KEY_X && debug)
	{
		enable_boxes = !enable_boxes;
	}

	if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S ||
		key == GLFW_KEY_D || key == GLFW_KEY_Q || key == GLFW_KEY_E)
	{
		blade_speed *= 4;
	}
}


void Homework2::OnKeyRelease(int key, int mods)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S ||
		key == GLFW_KEY_D || key == GLFW_KEY_Q || key == GLFW_KEY_E)
	{
		blade_speed /= 4;
	}
}


void Homework2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensitivityOX = 0.001f;
		float sensitivityOY = 0.001f;

		drone_camera->RotateThirdPerson_OY(-deltaX * sensitivityOX);
		drone_camera->RotateThirdPerson_OX(-deltaY * sensitivityOY);

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0), deltaX * sensitivityOX, glm::vec3(0.0, 1.0, 0.0));

		forward = glm::normalize(glm::vec3(drone_camera->forward.x, 0, drone_camera->forward.z));
		right = drone_camera->right;
	}
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


void Homework2::RenderSimpleMesh(Mesh* mesh, Shader* shader, glm::mat4 modelMatrix, GLfloat fAux, glm::vec3 vecAux)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	glUseProgram(shader->program);

	GLint locModel = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint locView = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(drone_camera->GetViewMatrix()));

	GLint locProjection = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));

	GLint locFloatAux = glGetUniformLocation(shader->program, "v_float_aux");
	glUniform1f(locFloatAux, fAux);

	GLint locVecAux = glGetUniformLocation(shader->program, "v_vec_aux");
	glUniform3fv(locVecAux, 1, glm::value_ptr(vecAux));

	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Homework2::UpdateDronePosition(float deltaTimeSeconds)
{
	float acc_mod = 0.5f;
	float vel_mod = 1.0f;

	glm::vec3 old_position = drone_position;

	drone_velocity += acc_mod * deltaTimeSeconds * drone_acceleration;
	drone_position += vel_mod * deltaTimeSeconds * drone_velocity;
}

bool Homework2::CollisionCheck(glm::vec3 pos)
{
	if (pos.y <= 1.0)
	{
		return true;
	}

	glm::vec3 new_pos = glm::vec3(pos);
	new_pos.y = 0;

	for (int i = 0; i < 3; ++i)
	{
		glm::vec4 obj = buildings[i] * glm::vec4(1);

		if (glm::distance(new_pos, glm::vec3(obj)) < building_radius)
		{
			return true;
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		glm::vec4 obj = trees[i] * glm::vec4(1);

		if (glm::distance(new_pos, glm::vec3(obj)) < tree_radius)
		{
			return true;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		glm::vec4 obj = gates[i] * glm::vec4(1);

		if (glm::distance(new_pos, glm::vec3(obj)) <= gate_radius * 2 && gate_status[i] == 1)
		{
			gate_status[i] = 2;

			if (i == 2)
			{
				running = false;
			}
			else
			{
				gate_status[i + 1] = 1;
			}
		}
	}

	return false;
}



