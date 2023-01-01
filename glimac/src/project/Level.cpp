#include <project/Level.hpp>

void Level::drawLevel(int squareVertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{
	tunnelStorage.drawTunnels(squareVertex, globalMVMatrix, projMatrix);
	// Creature
	// Tresure
}

void Level::clear()
{
	tunnelStorage.clear();
	/*
	textureWall.clearTexture();
	textureRoof.clearTexture();
	textureFloor.clearTexture();
	textureCreature.clearTexture();
	*/
}