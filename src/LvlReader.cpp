#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "LvlReader.hpp"
#include "Treasure.cpp"

vector<string> LvlReader::parse_line(const string str)
{
    stringstream ss(str);
    string token;
    vector<string> res;
    while (!ss.eof())
    {
        getline(ss, token, ':');
        res.push_back(token);
    }
    return res;
}

void LvlReader::build()
{
    string line;
    ifstream file(path_file);
    if (!file)
    {
        cout << "No such file\n";
    }
    else
    {
        getline(file, line);
        first_comment = line;

        getline(file, line);
        path_dungeon_ppm = line;

        // Part treasures.
        getline(file, line);
        nb_treasures = int(stoi(line));
        for (int i = 0; i < nb_treasures; i++)
        {
            // Parse data in line correspoding to the Treasure.
            getline(file, line);
            auto tokens = parse_line(line);
            auto treasure = Treasure(stoul(tokens[0]), make_tuple(stoul(tokens[1]), stoul(tokens[2])), tokens[3]);
            std::cout << treasure << std::endl;
            treasures.push_back(treasure);
        }

        // Part monstrers.
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