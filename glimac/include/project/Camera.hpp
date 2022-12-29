#pragma once
#include "glimac/glm.hpp"
#include <cmath>

class Camera
{
	public:
		Camera();
		bool moveAhead(bool direction);
		bool moveLeft(bool direction);
		bool turnLeft(bool direction);
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
};