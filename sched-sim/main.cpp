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
#include "PrioritySchedulingWithoutPreemption.h"
#include "ProcessData.h"

#include <fstream>
#include <string>

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule,
                   float averageWaitingTime);

int main()
{
  ScheduleType scheduleType;
  ProcessData processData;
  std::tie(scheduleType, processData) = readProcessData("input.txt");
  // Sor the processes by start time
  std::sort(processData.begin(), processData.end(), [](Process a, Process b) {
    return a.arrivalTime() < b.arrivalTime();
  });
  ScheduleData schedule;
  float averageWaitingTime = 0;
  if (scheduleType.algorithm == "RR")
  {
    std::tie(schedule, averageWaitingTime) = roundRobin(std::move(processData), scheduleType.timeQuantum);
  }
  else if (scheduleType.algorithm == "SJF")
  {
    std::tie(schedule, averageWaitingTime) = shortestJobFirst(std::move(processData));
  }
  else if (scheduleType.algorithm == "PR_noPREMP")
  {
    std::tie(schedule, averageWaitingTime) = prioritySchedulingWithoutPreemption(std::move(processData));
  }
  writeSchedule("output.txt", scheduleType, schedule, averageWaitingTime);
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
