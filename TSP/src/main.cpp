#include <iostream>
#include "tsp.hpp"

using namespace std;

int main()
{
    Tsp tsp;
    tsp.readFileContent("data/kroA100.tsp", 6);
    tsp.randomSolution();

    //tsp.nearestNeighborMethod();
    //tsp.simulatedAnnealing();
    //tsp.twoOpt();
    
    cout << tsp.getSolutionOrder() << endl;
    cout << tsp.getSolutionDistance() << endl;
    
    tsp.writeSolution();

    return 0;
}