#include "scheduler.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static bool compareQ(const Task &a, const Task &b)
{
    return a.Q < b.Q;
}

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
        task.id = i + 1;
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

void Scheduler::sortRQ()
{
    quickSort(0, tasks.size() - 1);
    
    int bestC_max = calculateC_max();
    vector<Task> best_tasks = tasks;

    for (int i = 0; i < tasks.size(); i++)
    {
        for (int j = i + 1; j < tasks.size(); j++)
        {
            swap(tasks[i], tasks[j]);

            int newC_max = calculateC_max();

            if (newC_max < bestC_max)
            {
                bestC_max = newC_max;
                best_tasks = tasks;
            }

            swap(tasks[i], tasks[j]);
        }
    }

    tasks = best_tasks;
}

void Scheduler::schrage()
{
    quickSort(0, tasks.size() - 1);

    vector<Task> N = tasks;
    vector<Task> G;
    vector<Task> order;
    
    int t = 0;
    int C_max = 0;

    while(!N.empty() || !G.empty())
    {
        while(!N.empty() && N.front().R <= t)
        {
            G.push_back(N.front());
            N.erase(N.begin());
        }

        if(!G.empty())
        {
            vector<Task>::iterator maxQ_it = max_element(G.begin(), G.end(), compareQ);

            Task e = *maxQ_it;
            G.erase(maxQ_it);

            order.push_back(e);
            t += e.P;
            C_max = max(C_max, t + e.Q);
        }
        else
        {
            t = N.front().R;
        }
    }

    tasks = order;
}

void Scheduler::display_order()
{
    for (const Task& task : tasks)
    {
        cout << task.id << " ";
    } 
}
