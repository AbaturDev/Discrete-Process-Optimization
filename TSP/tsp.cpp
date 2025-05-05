#include "tsp.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>

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
    auto rng = std::default_random_engine {};
    shuffle(begin(cities), end(cities), rng);
}

string Tsp::getSolutionOrder()
{
    string order;

    for(const City& city : cities)
    {
        order += to_string(city.id) + " ";
    }

    return order;
}

float Tsp::getSolutionDistance()
{
    float distance = 0;

    for (int i = 0; i < cities.size() - 1; i++)
    {
        distance += countDistance(cities[i], cities[i+1]);
    }

    return distance;
}

void Tsp::writeSolution()
{
    const string filePath = "data/solution_order.txt";
    ofstream file(filePath);

    file << getSolutionOrder();

    file.close();
}

float Tsp::countDistance(const City& cityA, const City& cityB) const
{
    float x_diff_square = pow(cityB.x -  cityA.x, 2);
    float y_diff_square = pow(cityB.y - cityA.y, 2);

    float distance = sqrt(x_diff_square + y_diff_square);

    return distance;
}
