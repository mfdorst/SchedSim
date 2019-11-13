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

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule);

int main()
{
  ScheduleType metaData;
  ProcessData processData;
  std::tie(metaData, processData) = readProcessData("input.txt");
  
  ScheduleData schedule;
  if (metaData.algorithm == "RR")
  {
    schedule = roundRobin(processData, metaData.timeQuantum);
  }
  writeSchedule("output.txt", metaData, schedule);
  return 0;
}

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule) {
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
