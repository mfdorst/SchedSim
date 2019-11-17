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
#include "PrioritySchedulingWithPreemption.h"
#include "ProcessData.h"

#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

void writeSchedule(std::string const& path, ScheduleType const& metaData, ScheduleData const& schedule,
                   float averageWaitingTime);

bool compareProcess(Process a, Process b) {
  return a.arrivalTime() < b.arrivalTime();
}

int main()
{
  ScheduleType scheduleType;
  ProcessData processData;
  std::tie(scheduleType, processData) = readProcessData("input.txt");
  // Sort the processes by start time
  std::sort(processData.begin(), processData.end(), compareProcess);
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
  else if (scheduleType.algorithm == "PR_withPREMP")
  {
    std::tie(schedule, averageWaitingTime) = prioritySchedulingWithPreemption(std::move(processData));
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
  for (size_t i = 0; i < schedule.size(); ++i) {
    out << schedule[i].timePoint << "    " << schedule[i].pid << "\n";
  }
  out << "AVG waiting time: " << std::fixed << std::setprecision(2) << averageWaitingTime << std::endl;
}
