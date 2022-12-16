#pragma once

#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

class LvlReader
{
public:
    string file_name;
    LvlReader(const string file_name_) : file_name{file_name_}
    {
        auto res = filesystem::current_path() / "lvls" / file_name;
        res += ".txt";
        path_file = res;
    }

    void build();

    void get_infos()
    {
        cout << "LvlReader : " << file_name << endl;
        cout << "LvlReader : " << first_comment << endl;
        cout << "LvlReader : " << path_dungeon_ppm << endl;
        cout << "LvlReader : " << nb_treasures << endl;
        cout << "LvlReader : " << nb_monsters << endl;
    };

private:
    filesystem::path path_file;

    string first_comment;
    string path_dungeon_ppm;
    int nb_treasures;
    // vector treasures.
    int nb_monsters;
    // vector monsters;
};