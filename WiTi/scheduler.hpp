#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include "task.hpp"
#include <string>

class Scheduler
{
private:
    std::vector<Task> tasks;

public:
    void readFileContent(std::string filePath);
    int delayCost();
    void displayOrder();
    const std::vector<Task>& getTasks() const;
    void witiDP();
};

#endif