#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem;

#include "Treasure.hpp"

class LvlReader
{
    friend std::ostream &operator<<(std::ostream &stream, const LvlReader &lvlReader)
    {
        return stream << "LvlReader: " << lvlReader.file_name << " | " << lvlReader.first_comment
                      << " | " << lvlReader.path_dungeon_ppm << " | " << lvlReader.nb_monsters;
    }

public:
    string file_name;
    LvlReader(const string file_name_) : file_name{file_name_}
    {
        path_file = fs::current_path() / "lvls" / file_name += ".txt";
    }

    vector<string> parse_line(const string str);
    void build();

private:
    fs::path path_file;

    string first_comment;
    string path_dungeon_ppm;
    int nb_treasures;
    // vector<unique_ptr<Treasure>> treasures;
    vector<Treasure> treasures;
    int nb_monsters;
    // vector monsters;
};