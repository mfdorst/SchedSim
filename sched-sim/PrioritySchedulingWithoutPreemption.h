//===- PrioritySchedulingWithoutPreemption.h --- sched-sim: A CPU scheduling simulator ------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `prioritySchedulingWithoutPreemption()` funciton, which simulates priority scheduling without
/// preemption.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ProcessData.h"
#include "ScheduleData.h"

#include <tuple>
#include <queue>

std::tuple<ScheduleData, float> prioritySchedulingWithoutPreemption(ProcessData&& processData)
{
  ScheduleData schedule;
  unsigned time = 0;
  auto process_iter = processData.begin();
  std::priority_queue<Process, std::vector<Process>, HighestPriority> waiting;
  std::vector<unsigned> endingTimes;
  endingTimes.reserve(processData.size());
  while (process_iter != processData.end() or !waiting.empty())
  {
    // Queue all processes that arrived while the working process ran
    while (process_iter != processData.end() and process_iter->arrivalTime() <= time)
    {
      waiting.push(*process_iter++);
    }
    // If the waiting queue is empty (but there are still more processes coming), go to the next time step.
    if (waiting.empty())
    {
      time += 1;
      continue;
    }
    // Select the next working process from sorted queue (the process with the smallest burst time)
    auto working = waiting.top();
    schedule.emplace_back(working.pid(), time);
    waiting.pop();
    // Run the working process to completion
    time += working.burstTime;
    endingTimes.push_back(time);
  }
  unsigned sumOfEndingTimes = 0, sumOfArrivalTimes = 0, totalBurstTime = 0;
  for (size_t i = 0; i < processData.size(); ++i)
  {
    sumOfEndingTimes += endingTimes[i];
    sumOfArrivalTimes += processData[i].arrivalTime();
    totalBurstTime += processData[i].burstTime;
  }
  auto const totalWaitingTime = sumOfEndingTimes - sumOfArrivalTimes - totalBurstTime;
  auto const averageWaitingTime = totalWaitingTime / (double) processData.size();
  return std::tuple<ScheduleData, float>(schedule, averageWaitingTime);
}
