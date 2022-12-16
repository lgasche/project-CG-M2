#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "LvlReader.hpp"

void LvlReader::build()
{
    cout << path_file << endl;
    string line;
    ifstream file(path_file);
    if (!file)
    {
        cout << "No such file\n";
    }
    else
    {
        cout << "here" << endl;
        getline(file, line);
        first_comment = line;

        getline(file, line);
        path_dungeon_ppm = line;

        getline(file, line);
        nb_treasures = int(stoi(line));
        for (int i = 0; i < nb_treasures; i++)
        {
            // Todo add treasure
            getline(file, line);
        }

        getline(file, line);
        nb_monsters = int(stoi(line));
        for (int i = 0; i < nb_monsters; i++)
        {
            // Todo add monster
            getline(file, line);
        }
    }
    file.close();
}