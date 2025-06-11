#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>

class Process;

class Scheduler {
public:
    static void FCFS(std::vector<Process>& processes,
                     std::vector<std::pair<std::string, int>>& gantt,
                     std::vector<int>& waiting_times,
                     std::vector<int>& turnaround_times);
    
    static void SJF(std::vector<Process>& processes,
                    std::vector<std::pair<std::string, int>>& gantt,
                    std::vector<int>& waiting_times,
                    std::vector<int>& turnaround_times);
    
    static void RoundRobin(std::vector<Process>& processes, int quantum,
                           std::vector<std::pair<std::string, int>>& gantt,
                           std::vector<int>& waiting_times,
                           std::vector<int>& turnaround_times);
    
    static void Priority(std::vector<Process>& processes,
                         std::vector<std::pair<std::string, int>>& gantt,
                         std::vector<int>& waiting_times,
                         std::vector<int>& turnaround_times);
};

#endif