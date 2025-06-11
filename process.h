#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    std::string id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time;
    int finish_time;

    Process(std::string pid, int at, int bt, int prio = 0)
        : id(pid), arrival_time(at), burst_time(bt), priority(prio),
          remaining_time(bt), start_time(-1), finish_time(-1) {}
};

#endif