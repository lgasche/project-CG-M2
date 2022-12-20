#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unistd.h>

using namespace std;

#include "Treasure.hpp"

class LvlReader
{
    friend std::ostream &operator<<(std::ostream &stream, const LvlReader &lvlReader)
    {
        return stream << "LvlReader: " << lvlReader.file_name
                      << " | " << lvlReader.first_comment
                      << " | " << lvlReader.path_file
                      << " | " << lvlReader.path_dungeon_ppm
                      << " | " << lvlReader.nb_monsters;
    }

public:
    string file_name;
    LvlReader(const string file_name_) : file_name{file_name_}
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
    void read_lvl();
    void read_ppm();

private:
    string path_file;

    string first_comment = "void";
    string path_dungeon_ppm;
    int nb_treasures = -1;
    // map<tuple<unsigned int, unsigned int>, unique_ptr<Treasure>> treasures;
    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
    int nb_monsters = -1;
    // vector monsters;
};