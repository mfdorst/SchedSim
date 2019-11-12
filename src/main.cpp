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

#include "RoundRobin.h"
#include "ProcessData.h"

#include <fstream>
#include <string>
#include <vector>

void writeSchedule(std::string const& path, MetaData const& metaData, std::vector<ProcessAssignment> const& schedule);

int main()
{
  MetaData metaData;
  ProcessData processData;
  std::tie(metaData, processData) = readProcessData("input.txt");
  
  std::vector<ProcessAssignment> schedule;
  if (metaData.algorithm == "RR")
  {
    schedule = roundRobin(processData.processes, metaData.timeQuantum);
  }
  writeSchedule("output.txt", metaData, schedule);
  return 0;
}

void writeSchedule(std::string const& path, MetaData const& metaData, ScheduleData const& schedule) {
  std::ofstream out(path);
  out << metaData.algorithm;
  if (metaData.timeQuantum > 0) {
    out << " " << metaData.timeQuantum;
  }
  out << "\n";
  for (auto const& assignment : schedule) {
    out << assignment.timePoint << "    " << assignment.pid << "\n";
  }
  out << std::flush;
}
