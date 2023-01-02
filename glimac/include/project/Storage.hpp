#pragma once

#include <iostream>
#include <map>

using namespace std;

#include <project/Texture.hpp>
#include <glimac/glm.hpp>
#include <project/LevelStructure.hpp>

template <typename Item>
class Storage
{
    friend std::ostream &operator<<(std::ostream &stream, const Storage<Item> &storage)
    {
        for (auto &i : storage.items)
        {
            stream << get<0>(i.first) << "," << get<1>(i.first) << " | ";
        }
        return stream;
    }

private:
    map<tuple<unsigned int, unsigned int>, Item> items;
    unsigned int type;

    Texture texture;

public:
    // Constructor copy.
    Storage(const Storage &other) : items{other.items},
                                    type{other.type},
                                    texture{other.texture}
    {
    }

    Storage(std::map<std::tuple<unsigned int, unsigned int>, Item> items_) : items{items_}
    {
        // tunnelProgam.loadBasicProgram(applicationPath_);

        // Charge model.
        auto itr = items.begin();
        texture.loadTexture("../assets/textures/" + itr->second.get_model());

        // Type_id of the item.
        type = itr->second.get_type();
    }

    void add(tuple<unsigned int, unsigned int> pos, Item item) { items.insert({pos, item}); };
    bool triggerAction(std::tuple<unsigned int, unsigned int> pos, Player &player)
    {
        auto item = items.find(pos);
        if (item == items.end())
            return false;
        if (item->second.action(player))
            items.erase(pos);
        return true;
    }

    void drawEntity(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix, std::tuple<float, float> player, LevelProgram &entityProgam)
    {
        // entityProgam.mProgram.use();
        glUniform1i(entityProgam.uTexture, 0);

        // Lumière
        glUniform3f(entityProgam.uKd, 0.3f, 0.3f, 0.3f);       // Intensité de la lumiètre globale
        glUniform3f(entityProgam.uKs, 0.001f, 0.001f, 0.001f); // Intensité du centre lumineux
        glUniform1f(entityProgam.uShininess, 4.f);             // Taille du centre lumineux
        glm::vec4 LightPos = globalMVMatrix * glm::vec4(0.0, 0.0, 0.0, 0.0);
        glUniform3f(entityProgam.uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glUniform3f(entityProgam.uLightIntensity, 1.f, 1.f, 1.f);

        // Entity
        texture.bindingFirstTexture();
        for (auto it = items.begin(); it != items.end(); it++)
        {
            auto pos = std::make_tuple((float)get<0>(it->first) + 0.5f, (float)get<1>(it->first) + 0.5f); // it->first;
            // std::cout << get<0>(pos) << " - " << get<1>(pos) << std::endl;
            float m = (get<1>(player) - get<1>(pos)) / (get<0>(player) - get<0>(pos));
            auto r = atan(m) + ((get<0>(player) >= get<0>(pos)) ? glm::radians(-90.f) : glm::radians(90.f));
            glm::mat4 matrix = glm::translate(globalMVMatrix, glm::vec3(get<0>(pos), 0.f, get<1>(pos)));
            // glm::mat4 matrix = glm::translate(globalMVMatrix, glm::vec3(2.5f, 0.f, 2.5f));
            matrix = glm::translate(matrix, glm::vec3((0.5f * (cos(r + glm::radians(180.f)))), 0.f, (sin(-r) / 2.f)));
            matrix = glm::rotate(matrix, -r, glm::vec3(0, 1, 0));
            glUniformMatrix4fv(entityProgam.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * matrix));
            glUniformMatrix4fv(entityProgam.uMVMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
            glUniformMatrix4fv(entityProgam.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(matrix))));
            glDrawArrays(GL_TRIANGLES, 0, vertex);
        }
    }
};