#include <project/Vertex.hpp>

Vertex::Vertex(){
	// Création du VBO
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

}

void Vertex::sendData(GLsizeiptr size, const void *data)
{
	// Bindind du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Envoie des données
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(ShapeVertex), data, GL_STATIC_DRAW);
    // Débindind du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vertex::indicationVertices()
{
	// Binding du VAO 
    glBindVertexArray(vao);
    // Précision de l'utilisation du VAO
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    // Bindind du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Spécification des différents formats, Débinding du VBO
    glVertexAttribPointer(VERTEX_ATTR_POSITION,  3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,    3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    // Débinding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Débindind du VAO
    glBindVertexArray(0);
}

void Vertex::clearData()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Vertex::testBindingVAO()
{
	// Binding du VAO 
	glBindVertexArray(vao);

	// TOUS LES AFFCHAGES DES ELEMENTS DU JEU
	// glBindVertexArray(0);
}