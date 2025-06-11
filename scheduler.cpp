#include "scheduler.h"
#include "process.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

// Helper function to reset process states
void resetProcesses(std::vector<Process>& processes) {
    for (auto& p : processes) {
        p.remaining_time = p.burst_time;
        p.start_time = -1;
        p.finish_time = -1;
    }
}

void Scheduler::FCFS(std::vector<Process>& processes,
                     std::vector<std::pair<std::string, int>>& gantt,
                     std::vector<int>& waiting_times,
                     std::vector<int>& turnaround_times) {
    resetProcesses(processes);
    gantt.clear();
    waiting_times.assign(processes.size(), 0);
    turnaround_times.assign(processes.size(), 0);

    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    for (auto& p : processes) {
        if (current_time < p.arrival_time) {
            gantt.push_back({"Idle", p.arrival_time - current_time});
            current_time = p.arrival_time;
        }
        
        p.start_time = current_time;
        gantt.push_back({p.id, p.burst_time});
        current_time += p.burst_time;
        p.finish_time = current_time;
    }

    for (int i = 0; i < processes.size(); i++) {
        turnaround_times[i] = processes[i].finish_time - processes[i].arrival_time;
        waiting_times[i] = turnaround_times[i] - processes[i].burst_time;
    }
}

void Scheduler::SJF(std::vector<Process>& processes,
                    std::vector<std::pair<std::string, int>>& gantt,
                    std::vector<int>& waiting_times,
                    std::vector<int>& turnaround_times) {
    resetProcesses(processes);
    gantt.clear();
    waiting_times.assign(processes.size(), 0);
    turnaround_times.assign(processes.size(), 0);

    auto comp = [](const Process* a, const Process* b) {
        return a->burst_time > b->burst_time;
    };
    std::priority_queue<Process*, std::vector<Process*>, decltype(comp)> pq(comp);
    
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    int index = 0;
    int completed = 0;
    const int n = processes.size();
    Process* current = nullptr;

    while (completed < n) {
        while (index < n && processes[index].arrival_time <= current_time) {
            pq.push(&processes[index]);
            index++;
        }

        if (pq.empty()) {
            int next_arrival = processes[index].arrival_time;
            gantt.push_back({"Idle", next_arrival - current_time});
            current_time = next_arrival;
            continue;
        }

        current = pq.top();
        pq.pop();
        
        if (current->start_time == -1) {
            current->start_time = current_time;
        }
        
        gantt.push_back({current->id, current->burst_time});
        current_time += current->burst_time;
        current->finish_time = current_time;
        current->remaining_time = 0;
        completed++;
    }

    for (int i = 0; i < n; i++) {
        turnaround_times[i] = processes[i].finish_time - processes[i].arrival_time;
        waiting_times[i] = turnaround_times[i] - processes[i].burst_time;
    }
}

void Scheduler::RoundRobin(std::vector<Process>& processes, int quantum,
                          std::vector<std::pair<std::string, int>>& gantt,
                          std::vector<int>& waiting_times,
                          std::vector<int>& turnaround_times) {
    resetProcesses(processes);
    gantt.clear();
    waiting_times.assign(processes.size(), 0);
    turnaround_times.assign(processes.size(), 0);

    std::queue<Process*> q;
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    int index = 0;
    int completed = 0;
    const int n = processes.size();
    Process* current = nullptr;

    while (completed < n) {
        while (index < n && processes[index].arrival_time <= current_time) {
            q.push(&processes[index]);
            index++;
        }

        if (q.empty()) {
            if (index < n) {
                gantt.push_back({"Idle", processes[index].arrival_time - current_time});
                current_time = processes[index].arrival_time;
            }
            continue;
        }

        current = q.front();
        q.pop();

        if (current->start_time == -1) {
            current->start_time = current_time;
        }

        int time_slice = std::min(quantum, current->remaining_time);
        gantt.push_back({current->id, time_slice});
        current_time += time_slice;
        current->remaining_time -= time_slice;

        while (index < n && processes[index].arrival_time <= current_time) {
            q.push(&processes[index]);
            index++;
        }

        if (current->remaining_time > 0) {
            q.push(current);
        } else {
            current->finish_time = current_time;
            completed++;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaround_times[i] = processes[i].finish_time - processes[i].arrival_time;
        waiting_times[i] = turnaround_times[i] - processes[i].burst_time;
    }
}

void Scheduler::Priority(std::vector<Process>& processes,
                         std::vector<std::pair<std::string, int>>& gantt,
                         std::vector<int>& waiting_times,
                         std::vector<int>& turnaround_times) {
    resetProcesses(processes);
    gantt.clear();
    waiting_times.assign(processes.size(), 0);
    turnaround_times.assign(processes.size(), 0);

    auto comp = [](const Process* a, const Process* b) {
        return a->priority > b->priority;
    };
    std::priority_queue<Process*, std::vector<Process*>, decltype(comp)> pq(comp);
    
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    int index = 0;
    int completed = 0;
    const int n = processes.size();
    Process* current = nullptr;

    while (completed < n) {
        while (index < n && processes[index].arrival_time <= current_time) {
            pq.push(&processes[index]);
            index++;
        }

        if (pq.empty()) {
            if (index < n) {
                gantt.push_back({"Idle", processes[index].arrival_time - current_time});
                current_time = processes[index].arrival_time;
            }
            continue;
        }

        current = pq.top();
        pq.pop();
        
        if (current->start_time == -1) {
            current->start_time = current_time;
        }
        
        gantt.push_back({current->id, current->burst_time});
        current_time += current->burst_time;
        current->finish_time = current_time;
        current->remaining_time = 0;
        completed++;
    }

    for (int i = 0; i < n; i++) {
        turnaround_times[i] = processes[i].finish_time - processes[i].arrival_time;
        waiting_times[i] = turnaround_times[i] - processes[i].burst_time;
    }
}