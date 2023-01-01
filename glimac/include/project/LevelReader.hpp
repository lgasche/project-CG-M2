#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unistd.h>
#include <algorithm>

using namespace std;

#include "Treasure.hpp"
#include "Monster.hpp"
#include "element/Tunnel.hpp"
#include "Level.hpp"

class LevelReader
{
    friend std::ostream &operator<<(std::ostream &stream, const LevelReader &lvlReader)
    {
        return stream << "LevelReader: " << lvlReader.file_name
                      << " | " << lvlReader.first_comment
                      << " | " << lvlReader.path_file
                      << " | " << lvlReader.path_dungeon_ppm
                      << " | " << lvlReader.nb_monsters;
    }

public:
    string file_name;
    LevelReader(const string file_name_) : file_name{file_name_}
    {
        // Build path file.
        char tmp[256];
        getcwd(tmp, 256);
        path_file = tmp;
        path_file += "/lvls/" + file_name + ".txt";

        // Build path ppm.
        path_dungeon_ppm = tmp;
        path_dungeon_ppm += "/lvls/dungeons/";
    }

    vector<string> parse_line(const string str);
    void read_lvl_txt_and_creat_objects();
    vector<vector<char>> read_ppm_to_vmap();
    void read_vmap_and_creat_decorative(const vector<vector<char>> vmap);
    Tunnel create_tunnel(const vector<vector<char>> vmap, const int x, const int y);

    // TODO change Tunnel by decords : water/door/ect..
    map<tuple<unsigned int, unsigned int>, Tunnel> map_lvl;

    Level creat_lvl(const FilePath &applicationPath);

private:
    string path_file;

    string first_comment;
    string path_dungeon_ppm;
    int nb_treasures = -1;
    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
    int nb_monsters = -1;
    map<tuple<unsigned int, unsigned int>, Monster> monsters;
    tuple<unsigned int, unsigned int> start;
};