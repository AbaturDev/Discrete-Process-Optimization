#include <iostream>
#include <chrono>
#include "tsp.hpp"

using namespace std;

int main()
{
    Tsp tsp;
    tsp.readFileContent("data/kroA100.tsp", 6);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    //tsp.randomSolution();

    //tsp.nearestNeighborMethod();
    //tsp.twoOpt();

    //tsp.simulatedAnnealing();
    tsp.geneticAlgorithm(200, 1000, 0.17);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;
    cout << "Order: " << tsp.getSolutionOrder() << endl;
    cout << "Distance: " << tsp.getSolutionDistance() << endl;
    
    tsp.writeSolution();

    return 0;
}
