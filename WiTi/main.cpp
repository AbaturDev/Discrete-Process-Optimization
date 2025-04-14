#include <iostream>
#include "scheduler.hpp"

using namespace std;

int main()
{
    int const fileCount = 11;
    int sum = 0;

    for(int i = 0; i < fileCount; i++)
    {
        Scheduler scheduler;

        string filePath = "data/data" + to_string(i+10) + ".txt";

        scheduler.readFileContent(filePath);
        scheduler.witiDP();
        int coast = scheduler.delayCost();

        cout << endl << "~~~~~~~~" << i+10 << "~~~~~~~~~" << endl;
        cout<< coast << endl;
        scheduler.displayOrder();

        sum += coast;
    }

    cout << endl << "Sum: " << sum << endl;

    return 0;
}