#pragma once

#include <GL/glew.h>
#include <glimac/Image.hpp>

using namespace glimac;

class Texture
{
	public:
		Texture();
		void loadTexture(const FilePath& filepath);
		void bindingTexture();
		void debindingTexture();
		void clearTexture();

	private:
		GLuint texture;
};