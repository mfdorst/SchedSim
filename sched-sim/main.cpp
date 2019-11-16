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
#include "ShortestJobFirst.h"
#include "ProcessData.h"

#include <fstream>
#include <string>

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule,
                   float averageWaitingTime);

int main()
{
  ScheduleType metaData;
  ProcessData processData;
  std::tie(metaData, processData) = readProcessData("input.txt");
  
  ScheduleData schedule;
  float averageWaitingTime = 0;
  if (metaData.algorithm == "RR")
  {
    std::tie(schedule, averageWaitingTime) = roundRobin(std::move(processData), metaData.timeQuantum);
  }
  else if (metaData.algorithm == "SJF")
  {
    std::tie(schedule, averageWaitingTime) = shortestJobFirst(std::move(processData));
  }
  writeSchedule("output.txt", metaData, schedule, averageWaitingTime);
  return 0;
}

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule,
                   float const averageWaitingTime)
{
  std::ofstream out(path);
  out << metaData.algorithm;
  if (metaData.timeQuantum > 0)
  {
    out << " " << metaData.timeQuantum;
  }
  out << "\n";
  for (auto const& assignment : schedule)
  {
    out << assignment.timePoint << "    " << assignment.pid << "\n";
  }
  out << "AVG waiting time: " << averageWaitingTime << std::endl;
}
