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
    //void simulatedAnnealing(float tempStart = 10000.0f, float alpha = 0.976f, int iterations = 400, int innerLoop = 100);   // default
    void simulatedAnnealing(float tempStart = 10000.0f, float alpha = 0.976f, int iterations = 400, int innerLoop = 200);   // kroA100
    //void simulatedAnnealing(float tempStart = 12500.0f, float alpha = 0.978f, int iterations = 500, int innerLoop = 300);   // kroA150
    //void simulatedAnnealing(float tempStart = 18000.0f, float alpha = 0.985f, int iterations = 600, int innerLoop = 400);   // kroA200

    void geneticAlghoritm(int populationSize, int generations, float mutationRate);

private:
    float countDistance(const City& cityA, const City& cityB) const;
    float evaluate(const std::vector<City>& individual);
    void mutate(std::vector<City>& individual, float mutationRate);
    std::vector<City> crossover(const std::vector<City>& parent1, const std::vector<City>& parent2);
};

#endif