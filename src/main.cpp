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
#include "RoundRobin.h"
#include "InputInfo.h"

#include <fstream>
#include <string>
#include <vector>

void writeSchedule(std::string const& path, InputInfo const& info, std::vector<ProcessAssignment> const& schedule);

int main()
{
  InputInfo input = readInputInfo("input.txt");
  
  std::vector<ProcessAssignment> schedule;
  if (input.algorithm == "RR")
  {
    schedule = roundRobin(input.processes, input.timeQuantum);
  }
  writeSchedule("output.txt", input, schedule);
  return 0;
}

void writeSchedule(std::string const& path, InputInfo const& info, std::vector<ProcessAssignment> const& schedule) {
  std::ofstream out(path);
  out << info.algorithm;
  if (info.timeQuantum > 0) {
    out << " " << info.timeQuantum;
  }
  out << "\n";
  for (auto const& assignment : schedule) {
    out << assignment.timePoint << "    " << assignment.pid << "\n";
  }
  out << std::flush;
}