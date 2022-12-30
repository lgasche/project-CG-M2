#include <project/Texture.hpp>

Texture::Texture(){

}

void Texture::loadTexture(GLuint *texture, std::unique_ptr<Image> image)
{
   glGenTextures(1, texture);
    // Bindind de la texture
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Envoie de l'image sur la texture 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    // Débindind de la texture
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void Texture::loadWall(const FilePath& filepath)
{
	loadTexture(&textureWall, loadImage(filepath));
}

void Texture::loadFloor(const FilePath& filepath)
{
	loadTexture(&textureFloor, loadImage(filepath));
}

void Texture::loadRoof(const FilePath& filepath)
{
	loadTexture(&textureRoof, loadImage(filepath));
}

void Texture::loadCreature(const FilePath& filepath)
{
	loadTexture(&textureCreature, loadImage(filepath));
}

void Texture::bindingWallTexture()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureWall); // la texture textureWall est bindée sur l'unité GL_TEXTURE0
}

void Texture::bindingFloorTexture()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureFloor); // la texture textureWall est bindée sur l'unité GL_TEXTURE0
}

void Texture::bindingRoofTexture()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureRoof); // la texture textureWall est bindée sur l'unité GL_TEXTURE0
}

void Texture::bindingCreatureTexture()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureCreature); // la texture textureWall est bindée sur l'unité GL_TEXTURE0
}

void Texture::debindingTexture()
{
	// Débindind de la texture principale
	glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0     
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &textureWall);
	glDeleteTextures(1, &textureRoof);
	glDeleteTextures(1, &textureFloor);
	glDeleteTextures(1, &textureCreature);
}