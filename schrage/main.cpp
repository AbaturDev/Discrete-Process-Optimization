#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Task
{
    int R;
    int P;
    int Q;
};

int partition(vector<Task>& tasks, int low, int high)
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

void quickSort(vector<Task>& tasks, int low, int high)
{
    if(low < high)
    {
        int pi = partition(tasks, low, high);

        quickSort(tasks, low, pi - 1);
        quickSort(tasks, pi + 1, high);
    }
}

void readFileContent(string dataFile, vector<Task>& tasks)
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

int scheduleTasks(vector<Task> tasks)
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

void optimizeC_max(vector<Task>& tasks)
{
    int c_max = scheduleTasks(tasks);

    for(int i = 0; i < tasks.size() - 1; i++)
    {
        for(int j = i + 1; j < tasks.size() - 1; j++)
        {
            swap(tasks[i], tasks[j]);

            int newC_max = scheduleTasks(tasks);

            if(newC_max < c_max)
            {
                c_max = newC_max;
            }
            else
            {
                swap(tasks[i], tasks[j]);
            }
        }
    }
}

int main()
{
    const int filesCount = 4;
    int sum = 0;
    for(int i=0; i<filesCount; i++)
    {
        string fileName =  "data" + to_string(i+1) + ".txt";
        vector<Task> tasks;

        readFileContent(fileName, tasks);
        quickSort(tasks, 0, tasks.size() - 1);
        optimizeC_max(tasks);

        sum += scheduleTasks(tasks);
    }

    cout << sum << endl;

    return 0;
}
//poczytac o tabuseachr lub symulowane wyzzarzanie