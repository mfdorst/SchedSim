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

template <class T>
T read(std::istream &in);
std::vector<Process> readProcessData(std::istream &in, unsigned processCount);

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  
  auto algorithm = read<std::string>(in);
  auto timeQuantum = algorithm == "RR" ? read<unsigned>(in) : 0;
  auto processCount = read<unsigned>(in);
  auto processes = readProcessData(in, processCount);
  // Print the algorithm type and time quantum (if present).
  out << algorithm;
  if (timeQuantum > 0)
  {
    out << " " << timeQuantum;
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

std::vector<Process> readProcessData(std::istream &in, const unsigned processCount)
{
  std::vector<Process> processes;
  processes.reserve(processCount);
  for (unsigned i = 0; i < processCount; ++i)
  {
    const auto pid = read<unsigned>(in);
    const auto arrivalTime = read<unsigned>(in);
    const auto burstTime = read<unsigned>(in);
    const auto priority = read<unsigned>(in);
    processes.emplace_back(pid, arrivalTime, burstTime, priority);
  }
  return processes;
}

template <class T>
T read(std::istream &in)
{
  T t;
  in >> t;
  return t;
}
