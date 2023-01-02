#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <cmath>

using namespace glimac;

class Camera
{
	public:
		Camera(float x, float y);
		int  update();
		bool movementCamera();
		void moveAhead(bool movingAhead);
		void moveLeft(bool movingLeft);
		void turnLeft(bool turningLeft);
		glm::mat4 getViewMatrix() const;


	private:
		void computeDirectionVectors();

		glm::vec3 position;
		float Phi;		// Pour tourner de gauche à droite

		glm::vec3 frontVector;
		glm::vec3 leftVector;
		glm::vec3 upVector;

		float speed;
		float indice;

		bool isTurningLeft  = false, isTurningRight = false,
         	 isMovingLeft   = false, isMovingRight  = false,
         	 isMovingAhead  = false, isMovingBack   = false;
};