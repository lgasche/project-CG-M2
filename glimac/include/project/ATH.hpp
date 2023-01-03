#pragma once

#include <iostream>
#include <glimac/glm.hpp>
#include <project/Texture.hpp>
#include <project/ATHStructure.hpp>
#include <project/Tunnel.hpp>

enum ATHBouton
{
	Base 	   = 0,
	HighLeft   = 1,
	HighMiddle = 2,
	HighRight  = 3,
	LowLeft    = 4,
	LowMiddle  = 5,
	LowRight   = 6
};

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

		ATHBouton clickCoordinate(glm::ivec2 mousePos, float widthWindow, float heightWindow);

		void update(int index_) { index = index_; };

		void drawATH(int vertex, glm::mat4 projMatrix);
		void clear();
};