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

bool Level::canMove(std::tuple<unsigned int, unsigned int> pos)
{
	//std::cout << get<0>(pos) << " " << get<1>(pos) << std::endl;
	if(!tunnelStorage.canMove(pos)) return false;
	return true;
}