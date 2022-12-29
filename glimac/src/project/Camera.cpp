#include <project/Camera.hpp>
#include <iostream>

Camera::Camera(){
	position = glm::vec3(0.5f, 0.5f, 0.5f);
	Phi = M_PI * 2.5f;
	speed = 4.f;
	indice = 0.f;
	computeDirectionVectors();
}

void Camera::computeDirectionVectors(){
	Phi = (Phi < M_PI) ? M_PI * 3.f : ((Phi > M_PI * 5.f) ? M_PI : Phi); // Correction du nombre PHI avec un Min et un Max pour éviter les grandes valeurs;
	frontVector = glm::vec3(cos(0.f) * sin(Phi)    , sin(0.f), cos(0.f) * cos(Phi));
	leftVector  = glm::vec3(sin(Phi + (M_PI / 2.f)), 0       , cos(Phi + (M_PI / 2.f)));
	upVector = glm::cross(frontVector, leftVector);
}

bool Camera::moveAhead(bool direction)
{
	if(indice >= 100)
	{
		indice = 0.f;
		return true;
	}
	indice += speed;
	position += speed * 0.01f * frontVector * ((direction) ? 1.f : -1.f);
	computeDirectionVectors();
	return false;
}

bool Camera::moveLeft(bool direction)
{
	if(indice >= 100)
	{
		indice = 0.f;
		return true;
	}
	indice += speed;
	position += speed * 0.01f * leftVector * ((direction) ? 1.f : -1.f);
	computeDirectionVectors();
	return false;
}

bool Camera::turnLeft(bool direction)
{	
	if(indice >= 100) 
	{
		indice = 0.f;
		return true;
	}
	/*
	float correction = ((indice >= 100.f / 2.f) ? 2.f : 0.f);
	float setp1 = (indice + speed) * ((2.f) / 100.f) - correction;
	float setp2 = (indice        ) * ((2.f) / 100.f) - correction;
	if(setp1 > 1.f) {
		setp1 = 1.f;
		correction = ((indice + speed >= 100.f / 2.f) ? 2.f : 0.f);
		Phi += (acos((indice + speed) * ((2.f) / 100.f) - correction) - acos(-1)) /  (2.f)  * ((direction) ? -1.f : 1.f);
	}
	Phi += (acos(setp1) - acos(setp2)) /  (2.f)  * ((direction) ? -1.f : 1.f);
	*/
	Phi += (((M_PI / 2) / 100.f)) * speed * ((direction) ? 1.f : -1.f);
	indice += speed;
	computeDirectionVectors();
	return false;
}

glm::mat4 Camera::getViewMatrix() const
{
	//Point
	glm::vec3 Point = position + frontVector;
	glm::mat4 MV = glm::lookAt(position, position + frontVector, upVector);
	return MV;
}