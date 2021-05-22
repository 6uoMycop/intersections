#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <algorithm>


typedef struct {
    int32_t x;
    int32_t y;
} point;

typedef struct {
    point point1, point2;
} segment;

/*
* Initialization function: here we fill the segments vector from a file
*/
bool init(const char* file_path, std::vector<segment>* segments)
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
        int32_t x1, y1, x2, y2;

        getline(s, field, ',');
        x1 = std::stoi(field);
        getline(s, field, ',');
        y1 = std::stoi(field);
        getline(s, field, ',');
        x2 = std::stoi(field);
        getline(s, field, ',');
        y2 = std::stoi(field);

        segment tmp_segment{
            {
                x1,
                y1
            },
            {
                x2,
                y2
            }
        };

        if (!segments->empty())
        {
            if (segments->back().point2.x != tmp_segment.point1.x &&
                segments->back().point2.y != tmp_segment.point1.y)
            {
                return false;
            }
        }

        segments->push_back(tmp_segment);
    }

    if ((segments->front().point1.x != segments->back().point2.x &&
         segments->front().point1.y != segments->back().point2.y) ||
         segments->empty())
    {
        return false;
    }

    return true;
}

inline int32_t direction(const point& pi, const point& pj, const point& pk)
{
    return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
}

inline bool on_segment(const point &pi, const point &pj, const point &pk)
{
    if ((std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)) &&
        (std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)))
    {
        return true;
    }
    return false;
}

/*
* Check if two given segments intersect each other
*/
bool segments_intersect(const segment &s1, const segment& s2)
{
    point p1 = s1.point1;
    point p2 = s1.point2;
    point p3 = s2.point1;
    point p4 = s2.point2;

    int32_t d1 = direction(p3, p4, p1);
    int32_t d2 = direction(p3, p4, p2);
    int32_t d3 = direction(p1, p2, p3);
    int32_t d4 = direction(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
    {
        return true;
    }
    else if (d1 == 0 && on_segment(p3, p4, p1))
    {
        return true;
    }
    else if (d2 == 0 && on_segment(p3, p4, p2))
    {
        return true;
    }
    else if (d3 == 0 && on_segment(p1, p2, p3))
    {
        return true;
    }
    else if (d4 == 0 && on_segment(p1, p2, p4))
    {
        return true;
    }

    return false;
}

inline bool segments_equal_or_adjacent(const size_t i, const size_t j, const size_t len)
{
    if ((i == j) ||
        (i + 1 == j) ||
        (j + 1 == i) ||
        (i == len - 1 && j == 0) ||
        (i == 0 && j == len - 1))
    {
        return true;
    }
    return false;
}

int32_t number_of_intersections(const std::vector<segment> &segments)
{
    int32_t number = 0;
    size_t len = segments.size();

    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i; j < len; j++)
        {
            if (!segments_equal_or_adjacent(i, j, len))
            {
                if (segments_intersect(segments[i], segments[j]))
                {
                    number++;
                }
            }
        }
    }

    return number;
}

/*
* USAGE: <executable_name>.exe <path/to/file/with/segments/data>.csv
* FILE FORMAT:
* (every line represents vector ((x1_i,y1_i),(x2_i,y2_i)))
* (coordinates are positive integer values)
* (second point of  i-th   vector MUST be the same as first point of  i+1-th  vector)
* (second point of  first  vector MUST be the same as first point of  last    vector)
* <x1_1>,<y1_1>,<x2_1>,<y2_1>
* <x2_1>,<y2_1>,<x2_2>,<y2_2>
* ...
* <xn_1>,<yn_1>,<x1_1>,<y1_1>
* EXAMPLE FILE:
* 3,9,156,2
* 156,2,29,0
* 29,0,3,9
*/
int main(int argc, char* argv[])
{
    std::vector<segment> segments;
    
    if (argc != 2)
    {
        if (!init("C:\\data.csv", &segments))
        {
            std::cout << "Initialization uncuccessful. Check input file. Terminating." << std::endl;
            return -1;
        }
    }
    else
    {
        if (!init(argv[1], &segments))
        {
            std::cout << "Initialization uncuccessful. Check input file. Terminating." << std::endl;
            return -1;
        }
    }

    std::cout << "Number of intersections: " << number_of_intersections(segments) << std::endl << std::endl;
    std::cout << "Press enter ";

    getchar();

    return 0;
}
