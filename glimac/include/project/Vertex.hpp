#pragma once

#include <project/Shape.hpp>
#include <GL/glew.h>

class Vertex
{
	public:
		Vertex();
		void sendData(GLsizeiptr size, const void *data);
		void indicationVertices();
		void clearData();
		void bindingVAO();
		void debindingVAO();



	private:
		GLuint vbo, vao;

		const GLuint VERTEX_ATTR_POSITION  = 0;
	    const GLuint VERTEX_ATTR_NORMAL    = 1;
	    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
};