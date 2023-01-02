#pragma once

#include <GL/glew.h>
#include <glimac/Image.hpp>

using namespace glimac;

class Texture
{
	public:
		Texture();
		void loadTexture(const FilePath& filepath);
		void bindingFirstTexture();
		void bindingSecondTexture();
		void debindingTexture();
		void clearTexture();

	private:
		GLuint texture;
};