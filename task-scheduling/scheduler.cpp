#include "scheduler.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Scheduler::partition(int low, int high)
{
    int pivot = tasks[high].R;

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if(tasks[j].R <= pivot)
        {
            i++;
            swap(tasks[i], tasks[j]);
        }
    }

    swap(tasks[i+1], tasks[high]);

    return i + 1;
}

void Scheduler::quickSort(int low, int high)
{
    if(low < high)
    {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void Scheduler::readFileContent(string dataFile)
{
    ifstream file(dataFile);

    if (!file.is_open())
    {
        cerr << "Error: Can not open the '" + dataFile + "' file" << endl;
        return;
    }

    int numberOfTasks = 0;
    file >> numberOfTasks;

    tasks.reserve(numberOfTasks);

    for (int i = 0; i < numberOfTasks; i++)
    {
        Task task;
        file >> task.R >> task.P >> task.Q;
        tasks.push_back(task);
    }

    file.close();
}

int Scheduler::calculateC_max()
{
    int time = 0;
    int C_max = 0;

    for (const Task& task : tasks)
    {
        if (time < task.R)
        {
            time = task.R;
        }
        time += task.P;
        C_max = max(C_max, time + task.Q);
    }

    return C_max;
}

const vector<Task>& Scheduler::getTasks() const
{
    return tasks;
}

int Scheduler::sortRQ()
{
    int bestC_max = calculateC_max();

    for (int i = 0; i < tasks.size(); i++)
    {
        for (int j = i + 1; j < tasks.size(); j++)
        {
            swap(tasks[i], tasks[j]);

            int newC_max = calculateC_max();

            if (newC_max < bestC_max)
            {
                bestC_max = newC_max;
            }

            swap(tasks[i], tasks[j]);
        }
    }

    return bestC_max;
}
