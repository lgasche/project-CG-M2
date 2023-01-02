#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <cmath>
#include <tuple>
#include <project/ATH.hpp>

using namespace glimac;

enum Direction
{
	North = 0,
	East = 1,
	South = 2,
	West = 3
};

class Camera
{
public:
	Camera(float x, float y);
	int update();
	std::tuple<unsigned int, unsigned int> prediction(ATHBouton boutonValue);
	bool movementCamera();
	void moveAhead(bool movingAhead);
	void moveLeft(bool movingLeft);
	void turnLeft(bool turningLeft);
	glm::mat4 getViewMatrix() const;
	glm::vec3 getFrontVector() const { return frontVector; }

private:
	void computeDirectionVectors();

	glm::vec3 position;
	float Phi; // Pour tourner de gauche à droite
	Direction dir = North;

	glm::vec3 frontVector;
	glm::vec3 leftVector;
	glm::vec3 upVector;

	float speed;
	float indice;

	bool isTurningLeft = false, isTurningRight = false,
		 isMovingLeft = false, isMovingRight = false,
		 isMovingAhead = false, isMovingBack = false;
};