#ifndef TSP_HPP
#define TSP_HPP

#include "city.hpp"
#include <vector>
#include <string>

class Tsp
{
private:
    std::vector<City> cities;

public:
    void readFileContent(const std::string& filePath, int skipLines);
    void nearestNeighborMethod();
    void randomSolution();
    std::string getSolutionOrder();
    float getSolutionDistance();
    void writeSolution();

private:
    float countDistance(const City& cityA, const City& cityB) const;
};

#endif