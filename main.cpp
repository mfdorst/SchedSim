//===- main.cpp --- sched-sim: A CPU scheduling simulator ---------------------------------------------------------===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains `main()`, which is the entry point for sched-sim.
///
//===--------------------------------------------------------------------------------------------------------------===//

#include "Process.h"

#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  std::string algorithm;
  unsigned timeQuantumLength = 0;
  unsigned numProcesses = 0;
  // Get the algorithm type, time quantum (if present), and number of processes.
  in >> algorithm;
  if (algorithm == "RR")
  {
    in >> timeQuantumLength;
  }
  in >> numProcesses;
  // Get the numbers for each process
  std::vector<Process> processes;
  processes.reserve(numProcesses);
  for (unsigned i = 0; i < numProcesses; ++i)
  {
    unsigned pid, arrivalTime, burstTime, priority;
    in >> pid >> arrivalTime >> burstTime >> priority;
    processes.emplace_back(pid, arrivalTime, burstTime, priority);
  }
  // Print the algorithm type and time quantum (if present).
  out << algorithm;
  if (timeQuantumLength > 0)
  {
    out << " " << timeQuantumLength;
  }
  // DEBUG: Print the process info
  for (auto process : processes)
  {
    out << "\n" << process.pid() << " " << process.arrivalTime() << " " << process.burstTime() << " "
        << process.priority();
  }
  out << std::endl;
  return 0;
}
