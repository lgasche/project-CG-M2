
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

using namespace std;

#include <project/LevelReader.hpp>
#include <project/TreasureStorage.hpp>

/**
 * Parse the line describing an object or a monster.
 *
 * @param str line describing an object or a monster.
 *
 * @return a vector<string> of elements that make up the string.
 */
vector<string> LevelReader::parse_line(const string str)
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
void LevelReader::read_lvl_txt_and_creat_objects()
{
    unsigned int type_check = 0;
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

            // Treasure.
            if (tokens.size() == 7)
            {
                auto pos = make_tuple((unsigned int)stoi(tokens[1]), (unsigned int)stoi(tokens[2]));
                auto type = (unsigned int)stoi(tokens[4]);
                auto treasure = Treasure((unsigned int)stoi(tokens[0]), pos, tokens[3], type, stoi(tokens[5]), tokens[6]);
                std::cout << treasure << std::endl;
                // Storage don't exist.
                if (treasureStorages.count(type) == 0)
                {
                    map<tuple<unsigned int, unsigned int>, Treasure> treasures;
                    treasures.insert({pos, treasure});
                    auto storage = TreasureStorage(treasures);
                    treasureStorages.insert(make_pair(type, storage));
                }
                // Storage exist.
                if (treasureStorages.count(type) == 1)
                {
                    auto itr = treasureStorages.find(type);
                    auto storage = itr->second;
                    storage.add(pos, treasure);
                }
                // treasures.insert({pos, treasure});
            }

            // Weapon.
            if (tokens.size() == 8)
            {
                auto pos = make_tuple((unsigned int)stoi(tokens[1]), (unsigned int)stoi(tokens[2]));
                auto weapon = std::make_unique<Weapon>((unsigned int)stoi(tokens[0]), pos, tokens[3], (unsigned int)stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6]), tokens[7]);
                std::cout << *weapon << std::endl;
                weapons.insert({pos, move(weapon)});
            }
        }

        // Part monstrers.
        getline(file, line);
        nb_monsters = int(stoi(line));
        for (int i = 0; i < nb_monsters; i++)
        {
            // Todo add monster
            getline(file, line);
            auto tokens = parse_line(line);
            auto pos = make_tuple((unsigned int)stoi(tokens[1]), (unsigned int)stoi(tokens[2]));
            auto monster = Monster((unsigned int)stoi(tokens[0]), pos, tokens[3], (unsigned int)stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6]), stoi(tokens[7]), tokens[8]);
            std::cout << monster << std::endl;
            monsters.insert({pos, monster});
        }
    }
    file.close();
}

/**
 * Read the ppm file associated with the level.
 * Create the ascii vector describing the level corresponding to the ppm: vmap.
 *
 * Care the origin (0,0) is at the bottom left of the ppm file.
 *
 * @return vector<vector<char>> vmap.
 */
vector<vector<char>> LevelReader::read_ppm_to_vmap()
{
    vector<vector<char>> vmap;
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
        }

        // TODO check first char == '#' because comments can be anywhere.
        // Comment.
        getline(file, line);

        string ppm_code;
        int width, height, max_color;
        file >> width >> height >> max_color;

        for (int x = 0; x < height; x++)
        {
            vector<char> row;
            for (int y = 0; y < width; y++)
            {
                unsigned int red, green, blue;
                file >> red >> green >> blue;
                if (!file)
                {
                    std::cerr << "Error reading from file around (" << x << "," << y << ")" << std::endl;
                }
                // std::cout << "RGB " << red << ", " << green << ", " << blue << std::endl;
                // Starter
                if (red == 255 && green == 0 && blue == 0)
                {
                    row.push_back('s');
                }
                // Exit.
                if (red == 0 && green == 255 && blue == 0)
                {
                    row.push_back('e');
                }
                // Door.
                if (red == 170 && green == 119 && blue == 34)
                {
                    row.push_back('d');
                }
                // Water.
                if (red == 0 && green == 0 && blue == 255)
                {
                    row.push_back('v');
                }
                // Tunnel.
                if (red == 255 && green == 255 && blue == 255)
                {
                    row.push_back('t');
                }
                // Wall.
                if (red == 0 && green == 0 && blue == 0)
                {
                    row.push_back('w');
                }
            }
            vmap.push_back(row);
        }
    }
    // Change the origin position.
    reverse(vmap.begin(), vmap.end());
    return vmap;
}

/**
 * Read the vector corresponding to the map level.
 * Create the corresponding decorative objects.
 *
 * @param vmap a char vector ascii representation of the map lvl.
 */
void LevelReader::read_vmap_and_creat_decorative(const vector<vector<char>> vmap)
{
    for (int x = 0; x < vmap.size(); x++)
    {
        for (int y = 0; y < vmap[x].size(); y++)
        {
            //  TODO creat object.
            //  Starter.
            if (vmap[x][y] == 's')
            {
                start = make_tuple((unsigned int)x, (unsigned int)y);
                auto tunnel = create_tunnel(vmap, x, y);
                map_lvl.insert({make_tuple((unsigned int)x, (unsigned int)y), tunnel});
            }
            // Exit.
            if (vmap[x][y] == 'e')
            {
                // Exit.
                out = make_tuple((unsigned int)x, (unsigned int)y);
                auto tunnel = create_tunnel(vmap, x, y);
                map_lvl.insert({make_tuple((unsigned int)x, (unsigned int)y), tunnel});
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
                map_lvl.insert({make_tuple((unsigned int)x, (unsigned int)y), tunnel});
            }
            // Wall. // ATTENTION, il n'y a rien a faire pour les murs (et le code pour wall et water sont les mêmes)
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
Tunnel LevelReader::create_tunnel(const vector<vector<char>> vmap, const int x, const int y)
{
    bool wall_north = false;
    bool wall_east = false;
    bool wall_south = false;
    bool wall_west = false;

    if (x == 0 || vmap[x - 1][y] == 'w')
        wall_north = true;
    if (y == vmap[x].size() - 1 || vmap[x][y + 1] == 'w')
        wall_east = true;
    if (x == vmap.size() - 1 || vmap[x + 1][y] == 'w')
        wall_south = true;
    if (y == 0 || vmap[x][y - 1] == 'w')
        wall_west = true;

    return Tunnel(make_tuple((unsigned int)x, (unsigned int)y), wall_north, wall_east, wall_south, wall_west);
}

/**
 * Creat the current lvl.
 *
 * @return Level
 */
Level LevelReader::creat_lvl(const FilePath &applicationPath)
{
    // Read lvl txt file and creat objects : Treasures, Monstres..
    read_lvl_txt_and_creat_objects();

    auto vmap = read_ppm_to_vmap();

    for (int i = 0; i < vmap.size(); i++)
    {
        for (int j = 0; j < vmap[i].size(); j++)

        {
            std::cout << vmap[i][j] << " ";
        }

        std::cout << endl;
    }

    // Read vmap and creat decorative objects : Tunnel, Water..
    read_vmap_and_creat_decorative(vmap);

    std::cout << "Elements in mp1 are\n";
    std::cout << "KEY\tELEMENT\n";
    for (auto itr = map_lvl.begin(); itr != map_lvl.end(); ++itr)
    {
        std::cout
            << '\t'
            << itr->second << '\n';
    }

    return Level(map_lvl, treasureStorages, monsters, start, out, applicationPath);
}