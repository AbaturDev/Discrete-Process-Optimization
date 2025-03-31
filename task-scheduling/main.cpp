#include <iostream>
#include "scheduler.hpp"

using namespace std;

int main()
{
    const int filesCount = 4;
    int sum = 0;

    for(int i=0; i<filesCount; i++)
    {
        Scheduler scheduler;

        string fileName =  "data/data" + to_string(i+1) + ".txt";

        scheduler.readFileContent(fileName);
        //scheduler.sortRQ();
        scheduler.schrage();
        //scheduler.display_order();
        cout << scheduler.calculateC_max() << endl;

        sum += scheduler.calculateC_max();
    }

    cout << sum << endl;

    return 0;
}
