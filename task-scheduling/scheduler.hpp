#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "task.hpp"
#include <vector>
#include <string>

class Scheduler
{
private:
    std::vector<Task> tasks;

public:
    void readFileContent(std::string dataFile);
    void quickSort(int low, int high);
    int calculateC_max();
    const std::vector<Task>& getTasks() const;
    int sortRQ();
    
private:
    int partition(int low, int high);
};

#endif