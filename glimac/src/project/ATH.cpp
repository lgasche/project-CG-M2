#include <project/ATH.hpp>


ATH::ATH(const FilePath& applicationPath) {
	athProgram.loadATHProgram(applicationPath);
	textureBackground.loadTexture("../assets/textures/ATH_2_2.png");
	textureBase.loadTexture("../assets/textures/ATH_1.png");
	textureHighLeft.loadTexture("../assets/textures/ATH_1_2.png");
	textureHighMiddle.loadTexture("../assets/textures/ATH_1_3.png");
	textureHighRight.loadTexture("../assets/textures/ATH_1_4.png");
	textureLowLeft.loadTexture("../assets/textures/ATH_1_5.png");
	textureLowMiddle.loadTexture("../assets/textures/ATH_1_6.png");
	textureLowRight.loadTexture("../assets/textures/ATH_1_7.png");
}

ATHBouton ATH::clickCoordinate(glm::ivec2 mousePos, float widthWindow, float heightWindow) {
	// Hight Left Bouton position
	if(mousePos.x > widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (20.f / 100.f) &&
	   mousePos.x < widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (40.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (36.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (57.f / 100.f))   
		return HighLeft;
	// Hight Middle Bouton position
    if(mousePos.x > widthWindow  *  (2.f / 3.f) + widthWindow * (1.f / 3.f) * (40.f / 100.f) &&
	   mousePos.x < widthWindow  *  (2.f / 3.f) + widthWindow * (1.f / 3.f) * (60.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (36.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (57.f / 100.f))
        return HighMiddle;
    // Hight Right Bouton position
 	if(mousePos.x > widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (60.f / 100.f) &&
	   mousePos.x < widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (80.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (36.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (57.f / 100.f))
        return HighRight;
    // Low Left Bouton position
    if(mousePos.x > widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (20.f / 100.f) &&
	   mousePos.x < widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (40.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (58.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (79.f / 100.f))
	   	return LowLeft;
	// Low Middle Bouton position
	if(mousePos.x > widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (40.f / 100.f) &&
	   mousePos.x < widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (60.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (58.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (79.f / 100.f))
	   	return LowMiddle;
	// Low Right Bouton position
	if(mousePos.x > widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (60.f / 100.f) &&
	   mousePos.x < widthWindow  * (2.f / 3.f) + widthWindow  * (1.f / 3.f) * (80.f / 100.f) &&
	   mousePos.y > heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (58.f / 100.f) &&
	   mousePos.y < heightWindow * (1.f / 2.f) + heightWindow * (1.f / 2.f) * (79.f / 100.f))
	   	return LowRight;
    return Base;
}

void ATH::addMatrix(int vertex, glm::mat4 projMatrix, glm::mat4 matrix)
{
	glUniformMatrix4fv(athProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * matrix));
	glUniformMatrix4fv(athProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
	glUniformMatrix4fv(athProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(matrix))));
	glDrawArrays(GL_TRIANGLES, 0, vertex);
}

void ATH::drawATH(int vertex, glm::mat4 projMatrix)
{	
	athProgram.mProgram.use();
	glUniform1i(athProgram.uTexture,  0);
	glUniform1i(athProgram.uTexture2, 1);
	
	switch(index) 
	{
		case 0: textureBase.bindingFirstTexture(); break;
		case 1: textureHighLeft.bindingFirstTexture(); break;
		case 2: textureHighMiddle.bindingFirstTexture(); break;
		case 3: textureHighRight.bindingFirstTexture(); break;
		case 4: textureLowLeft.bindingFirstTexture(); break;
		case 5: textureLowMiddle.bindingFirstTexture(); break;
		case 6: textureLowRight.bindingFirstTexture(); break;
	}
	textureBackground.bindingSecondTexture();
	glm::mat4 matrix = glm::translate(glm::mat4(1), glm::vec3(0.125f, -0.25f, -0.25f));
	matrix = glm::scale(matrix, glm::vec3(0.25f));
	addMatrix(vertex, projMatrix, matrix);
	glDrawArrays(GL_TRIANGLES, 0, vertex);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE1

	//textureLow.bindingSecondTexture();

	matrix = glm::translate(glm::mat4(1), glm::vec3(0.125f, 0.f, -0.25f));
	matrix = glm::scale(matrix, glm::vec3(0.25f));
	addMatrix(vertex, projMatrix, matrix);
	glDrawArrays(GL_TRIANGLES, 0, vertex);
}

void ATH::clear()
{
	textureBackground.clearTexture();
	textureBase.clearTexture();
	textureHighLeft.clearTexture();
	textureHighMiddle.clearTexture();
	textureHighRight.clearTexture();
	textureLowLeft.clearTexture();
	textureLowMiddle.clearTexture();
	textureLowRight.clearTexture();
}