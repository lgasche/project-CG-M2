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

private:
    map<tuple<unsigned int, unsigned int>, Item> items;
    unsigned int type;

    Texture texture;

    LevelProgram tunnelProgam;

public:
    // Constructor copy.
    Storage(const Storage &other) : items{other.items},
                                    type{other.type},
                                    texture{other.texture}
    // todo add tunnelProgam
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
    // void draw(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    // void clear();
};