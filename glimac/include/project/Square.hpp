#pragma once

#include <vector>
#include "Shape.hpp"

class Square {
    public:
        // Constructeur: alloue le tableau de données et construit les attributs des vertex
        Square() {
                std::vector<ShapeVertex> data;
                // Construit l'ensemble des vertex : position / normal / texCoords
                data.push_back(ShapeVertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec2(0, 1)));
                data.push_back(ShapeVertex(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)));
                data.push_back(ShapeVertex(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1)));
                data.push_back(ShapeVertex(glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), glm::vec2(1, 0)));
                // 6 Vertex pour 2 triangle
                m_nVertexCount = 6;      
                // Construit les vertex finaux en regroupant les données en triangles:
                // Premier triangle
                m_Vertices.push_back(data[0]);
                m_Vertices.push_back(data[1]);
                m_Vertices.push_back(data[2]);
                // deuxième triangle
                m_Vertices.push_back(data[1]);
                m_Vertices.push_back(data[2]);
                m_Vertices.push_back(data[3]);
        }

        // Renvoit le pointeur vers les données
        const ShapeVertex* getDataPointer() const {
            return &m_Vertices[0];
        }
        
        // Renvoit le nombre de vertex
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount; // Nombre de vertex
};