#pragma once

#include <iostream>
#include <map>

using namespace std;

#include <project/Texture.hpp>
#include <glimac/glm.hpp>
#include <project/LevelStructure.hpp>

#include "Treasure.hpp"

class TreasureStorage
{

private:
    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
    unsigned int type;

    Texture texture;

    LevelProgram tunnelProgam;

public:
    // Constructor copy.
    TreasureStorage(const TreasureStorage &other) : treasures{other.treasures},
                                                    type{other.type},
                                                    texture{other.texture}
    // todo add tunnelProgam
    {
    }

    TreasureStorage(std::map<std::tuple<unsigned int, unsigned int>, Treasure> treasures_) : treasures{treasures_}
    {
        // tunnelProgam.loadBasicProgram(applicationPath_);

        // Charge model.
        auto itr = treasures.begin();
        texture.loadTexture("../assets/textures/" + itr->second.get_model());

        // Type_id of the treasure.
        type = itr->second.get_type();
    }

    void add(tuple<unsigned int, unsigned int> pos, Treasure treasure) { treasures.insert({pos, treasure}); };
    // void draw(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    // void clear();
};