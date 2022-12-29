#include <project/Camera.hpp>
#include <iostream>

Camera::Camera(float x, float y){
	position = glm::vec3(x + 0.5f, y + 0.5f, 0.5f);
	Phi = M_PI * 2.5f;
	speed = 4.f;
	indice = 0.f;
	computeDirectionVectors();
}
 
bool Camera::movementCamera()
{
	if(isTurningLeft) 	turnLeft(true);
    if(isTurningRight) 	turnLeft(false);
    if(isMovingLeft)  	moveLeft(true);
    if(isMovingRight) 	moveLeft(false);
    if(isMovingAhead)  	moveAhead(true);
    if(isMovingBack) 	moveAhead(false);
	return !isTurningLeft && !isTurningRight && !isMovingLeft && !isMovingRight && !isMovingAhead && !isMovingBack;
}

void Camera::computeDirectionVectors(){
	Phi = (Phi < M_PI) ? M_PI * 3.f : ((Phi > M_PI * 5.f) ? M_PI : Phi); // Correction du nombre PHI avec un Min et un Max pour éviter les grandes valeurs;
	frontVector = glm::vec3(cos(0.f) * sin(Phi)    , sin(0.f), cos(0.f) * cos(Phi));
	leftVector  = glm::vec3(sin(Phi + (M_PI / 2.f)), 0       , cos(Phi + (M_PI / 2.f)));
	upVector = glm::cross(frontVector, leftVector);
}

void Camera::moveAhead(bool movingAhead)
{
	if(indice == 0.f)
	{
		if(movingAhead)  isMovingAhead = true;
		if(!movingAhead) isMovingBack  = true;
	}
	if(indice >= 100.f)
	{
		indice = 0.f;
		if(movingAhead)  isMovingAhead = false;
		if(!movingAhead) isMovingBack  = false;
		return;
	}
	indice += speed;
	position += speed * 0.01f * frontVector * ((movingAhead) ? 1.f : -1.f);
	computeDirectionVectors();
}

void Camera::moveLeft(bool movingLeft)
{
	if(indice == 0.f)
	{
		if(movingLeft)  isMovingLeft  = true;
		if(!movingLeft) isMovingRight = true;
	}
	if(indice >= 100.f)
	{
		indice = 0.f;
		if(movingLeft)  isMovingLeft  = false;
		if(!movingLeft) isMovingRight = false;
		return;
	}
	indice += speed;
	position += speed * 0.01f * leftVector * ((movingLeft) ? 1.f : -1.f);
	computeDirectionVectors();
}

void Camera::turnLeft(bool turningLeft)
{	
	if(indice == 0.f)
	{
		if(turningLeft)  isTurningLeft  = true;
		if(!turningLeft) isTurningRight = true;
	}
	if(indice >= 100.f) 
	{
		indice = 0.f;
		if(turningLeft)  isTurningLeft  = false;
		if(!turningLeft) isTurningRight = false;
		return;
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
	indice += speed;
	Phi += (((M_PI / 2) / 100.f)) * speed * ((turningLeft) ? 1.f : -1.f);
	computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	glm::vec3 Point = position + frontVector;
	glm::mat4 MV = glm::lookAt(position, position + frontVector, upVector);
	return MV;
}