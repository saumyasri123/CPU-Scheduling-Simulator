#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "process.h"
#include "scheduler.h"
#include "file_io.h"

void printResults(const std::vector<std::pair<std::string, int>>& gantt,
                  const std::vector<Process>& processes,
                  const std::vector<int>& waiting_times,
                  const std::vector<int>& turnaround_times) {
    // Print Gantt Chart
    std::cout << "\nGantt Chart:\n";
    for (const auto& entry : gantt) {
        std::cout << "[" << entry.first << ":" << entry.second << "] ";
    }
    std::cout << "\n\n";
    
    // Print process details
    std::cout << "Process\tWaiting Time\tTurnaround Time\n";
    double total_waiting = 0, total_turnaround = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id << "\t" 
                  << waiting_times[i] << "\t\t"
                  << turnaround_times[i] << "\n";
        total_waiting += waiting_times[i];
        total_turnaround += turnaround_times[i];
    }
    
    // Calculate averages
    double avg_waiting = total_waiting / processes.size();
    double avg_turnaround = total_turnaround / processes.size();
    
    std::cout << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2) 
              << avg_waiting << "\n";
    std::cout << "Average Turnaround Time: " << avg_turnaround << "\n\n";
}

int main() {
    std::vector<Process> processes;
    int choice, n, quantum;
    bool file_input = false;
    std::string filename;
    
    std::cout << "CPU Scheduling Simulator\n";
    std::cout << "1. Enter process data manually\n";
    std::cout << "2. Read from file\n";
    std::cin >> choice;
    
    if (choice == 2) {
        std::cout << "Enter filename: ";
        std::cin >> filename;
        processes = readProcessesFromFile(filename);
        file_input = true;
    } else {
        std::cout << "Enter number of processes: ";
        std::cin >> n;
        
        for (int i = 0; i < n; i++) {
            std::string id;
            int at, bt, prio = 0;
            
            std::cout << "Process " << i+1 << ":\n";
            std::cout << "ID: ";
            std::cin >> id;
            std::cout << "Arrival Time: ";
            std::cin >> at;
            std::cout << "Burst Time: ";
            std::cin >> bt;
            std::cout << "Priority (0 if none): ";
            std::cin >> prio;
            
            processes.emplace_back(id, at, bt, prio);
        }
    }
    
    while (true) {
        std::vector<std::pair<std::string, int>> gantt;
        std::vector<int> waiting_times(processes.size());
        std::vector<int> turnaround_times(processes.size());
        
        std::cout << "\nScheduling Algorithms:\n";
        std::cout << "1. FCFS\n2. SJF\n3. Round Robin\n4. Priority\n5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        if (choice == 5) break;
        
        switch(choice) {
            case 1:
                Scheduler::FCFS(processes, gantt, waiting_times, turnaround_times);
                break;
            case 2:
                Scheduler::SJF(processes, gantt, waiting_times, turnaround_times);
                break;
            case 3:
                std::cout << "Enter time quantum: ";
                std::cin >> quantum;
                Scheduler::RoundRobin(processes, quantum, gantt, waiting_times, turnaround_times);
                break;
            case 4:
                Scheduler::Priority(processes, gantt, waiting_times, turnaround_times);
                break;
            default:
                std::cout << "Invalid choice!\n";
                continue;
        }
        
        printResults(gantt, processes, waiting_times, turnaround_times);
        
        std::cout << "Export results to file? (y/n): ";
        char export_choice;
        std::cin >> export_choice;
        if (export_choice == 'y' || export_choice == 'Y') {
            std::cout << "Enter filename: ";
            std::cin >> filename;
            
            double total_waiting = 0, total_turnaround = 0;
            for (size_t i = 0; i < processes.size(); ++i) {
                total_waiting += waiting_times[i];
                total_turnaround += turnaround_times[i];
            }
            double avg_waiting = total_waiting / processes.size();
            double avg_turnaround = total_turnaround / processes.size();
            
            writeResultsToFile(filename, gantt, processes, 
                              waiting_times, turnaround_times,
                              avg_waiting, avg_turnaround);
            std::cout << "Results exported to " << filename << "\n";
        }
    }
    
    return 0;
}