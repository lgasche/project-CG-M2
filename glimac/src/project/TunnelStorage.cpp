#include <project/TunnelStorage.hpp>


TunnelStorage::TunnelStorage(const std::map<std::tuple<unsigned int, unsigned int>, Tunnel> map_lvl_, const FilePath& applicationPath) : tunnels{map_lvl_}
{	
	tunnelProgam.loadBasicProgram(applicationPath);
	textureWall.loadTexture("../assets/textures/Wall_1.png");
	textureRoof.loadTexture("../assets/textures/Roof_1.png");
	textureFloor.loadTexture("../assets/textures/Floor_1.png");
}

TunnelStorage::TunnelStorage() 
{}


void TunnelStorage::addLight(glm::mat4 globalMVMatrix)
{
	glUniform3f(tunnelProgam.uKd, 0.3f, 0.3f, 0.3f);	   // Intensité de la lumiètre globale
	glUniform3f(tunnelProgam.uKs, 0.001f, 0.001f, 0.001f); // Intensité du centre lumineux
	glUniform1f(tunnelProgam.uShininess, 4.f);			   // Taille du centre lumineux
	glm::vec4 LightPos = globalMVMatrix * glm::vec4(0.0, 0.0, 0.0, 0.0);
	glUniform3f(tunnelProgam.uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
	glUniform3f(tunnelProgam.uLightIntensity, 1.f, 1.f, 1.f);
}

void TunnelStorage::addMatrix(int vertex, glm::mat4 projMatrix, glm::mat4 matrix)
{
	glUniformMatrix4fv(tunnelProgam.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * matrix));
    glUniformMatrix4fv(tunnelProgam.uMVMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniformMatrix4fv(tunnelProgam.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(matrix))));
    glDrawArrays(GL_TRIANGLES, 0, vertex);
}

bool TunnelStorage::canMove(std::tuple<unsigned int, unsigned int>  pos)
{
	for (auto it = tunnels.begin(); it != tunnels.end(); it++)
	{
		if(it->second.get_pos() == pos)  return true;
	}
	return false;
}

void TunnelStorage::drawTunnels(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix)
{	
	tunnelProgam.mProgram.use();
	glUniform1i(tunnelProgam.uTexture, 0);

	// Lumière
	addLight(globalMVMatrix);

	// Walls
	textureWall.bindingFirstTexture();
	for (auto it = tunnels.begin(); it != tunnels.end(); it++)
	{
		if(it->second.haveNorthWall()) addMatrix(vertex, projMatrix, it->second.drawNorthWall(globalMVMatrix));
		if(it->second.haveEastWall())  addMatrix(vertex, projMatrix, it->second.drawEastWall(globalMVMatrix));
		if(it->second.haveSouthWall()) addMatrix(vertex, projMatrix, it->second.drawSouthWall(globalMVMatrix));
		if(it->second.haveWestWall())  addMatrix(vertex, projMatrix, it->second.drawWestWall(globalMVMatrix));
	}

	// // Roofs
	textureRoof.bindingFirstTexture();
	for (auto it = tunnels.begin(); it != tunnels.end(); it++)
	{
		addMatrix(vertex, projMatrix, it->second.drawRoof(globalMVMatrix));
	}

	// Floors
	textureFloor.bindingFirstTexture();
	for (auto it = tunnels.begin(); it != tunnels.end(); it++)
	{
		addMatrix(vertex, projMatrix, it->second.drawFloor(globalMVMatrix));
	}
}

void TunnelStorage::clear()
{
	textureWall.clearTexture();
	textureRoof.clearTexture();
	textureFloor.clearTexture();
}