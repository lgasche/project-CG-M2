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
    bool triggerAction(std::tuple<unsigned int, unsigned int> pos, Player &player)
    {
        auto item = items.find(pos);
        if (item == items.end())
            return false;
        if (item->second.action(player))
            items.erase(pos);
        return true;
    }
    // void draw(int vertex, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    // void clear();
};