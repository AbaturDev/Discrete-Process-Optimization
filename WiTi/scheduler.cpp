#include "scheduler.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Scheduler::readFileContent(string filePath)
{
    ifstream file(filePath);

    if(!file.is_open())
    {
        cerr << "Can not open file " + filePath << endl;
        return;
    }

    int size = 0;
    file >> size;

    tasks = vector<Task>(size);

    for (int i = 0; i < size; i++)
    {
        Task task;
        task.id = i + 1;
        file >>  task.P >> task.W >> task.D;
        
        tasks.push_back(task);
    }

    file.close();
}

void Scheduler::displayOrder()
{
    for (const Task& task: tasks)
    {
        cout << task.id << " ";
    }
    cout << endl;
}

const vector<Task>& Scheduler::getTasks() const
{
    return tasks;
}

int Scheduler::delayCost()
{
    int currentTime = 0;
    int coast = 0;

    for(const Task& task : tasks)
    {
        currentTime += task.P;

        if(currentTime > task.D)
        {
            coast += (currentTime - task.D) * task.W;
        }
    }

    return coast;
}