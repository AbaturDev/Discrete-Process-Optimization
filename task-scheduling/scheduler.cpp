#include "scheduler.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

void Scheduler::sortRQ(int maxIterations, int tabuSize)
{
    quickSort(0, tasks.size() - 1);
    
    vector<Task> bestSolution = tasks;
    int bestC_max = calculateC_max();
    unordered_set<string> tabuList;

    for (int iter = 0; iter < maxIterations; iter++)
    {
        vector<Task> bestNeighbor = tasks;
        int bestNeighborC_max = bestC_max;
        int swapIdx1 = -1, swapIdx2 = -1;

        for (size_t i = 0; i < tasks.size() - 1; i++)
        {
            for (size_t j = i + 1; j < tasks.size(); j++)
            {
                swap(tasks[i], tasks[j]);
                int newC_max = calculateC_max();
                string move = to_string(i) + "," + to_string(j);
                if (newC_max < bestNeighborC_max && tabuList.find(move) == tabuList.end())
                {
                    bestNeighborC_max = newC_max;
                    bestNeighbor = tasks;
                    swapIdx1 = i;
                    swapIdx2 = j;
                }
                swap(tasks[i], tasks[j]);
            }
        }

        if (swapIdx1 != -1)
        {
            tabuList.insert(to_string(swapIdx1) + "," + to_string(swapIdx2));
            if (tabuList.size() > tabuSize) tabuList.erase(tabuList.begin());
            tasks = bestNeighbor;
            bestC_max = bestNeighborC_max;
        }
    }
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
