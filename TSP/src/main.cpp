#include <iostream>
#include "tsp.hpp"

using namespace std;

int main()
{
    Tsp tsp;
    tsp.readFileContent("data/burma14.tsp", 8);
    tsp.randomSolution();

    cout << tsp.getSolutionOrder() << endl;
    cout << tsp.getSolutionDistance() << endl;

    tsp.nearestNeighborMethod();
    
    cout << tsp.getSolutionOrder() << endl;
    cout << tsp.getSolutionDistance() << endl;
    
    tsp.writeSolution();

    return 0;
}