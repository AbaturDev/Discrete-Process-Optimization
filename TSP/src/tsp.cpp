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
            cities.reserve(size + 1);
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
    City currentCity = cities.front();

    vector<City> remainingCites = cities;
    remainingCites.erase(remainingCites.begin());

    vector<City> route;
    route.push_back(currentCity);

    while(!remainingCites.empty())
    {
        auto nearestCity = min_element(remainingCites.begin(), remainingCites.end(), [&](const City& a, const City& b)
            {
                return countDistance(currentCity, a) < countDistance(currentCity, b);
            });
        

        currentCity = *nearestCity;
        route.push_back(currentCity);
        
        remainingCites.erase(nearestCity);
    }

    cities = route;
}

void Tsp::randomSolution()
{
    auto rng = std::default_random_engine {};
    std::shuffle(cities.begin() + 1, cities.end(), rng);
}

string Tsp::getSolutionOrder()
{
    string order;

    for(const City& city : cities)
    {
        order += to_string(city.id) + " ";
    }

    if(!cities.empty())
    {
        order += to_string(cities.front().id);
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

    if(!cities.empty())
    {
        distance += countDistance(cities.back(), cities.front());
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

void Tsp::simulatedAnnealing(float tempStart, float alpha, int iterations, int innerLoop)
{
    randomSolution();

    vector<City> currentPath = cities;
    std::rotate(currentPath.begin(), currentPath.begin() + 1, currentPath.end()); // Przesuwamy, by miasto 1 było na początku
    float currentDist = getSolutionDistance();

    vector<City> bestPath = currentPath;
    float bestDist = currentDist;

    float temp = tempStart;

    for (int i = 0; i < iterations; ++i)
    {
        for (int j = 0; j < innerLoop; ++j)
        {
            int a = rand() % (currentPath.size() - 1);
            int b = rand() % (currentPath.size() - 1);
            if (a > b) std::swap(a, b);

            std::reverse(currentPath.begin() + a, currentPath.begin() + b + 1);

            float newDist = 0.0f;
            for (size_t k = 0; k < currentPath.size() - 1; ++k)
                newDist += countDistance(currentPath[k], currentPath[k + 1]);
            newDist += countDistance(currentPath.back(), currentPath.front());

            float delta = newDist - currentDist;

            if (delta < 0 || (exp(-delta / temp) > ((float)rand() / RAND_MAX)))
            {
                currentDist = newDist;
                if (currentDist < bestDist)
                {
                    bestDist = currentDist;
                    bestPath = currentPath;
                }
            }
            else
            {
                std::reverse(currentPath.begin() + a, currentPath.begin() + b + 1);
            }
        }

        temp *= alpha;
    }

    cities = bestPath;
}

float Tsp::countDistance(const City& cityA, const City& cityB) const
{
    float x_diff_square = pow(cityB.x -  cityA.x, 2);
    float y_diff_square = pow(cityB.y - cityA.y, 2);

    float distance = sqrt(x_diff_square + y_diff_square);

    return distance;
}
