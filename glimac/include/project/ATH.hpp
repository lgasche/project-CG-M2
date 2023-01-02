#pragma once

#include <iostream>
#include <glimac/glm.hpp>
#include <project/Texture.hpp>
#include <project/ATHStructure.hpp>

#include "element/Tunnel.hpp"

class ATH
{

	private:
		Texture textureBackground;
		Texture textureBase;
		Texture textureHighLeft;
		Texture textureHighMiddle;
		Texture textureHighRight;
		Texture textureLowLeft;
		Texture textureLowMiddle;
		Texture textureLowRight;


		ATHProgram athProgram;
		int index = 0;

		void addMatrix(int vertex, glm::mat4 projMatrix, glm::mat4 matrix);

	public:
		ATH(const FilePath& applicationPath);

		int clickCoordinate(glm::ivec2 mousePos, float widthWindow, float heightWindow);

		void update(int index_) { index = index_; };

		void drawATH(int vertex, glm::mat4 projMatrix);
		void clear();
};