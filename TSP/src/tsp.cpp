#include "tsp.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <unordered_set>

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

    route.push_back(cities.front());

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

    if(!cities.empty() && cities.front().id != cities.back().id)
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

    if(!cities.empty() && cities.front().id != cities.back().id)
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
    std::rotate(currentPath.begin(), currentPath.begin() + 1, currentPath.end());
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

float Tsp::countDistance(const City &cityA, const City &cityB) const
{
    float x_diff_square = pow(cityB.x -  cityA.x, 2);
    float y_diff_square = pow(cityB.y - cityA.y, 2);

    float distance = sqrt(x_diff_square + y_diff_square);

    return distance;
}

void Tsp::twoOpt()
{
    bool improvement = true;
    int sizeCities = cities.size();

    while (improvement)
    {
        improvement = false;
        for (int i = 1; i < sizeCities - 2; ++i)
        {
            for (int k = i + 1; k < sizeCities - 1; ++k)
            {
                float delta = 
                    countDistance(cities[i - 1], cities[k]) +
                    countDistance(cities[i], cities[k + 1]) -
                    countDistance(cities[i - 1], cities[i]) -
                    countDistance(cities[k], cities[k + 1]);

                if (delta < -1e-6)
                {
                    reverse(cities.begin() + i, cities.begin() + k + 1);
                    improvement = true;
                }
            }
        }
    }
}

float Tsp::evaluate(const vector<City>& individual)
{
    float dist = 0.0f;
    for (int i = 0; i < individual.size() - 1; ++i)
        dist += countDistance(individual[i], individual[i + 1]);
    dist += countDistance(individual.back(), individual.front());
    return dist;
}

void Tsp::mutate(vector<City>& individual, float mutationRate)
{
    if ((float)rand() / RAND_MAX < mutationRate)
    {
        int i = 1 + rand() % (individual.size() - 2);
        int j = i + 1 + rand() % (individual.size() - i - 1);
        std::reverse(individual.begin() + i, individual.begin() + j);
    }
}

vector<City> Tsp::crossover(const vector<City>& parent1, const vector<City>& parent2)
{
    int size = parent1.size();
    int start = rand() % size;
    int end = start + rand() % (size - start);

    vector<City> child(size, City{-1, -1, -1});
    unordered_set<int> used;

    for (int i = start; i <= end; ++i)
    {
        child[i] = parent1[i];
        used.insert(parent1[i].id);
    }

    int idx = (end + 1) % size;
    for (int i = 0; i < size; ++i)
    {
        const City& c = parent2[(end + 1 + i) % size];
        if (used.count(c.id) == 0)
        {
            child[idx] = c;
            idx = (idx + 1) % size;
        }
    }

    return child;
}

void Tsp::geneticAlgorithm(int populationSize, int generations, float mutationRate)
{
    std::vector<std::vector<City>> population;

    for (int i = 0; i < populationSize; i++)
    {
        std::vector<City> individual = cities;
        std::shuffle(individual.begin() + 1, individual.end(), rng);
        population.push_back(individual);
    }

    float bestDistance = std::numeric_limits<float>::max();
    std::vector<City> bestSolution;

    for (int g = 0; g < generations; g++)
    {
        std::sort(population.begin(), population.end(), [&](const auto& a, const auto& b)
        {
            return evaluate(a) < evaluate(b);
        });

        if (evaluate(population.front()) < bestDistance)
        {
            bestDistance = evaluate(population.front());
            bestSolution = population.front();
        }

        int eliteCount = std::max(1, (int)(populationSize * 0.2));

        std::vector<std::vector<City>> newPopulation(population.begin(), population.begin() + eliteCount);

        while (newPopulation.size() < populationSize)
        {
            int i1 = rand() % eliteCount;
            int i2 = rand() % eliteCount;
            auto child = crossover(population[i1], population[i2]);
            mutate(child, mutationRate);
            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    cities = bestSolution;
}
