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
    std::vector<point> tmp_points;

    if (!file_in || file_in.peek() == std::ifstream::traits_type::eof())
    {
        return false;
    }

    while (std::getline(file_in, line))
    {
        std::istringstream s(line);
        std::string field;
        int32_t x, y;

        getline(s, field, ',');
        x = std::stoi(field);
        getline(s, field, ',');
        y = std::stoi(field);

        point tmp_point{
            x,
            y
        };

        tmp_points.push_back(tmp_point);
    }

    file_in.close();

    if (tmp_points.size() < 3)
    {
        std::cout << "Input file contains only " << tmp_points.size() << " points" << std::endl;
        return false;
    }
         
    if (tmp_points.front().x != tmp_points.back().x ||
        tmp_points.front().y != tmp_points.back().y)
    {
        std::cout << "Input line is not a circuit" << std::endl;
        return false;
    }

    for (std::vector<point>::iterator it = tmp_points.begin() + 1, it_prev = tmp_points.begin();
        it != tmp_points.end();
        ++it, ++it_prev)
    {
        if (it_prev->x == it->x && it_prev->y == it->y)
        {
            std::cout << "Input file contains \"void\" line (" << 
                it_prev->x << ","<< it_prev->y << "), (" << it->x << ","<< it->y << ")" 
                << std::endl;
            return false;
        }

        segment tmp_segment{
            {
                it_prev->x,
                it_prev->y
            },
            {
                it->x,
                it->y
            }
        };

        segments->push_back(tmp_segment);
    }

    return true;
}

inline int32_t direction(const point& pi, const point& pj, const point& pk)
{
    return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
}

inline bool on_segment(const point& pi, const point& pj, const point& pk)
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
bool segments_intersect(const segment& s1, const segment& s2)
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

int32_t number_of_intersections(const std::vector<segment>& segments)
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
* (every line represents a point (x_i,y_i))
* (coordinates are positive integer values)
* (first point MUST be the same as last point)
* (minimum 3 points allowed)
* <x_1>,<y_1>
* <x_2>,<y_2>
* ...
* <x_1>,<y_1>
* EXAMPLE FILE:
* 3,9
* 156,2
* 29,0
* 3,9
*/
int main(int argc, char* argv[])
{
    std::vector<segment> segments;

    if (argc != 2)
    {
        if (!init("data.csv", &segments))
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

    return 0;
}
