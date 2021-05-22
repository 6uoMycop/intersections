#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>


typedef struct {
    struct {
        uint32_t x;
        uint32_t y;
    } point1, point2;
} segment;

std::vector<segment> segments;

/*
* Initialization function: here we fill the segments vector from a file
*/
bool init(const char* file_path)
{
    std::ifstream file_in(file_path);
    std::string line;

    if (!file_in)
    {
        return false;
    }

    while (std::getline(file_in, line))
    {
        std::istringstream s(line);
        std::string field;
        segment tmp_segment;
        uint32_t x1, y1, x2, y2;

        getline(s, field, ',');
        x1 = std::stoi(field);
        getline(s, field, ',');
        tmp_point.p2 = std::stoi(field);

        segments.push_back(tmp_point);
    }
    return true;
}

/*
*
*/
bool segments_intersect()
{

}

/*
* USAGE: <executable_name>.exe <path/to/file/with/segments/data>.csv
* FILE FORMAT:
* (every line represents vector ((x1_i,y1_i),(x2_i,y2_i)))
* (coordinates are positive integer values)
* <x1_1>,<y1_1>,<x2_1>,<y2_1>
* <x1_2>,<y1_2>,<x2_2>,<y2_2>
* ...
* EXAMPLE FILE:
* 3,9,156,2
* 0,1,29,0
*/
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Pass data file path as an option on next run. Terminating." << std::endl;
        return -2;
    }

    if (!init(argv[1]))
    {
        std::cout << "Initialization uncuccessful. Probably check input file. Terminating." << std::endl;
        return -1;
    }



    return 0;
}
