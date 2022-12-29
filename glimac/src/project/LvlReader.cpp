#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include <project/LvlReader.hpp>
#include <project/Treasure.hpp>
#include <project/Tunnel.hpp>

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
            auto treasure = Treasure((unsigned int)stoi(tokens[0]), make_tuple((unsigned int)stoi(tokens[1]), (unsigned int)stoi(tokens[2])), tokens[3]);
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

/**
 * Read the ppm file associated with the level.
 * Create the corresponding decorative objects.
 *
 * @return vector<vector<char>> map.
 */
vector<vector<char>> LvlReader::read_ppm()
{
    vector<vector<char>> map;
    string line;
    ifstream file(path_dungeon_ppm);
    if (!file)
    {
        cout << "PPM file not found.\n";
    }
    else
    {
        // Check type of PPM.
        getline(file, line);
        if (line != "P3")
        {
            cout << "PPM type does not match." << endl;
            return map;
        }

        // TODO check first char == '#' because comments can be anywhere.
        // Comment.
        getline(file, line);

        string ppm_code;
        int width, height, max_color;
        file >> width >> height >> max_color;

        for (int y = 0; y < height; y++)
        {
            vector<char> row;
            for (int x = 0; x < width; x++)
            {
                unsigned int red, green, blue;
                file >> red >> green >> blue;
                if (!file)
                {
                    std::cerr << "Error reading from file around (" << x << "," << y << ")" << std::endl;
                    return map;
                }
                std::cout << "RGB " << red << ", " << green << ", " << blue << std::endl;
                // TODO creat object.
                // Starter
                if (red == 255 && green == 0 && blue == 0)
                {
                    // Starter
                    row.push_back('s');
                }
                // Exit.
                if (red == 0 && green == 255 && blue == 0)
                {
                    // Exit.
                    row.push_back('e');
                }
                // Door.
                if (red == 170 && green == 119 && blue == 34)
                {
                    // Door.
                    row.push_back('d');
                }
                // Water.
                if (red == 0 && green == 0 && blue == 255)
                {
                    // Water.
                }
                // Tunnel.
                if (red == 255 && green == 255 && blue == 255)
                {
                    row.push_back('t');
                }
                // Wall.
                if (red == 0 && green == 0 && blue == 0)
                {
                    // Wall.
                    row.push_back('w');
                }
            }
            map.push_back(row);
        }
    }
    return map;
}

/**
 * Read the vector corresponding to the map.
 * Create the corresponding decorative objects.
 *
 * @param vmap
 */
void LvlReader::read_map(const vector<vector<char>> vmap)
{

    for (int y = 0; y < vmap.size(); y++)
    {
        for (int x = 0; x < vmap[y].size(); x++)
        {

            // TODO creat object.
            // Starter
            if (vmap[x][y] == 's')
            {
                // Starter
            }
            // Exit.
            if (vmap[x][y] == 'e')
            {
                // Exit.
            }
            // Door.
            if (vmap[x][y] == 'd')
            {
                // Door.
            }
            // Water.
            if (vmap[x][y] == 'w')
            {
                // Water.
            }
            // Tunnel.
            if (vmap[x][y] == 't')
            {
                // todo in function : check wall
                auto tunnel = create_tunnel(vmap, x, y);
                mp.insert({make_tuple((unsigned int)x, (unsigned int)y), tunnel});
            }
            // Wall.
            if (vmap[x][y] == 'w')
            {
                // Wall.
            }
        }
    }
}

/**
 * Check wall for create a tunnel.
 *
 * @return Tunnel
 */
Tunnel LvlReader::create_tunnel(const vector<vector<char>> vmap, const int x, const int y)
{
    bool wall_north = false;
    bool wall_east = false;
    bool wall_south = false;
    bool wall_west = false;

    if (vmap[x][y - 1] == 'w' || y < 0)
        wall_north = true;
    if (vmap[x + 1][y] == 'w' || x > vmap[x].size())
        wall_east = true;
    if (vmap[x][y + 1] == 'w' || y > vmap.size())
        wall_south = true;
    if (vmap[x - 1][y] == 'w' || x < 0)
        wall_west = true;

    return Tunnel(make_tuple((unsigned int)x, (unsigned int)y), wall_north, wall_east, wall_south, wall_west);
}