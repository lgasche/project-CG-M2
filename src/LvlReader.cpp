#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

#include "LvlReader.hpp"
#include "Treasure.cpp"

/**
 * Parse the line describing an object or a monster.
 *
 * @param str line describing an object or a monster.
 *
 * @return a vector<string> of elements that make up the string.
 */
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

/**
 * Read the txt file corresponding to the level.
 * Create the different objects present in the level: treasures, monsters, etc..
 */
void LvlReader::read_lvl()
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
        path_dungeon_ppm += line;

        // Part treasures.
        getline(file, line);
        nb_treasures = int(stoi(line));
        for (int i = 0; i < nb_treasures; i++)
        {
            // Parse data in line correspoding to the Treasure.
            getline(file, line);
            auto tokens = parse_line(line);
            auto treasure = Treasure((unsigned int)stoi(tokens[0]),
                                     make_tuple((unsigned int)stoi(tokens[1]),
                                                (unsigned int)stoi(tokens[2])),
                                     tokens[3],
                                     stoi(tokens[4]));

            cout << treasure << endl;
            // TODO map with unique_ptr
            // assert(treasure != nullptr);
            // treasures.insert({treasure.get()->get_pos(), move(treasure)});
            treasures.insert({treasure.get_pos(), treasure});
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

/**
 * Read the ppm file associated with the level.
 * Create the corresponding decorative objects.
 */
void LvlReader::read_ppm()
{
    string line;
    ifstream file(path_dungeon_ppm);
    if (!file)
    {
        cout << "PPM file not found.\n";
        return;
    }
    else
    {
        // Check type of PPM.
        getline(file, line);
        if (line != "P3")
        {
            cout << "PPM type does not match." << endl;
            return;
        }

        // TODO check first char == '#' because comments can be anywhere.
        // Comment.
        getline(file, line);

        string ppm_code;
        int width, height, max_color;
        file >> width >> height >> max_color;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                unsigned int red, green, blue;
                file >> red >> green >> blue;
                if (!file)
                {
                    std::cerr << "Error reading from file around (" << y << "," << x << ")" << std::endl;
                    return;
                }
                std::cout << "RGB " << red << ", " << green << ", " << blue << std::endl;
                // TODO creat object.
                // Starter
                if (red == 255 && green == 0 && blue == 0)
                {
                    // Starter
                }
                // Exit.
                if (red == 0 && green == 255 && blue == 0)
                {
                    // Exit.
                }
                // Door.
                if (red == 170 && green == 119 && blue == 34)
                {
                    // Door.
                }
                // Water.
                if (red == 0 && green == 0 && blue == 255)
                {
                    // Water.
                }
                // Corridors.
                if (red == 255 && green == 255 && blue == 255)
                {
                    // Corridors.
                }
                // Wall.
                if (red == 0 && green == 0 && blue == 0)
                {
                    // Wall.
                }
            }
        }
    }
}
