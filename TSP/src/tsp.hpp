#ifndef TSP_HPP
#define TSP_HPP

#include "city.hpp"
#include <vector>
#include <string>

class Tsp
{
private:
    int size;
    std::vector<City> cities;

public:
    void readFileContent(const std::string& filePath, int skipLines);
    void nearestNeighborMethod();
    void twoOpt();
    void randomSolution();
    std::string getSolutionOrder();
    float getSolutionDistance();
    void writeSolution();
    //void simulatedAnnealing(float tempStart = 10000.0f, float alpha = 0.976f, int iterations = 450, int innerLoop = 450);
    void simulatedAnnealing(float tempStart = 10000.0f, float alpha = 0.976f, int iterations = 400, int innerLoop = 200); //kroA100 - optimal solution

private:
    float countDistance(const City& cityA, const City& cityB) const;
};

#endif