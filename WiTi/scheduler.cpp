#include "scheduler.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

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

    tasks.reserve(size);

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

void Scheduler::witiDP()
{
    int n = tasks.size();
    int size = 1 << n; 
    vector<int> dp(size, INT_MAX);
    vector<int> prev(size, -1);     
    vector<int> lastTask(size, -1); 

    dp[0] = 0;

    for (int mask = 0; mask < size; ++mask)
    {
        int time = 0;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                time += tasks[i].P;
            }
        }

        for (int j = 0; j < n; ++j)
        {
            if (!(mask & (1 << j)))
            {
                int nextMask = mask | (1 << j);
                int completionTime = time + tasks[j].P;
                int tardiness = max(0, completionTime - tasks[j].D);
                int cost = dp[mask] + tardiness * tasks[j].W;

                if (cost < dp[nextMask])
                {
                    dp[nextMask] = cost;
                    prev[nextMask] = mask;
                    lastTask[nextMask] = j;
                }
            }
        }
    }

    vector<Task> optimalOrder;
    int mask = size - 1;
    while (mask)
    {
        int taskIndex = lastTask[mask];
        optimalOrder.push_back(tasks[taskIndex]);
        mask = prev[mask];
    }

    reverse(optimalOrder.begin(), optimalOrder.end());

    tasks = optimalOrder;
}
