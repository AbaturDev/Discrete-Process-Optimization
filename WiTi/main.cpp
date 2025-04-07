#include <iostream>
#include "scheduler.hpp"

using namespace std;

int main()
{
    cout << "Hello World" << endl;

    Scheduler scheduler;

    scheduler.readFileContent("data/data10.txt");
    cout << scheduler.delayCost() << endl;

    return 0;
}