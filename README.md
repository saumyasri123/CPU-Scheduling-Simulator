# CPU Scheduling Simulator

This project simulates various CPU scheduling algorithms in C++, allowing users to visualize and compare their performance.

## Features

- Simulates popular CPU scheduling algorithms:
  - First-Come, First-Served (FCFS)
  - Shortest Job First (SJF)
  - Priority Scheduling
  - Round Robin (RR, configurable quantum)
- Visualizes process execution order with a Gantt chart
- Calculates and displays detailed waiting and turnaround times
- Computes average metrics
- Supports manual input and file input (space-separated: PID, Arrival, Burst, Priority)
- Exports results to CSV
- Handles idle CPU periods and validates input

## File Structure

- `process.h` — Process class definition
- `scheduler.h` — Scheduler class declaration
- `scheduler.cpp` — Scheduler class implementation
- `file_io.h` — File I/O functions
- `main.cpp` — Main application logic

## Getting Started

1. **Clone the repository:**
   ```bash
   git clone https://github.com/saumyasri123/CPU-Scheduling-Simulator.git
   cd CPU-Scheduling-Simulator
   ```

2. **Compile the project:**
   ```bash
   g++ -std=c++11 main.cpp scheduler.cpp -o scheduler
   ```

3. **Run the simulator:**
   ```bash
   ./scheduler
   ```

## Usage

- Input your processes and their burst times, priorities, and arrival times as required (via console or file).
- Select the scheduling algorithm to simulate.
- View the Gantt chart, results, and analysis.
- Export results to CSV if needed.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

