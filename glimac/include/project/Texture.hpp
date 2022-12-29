#pragma once

#include <GL/glew.h>
#include <glimac/Image.hpp>

using namespace glimac;

class Texture
{
	public:
		Texture();
		void loadWall(const FilePath& filepath);
		void loadCreature(const FilePath& filepath);
		void loadFloor(const FilePath& filepath);
		void bindingWallTexture();
		void bindingCreatureTexture();
		void bindingFloorTexture();
		void debindingTexture();
		void clearTexture();

	private:
		GLuint textureWall, textureCreature, textureFloor;
		void loadTexture(GLuint *texture, std::unique_ptr<Image> image);
};