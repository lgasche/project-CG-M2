#include "LvlReader.hpp"

int main(int argc, char *argv[])
{

    // TODO commandReader

    std::cout << "Test : " << argv[1] << std::endl;

    string filename = argv[1];
    auto read = LvlReader(filename);
    read.read_lvl();
    std::cout << read << std::endl;
    read.read_ppm();

    return 0;
}