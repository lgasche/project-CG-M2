#include "LvlReader.hpp"

int main(int argc, char *argv[])
{

    // TODO commandReader
    // TowerSimulation simulation{argc, argv};

    std::cout << "Test : " << argv[1] << std::endl;

    string filename = argv[1];
    auto read = LvlReader(filename);
    read.get_infos();
    read.build();
    read.get_infos();

    return 0;
}