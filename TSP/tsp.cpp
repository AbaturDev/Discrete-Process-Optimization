#include "tsp.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

void Tsp::readFileContent(const std::string& filePath, int skipLines)
{
    ifstream file(filePath);

    if(!file.is_open())
    {
        cerr << "Can not open file " + filePath << endl;
        return;
    }

    int lineCounter = 0;
    string line;

    while(lineCounter++ < skipLines && getline(file, line))
    {   
        if (line == "DIMENSION")
        {
            int size = 0;
            file >> size;
            cities.reserve(size);
        }

        continue;   
    }

    while(getline(file, line))
    {
        if (line == "EOF")
        {
            break;
        }
        
        istringstream iss(line);
        City city;
        if (!(iss >> city.id >> city.x >> city.y))
        {
            cerr << "Error parsing city from line: " << line << endl;
            continue;
        }

        cities.push_back(city);
    }

    file.close();
}

void Tsp::nearestNeighborMethod()
{
}

void Tsp::randomSolution()
{
}

string Tsp::get_order()
{
    for(const City& city : cities)
    {
        cout << city.id << endl;
    }

    cout << countDistance(cities[0], cities[1]) << endl;

    return string();
}

float Tsp::countDistance(const City& cityA, const City& cityB) const
{
    float x_diff_square = pow(cityB.x -  cityA.x, 2);
    float y_diff_square = pow(cityB.y - cityA.y, 2);

    float distance = sqrt(x_diff_square + y_diff_square);

    return distance;
}
