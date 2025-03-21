#include <iostream>
#include <fstream>

using namespace std;

struct Task
{
    int R;
    int P;
    int Q;
};

void readFileContent(string dataFile, Task*& tasks, int& numberOfTasks)
{
    ifstream file(dataFile);

    if (!file.is_open())
    {
        cerr << "Error: Can not open the '" + dataFile + "' file" << endl;
        return;
    }

    file >> numberOfTasks;

    tasks = new Task[numberOfTasks];

    for (int i = 0; i < numberOfTasks; i++)
    {
        file >> tasks[i].R >> tasks[i].P >> tasks[i].Q;
    }

    file.close();
}

void scheduleWithoutSorting(Task* tasks, int numberOfTasks)
{
    int time = 0;
    int C_max = 0;

    for (int i = 0; i<numberOfTasks; i++)
    {
        if (time < tasks[i].R)
        {
            time = tasks[i].R;
        }
        time += tasks[i].P;
        C_max = max(C_max, time + tasks[i].Q);
    }

    cout << C_max << endl;
}

int main()
{
    string fileName = "data3.txt";
    Task* tasks = nullptr;
    int numberOfTasks = 0;

    readFileContent(fileName, tasks, numberOfTasks);

    if (tasks == nullptr)
    {
        cerr << "Error: No tasks loaded" << endl;
        return 1;
    }

    scheduleWithoutSorting(tasks, numberOfTasks);

    delete[] tasks;

    return 0;
}
