//===- PrioritySchedulingWithPreemption.h --- sched-sim: A CPU scheduling simulator ---------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `prioritySchedulingWithPreemption()` funciton, which simulates priority scheduling with
/// preemption.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ProcessData.h"
#include "ScheduleData.h"

#include <tuple>
#include <queue>

std::tuple<ScheduleData, float> prioritySchedulingWithPreemption(ProcessData&& processData)
{
  ScheduleData schedule;
  auto process_iter = processData.begin();
  std::priority_queue<Process, std::vector<Process>, HighestPriority> waiting;
  std::vector<unsigned> endingTimes;
  unsigned sumOfArrivalTimes = 0, totalBurstTime = 0;
  endingTimes.reserve(processData.size());
  unsigned time = process_iter->arrivalTime();
  unsigned previousProcess = 0;
  while (process_iter != processData.end() or !waiting.empty())
  {
    // Queue all processes with arrival times <= the current time.
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
    // Chose the process with the highest priority.
    auto working = waiting.top();
    if (working.pid() != previousProcess)
    {
      schedule.emplace_back(working.pid(), time);
    }
    previousProcess = working.pid();
    waiting.pop();
    // If the working process will finish before the next process arrives, let it finish.
    if (process_iter == processData.end() or time + working.burstTime <= process_iter->arrivalTime())
    {
      time += working.burstTime;
      // Process finished.
      endingTimes.push_back(time);
      continue;
    }
    // The next process will arrivce before the working process arrives. Run until that time.
    working.burstTime -= process_iter->arrivalTime() - time;
    time = process_iter->arrivalTime();
    // The working process is not finished. Queue it.
    waiting.push(working);
  }
  for (auto & process : processData)
  {
    sumOfArrivalTimes += process.arrivalTime();
    totalBurstTime += process.burstTime;
  }
  unsigned sumOfEndingTimes = 0;
  for (size_t i = 0; i < processData.size(); ++i)
  {
    sumOfEndingTimes += endingTimes[i];
  }
  auto const totalWaitingTime = sumOfEndingTimes - sumOfArrivalTimes - totalBurstTime;
  auto const averageWaitingTime = totalWaitingTime / (double) processData.size();
  return std::make_tuple(schedule, averageWaitingTime);
}
