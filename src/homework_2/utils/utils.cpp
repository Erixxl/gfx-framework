#include "homework_2/utils/utils.hpp"


using namespace std;
using namespace hw2_utils;


Camera::Camera()
{

}


Camera::Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
{
	Set(position, center, up);
}


Camera::~Camera()
{

}


void Camera::Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
{
	this->position = position;
	forward = glm::normalize(center - position);
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward);
	distanceToTarget = glm::distance(position, center);
}


void Camera::MoveForward(float distance)
{
	glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	position += dir * distance;
}


void Camera::TranslateForward(float distance)
{
	position += forward * distance;
}


void Camera::TranslateUpward(float distance)
{
	position += up * distance;
}


void Camera::TranslateRight(float distance)
{
	glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
	position += dir * distance;
}


void Camera::RotateFirstPerson_OX(float angle)
{
	glm::vec4 newForward = glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1);

	forward = glm::normalize(glm::vec3(newForward));
	up = glm::normalize(glm::cross(right, forward));
}


void Camera::RotateFirstPerson_OY(float angle)
{
	glm::vec4 newForward = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0))
		* glm::vec4(forward, 1);

	glm::vec4 newRight = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0))
		* glm::vec4(right, 1);

	forward = glm::normalize(glm::vec3(newForward));
	right = glm::normalize(glm::vec3(newRight));
	up = glm::normalize(glm::cross(right, forward));
}


void Camera::RotateFirstPerson_OZ(float angle)
{
	glm::vec4 newRight = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 0, 1))
		* glm::vec4(right, 1);

	right = glm::normalize(glm::vec3(newRight));
	up = glm::normalize(glm::cross(right, forward));
}


void Camera::RotateThirdPerson_OX(float angle)
{
	position += forward * distanceToTarget;
	RotateFirstPerson_OX(angle);
	position -= forward * distanceToTarget;
}


void Camera::RotateThirdPerson_OY(float angle)
{
	position += forward * distanceToTarget;
	RotateFirstPerson_OY(angle);
	position -= forward * distanceToTarget;
}


void Camera::RotateThirdPerson_OZ(float angle)
{
	position += forward * distanceToTarget;
	RotateFirstPerson_OZ(angle);
	position -= forward * distanceToTarget;
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}


glm::vec3 Camera::GetTargetPosition()
{
	return position + forward * distanceToTarget;
}


