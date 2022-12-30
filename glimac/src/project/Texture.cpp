#include <project/Texture.hpp>

Texture::Texture(){

}

void Texture::loadTexture(const FilePath& filepath)
{
	std::unique_ptr<Image> image = loadImage(filepath);

   glGenTextures(1, &texture);
    // Bindind de la texture
    glBindTexture(GL_TEXTURE_2D, texture);
    // Envoie de l'image sur la texture 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    // Débindind de la texture
    glBindTexture(GL_TEXTURE_2D, 0); 
}


void Texture::bindingTexture()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // la texture est bindée sur l'unité GL_TEXTURE0
}

void Texture::debindingTexture()
{
	// Débindind de la texture 
	glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0     
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &texture);
}