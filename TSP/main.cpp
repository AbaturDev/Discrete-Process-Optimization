#include <iostream>
#include "tsp.hpp"

using namespace std;

int main()
{
    Tsp tsp;
    tsp.readFileContent("data/burma14.tsp", 8);
    tsp.get_order();
    
    return 0;
}