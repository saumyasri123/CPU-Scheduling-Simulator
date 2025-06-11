#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "process.h"

std::vector<Process> readProcessesFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id;
        int at, bt, prio = 0;
        
        if (iss >> id >> at >> bt) {
            // Try reading priority if exists
            if (!(iss >> prio)) prio = 0;
            processes.emplace_back(id, at, bt, prio);
        }
    }
    return processes;
}

void writeResultsToFile(const std::string& filename,
                        const std::vector<std::pair<std::string, int>>& gantt,
                        const std::vector<Process>& processes,
                        const std::vector<int>& waiting_times,
                        const std::vector<int>& turnaround_times,
                        double avg_waiting, double avg_turnaround) {
    std::ofstream file(filename);
    
    file << "Gantt Chart:\n";
    for (const auto& entry : gantt) {
        file << "[" << entry.first << ":" << entry.second << "] ";
    }
    file << "\n\n";
    
    file << "Process\tWaiting Time\tTurnaround Time\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        file << processes[i].id << "\t"
             << waiting_times[i] << "\t\t"
             << turnaround_times[i] << "\n";
    }
    
    file << "\nAverage Waiting Time: " << avg_waiting << "\n";
    file << "Average Turnaround Time: " << avg_turnaround << "\n";
}

#endif