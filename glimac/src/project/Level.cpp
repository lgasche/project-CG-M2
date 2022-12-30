#include <project/Level.hpp>

void Level::addLight(glm::mat4 globalMVMatrix) {
	glUniform3f(squareProgam.uKd, 0.3f, 0.3f, 0.3f);       // Intensité de la lumiètre globale
	glUniform3f(squareProgam.uKs, 0.001f, 0.001f, 0.001f); // Intensité du centre lumineux
	glUniform1f(squareProgam.uShininess, 4.f);             // Taille du centre lumineux
	glm::vec4 LightPos = globalMVMatrix * glm::vec4(0.0, 0.0, 0.0, 0.0);
	glUniform3f(squareProgam.uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
	glUniform3f(squareProgam.uLightIntensity, 1.f, 1.f, 1.f);
}

void Level::drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix) 
{	
	squareProgam.mProgram.use();
    glUniform1i(squareProgam.uTexture, 0);

    // Lumière 
    addLight(globalMVMatrix);

	// Walls
	textureWall.bindingTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawWalls(squareVertex, &squareProgam, globalMVMatrix, projMatrix);
	}
	// Roofs
	textureRoof.bindingTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawRoof(squareVertex, &squareProgam, globalMVMatrix, projMatrix);
	}
	// Floors
	textureFloor.bindingTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawFloor(squareVertex, &squareProgam, globalMVMatrix, projMatrix);
	}

}

void Level::clear() 
{ 
	textureWall.clearTexture(); 
	textureRoof.clearTexture(); 
	textureFloor.clearTexture(); 
	textureCreature.clearTexture(); 
}