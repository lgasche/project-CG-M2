#pragma once

#include <cstdint>
#include <cmath>
#include <SDL/SDL.h>
#include "glm.hpp"

namespace glimac {

	class TrackballCamera {
	  
		public:
			TrackballCamera() {
		        m_fDistance = 1.f;
		        m_fAngleX = 0.f;
		        m_fAngleY = 0.f;
		    }

		    void moveFront(float delta) {
		    	m_fDistance += delta;
		    }

		    void rotateLeft(float degrees) {
		    	m_fAngleX += degrees; //fmod(m_fAngleX + degrees, 360.f);
		    }

		    void rotateUp(float degrees) {
		    	m_fAngleY += degrees; //fmod(m_fAngleY + degrees, 360.f);
		    }

		    glm::mat4 getViewMatrix() const{

		        glm::mat4 MatrixId = glm::mat4(1.0); //Matrice Identité
		        		  MatrixId = glm::translate( MatrixId, glm::vec3(-0.5f, -0.5f, -m_fDistance) ); //Translation en z
		                  MatrixId = glm::rotate( MatrixId, glm::radians(m_fAngleX), glm::vec3(1, 0, 0) ); //Axe x
		                  MatrixId = glm::rotate( MatrixId, glm::radians(m_fAngleY), glm::vec3(0, 1, 0) ); //Axe y
		        return MatrixId;
		    }

		private:
			float m_fDistance, m_fAngleX, m_fAngleY;
	};


    
}