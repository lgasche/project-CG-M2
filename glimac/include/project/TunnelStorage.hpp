#pragma once

#include <iostream>
#include <map>
#include <glimac/glm.hpp>
#include <project/Texture.hpp>
#include <project/LevelStructure.hpp>

#include "element/Tunnel.hpp"

class TunnelStorage
{

	private:
		map<tuple<unsigned int, unsigned int>, Tunnel> tunnels;

		Texture textureWall;
		Texture textureRoof;
		Texture textureFloor;

		LevelProgram tunnelProgam;

		void addLight(glm::mat4 globalMVMatrix);
		void addMatrix(int vertex, glm::mat4 projMatrix, glm::mat4 matrix);

	public:
		TunnelStorage();
		TunnelStorage(const std::map<std::tuple<unsigned int, unsigned int>, Tunnel> map_lvl_, const FilePath& applicationPath);

		bool canMove(std::tuple<unsigned int, unsigned int>  pos);
		void drawTunnels(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
		void addMap(const map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl_) { tunnels = map_lvl_; };
		void clear();
};