//===- RoundRobin.h --- sched-sim: A CPU scheduling simulator -------------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `roundRobin()` funciton, which simulates round-robin scheduling.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ProcessData.h"
#include "ScheduleData.h"

#include <vector>
#include <queue>

/// Simulates round-robin scheduling
///
/// \param processData The processes to be scheduled
/// \param timeQuantum The length of the time quantum given to each process in a given round
/// \return The process scedule
std::tuple<ScheduleData, float> roundRobin(ProcessData&& processData, unsigned const timeQuantum)
{
  ScheduleData schedule;
  unsigned time = 0;
  auto process_iter = processData.begin();
  std::vector<Process> waiting = { *process_iter++ };
  waiting.reserve(processData.size());
  std::vector<unsigned> endingTimes;
  endingTimes.reserve(processData.size());
  while (!waiting.empty())
  {
    // Select the next working process from the front of the queue
    auto working = waiting.front();
    waiting.erase(waiting.begin());
    // Simulate a CPU time quantum (working process has the CPU for timeQuantum cycles)
    schedule.emplace_back(working.pid(), time);
    if (working.burstTime > timeQuantum)
    {
      time += timeQuantum;
      working.burstTime -= timeQuantum;
    }
    else
    {
      time += working.burstTime;
      working.burstTime = 0;
      // Process is done.
      endingTimes.push_back(time);
    }
    // Queue all the processes that arrived during the time quantum
    while (process_iter != processData.end() and process_iter->arrivalTime() <= time)
    {
      waiting.push_back(*process_iter++);
    }
    // Queue the current working process if it is not done yet
    if (working.burstTime > 0) {
      waiting.push_back(working);
    }
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
