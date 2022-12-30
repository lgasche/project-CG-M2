#include <project/Lvl.hpp>

void Lvl::drawLevel(BasicProgram *squareProgam, glm::mat4 globalMVMatrix, glm::mat4 projMatrix) 
{	
	vertex.bindingVAO();

	// Walls
	texture.bindingWallTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawWalls(square.getVertexCount(), squareProgam, globalMVMatrix, projMatrix);
	}
	// Floors
	texture.bindingFloorTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawFloor(square.getVertexCount(), squareProgam, globalMVMatrix, projMatrix);
	}
	// Roofs
	texture.bindingRoofTexture();
	for(auto it = map_lvl.begin(); it != map_lvl.end(); it++)
	{
	    it->second.drawRoof(square.getVertexCount(), squareProgam, globalMVMatrix, projMatrix);
	}

	vertex.debindingVAO();
	texture.debindingTexture();
}

void Lvl::clear() 
{ 
	texture.clearTexture(); 
	vertex.clearData();
}

void Lvl::initialization() 
{	
	glEnable(GL_DEPTH_TEST);
    // Gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Chargement des textures
	texture.loadWall("../assets/textures/Wall_1.png");
    texture.loadRoof("../assets/textures/Roof_1.png");
    texture.loadFloor("../assets/textures/Floor_1.png");
    texture.loadCreature("../assets/textures/Creature_1.png");

    // VBO - VAO
    vertex.sendData(square.getVertexCount(), square.getDataPointer());
    vertex.indicationVertices();
}