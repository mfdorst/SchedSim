//===- ShortestJobFirst.h --- sched-sim: A CPU scheduling simulator -------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `shortestJobFirst()` funciton, which simulates shortest-job-first scheduling.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ScheduleData.h"
#include "ProcessData.h"

#include <tuple>
#include <queue>

struct ShortestProcess
{
  bool operator()(Process const& a, Process const& b) const
  {
    return a.burstTime > b.burstTime;
  }
};

/// Simulates shortest-job-first scheduling
///
/// \param processes The processes to be scheduled
/// \return The process schedule and the average waiting time
std::tuple<ScheduleData, float> shortestJobFirst(ProcessData&& processData)
{
  ScheduleData schedule;
  unsigned time = 0;
  auto process_iter = processData.begin();
  std::priority_queue<Process, std::vector<Process>, ShortestProcess> waiting;
  std::vector<unsigned> endingTimes;
  endingTimes.reserve(processData.size());
  while (process_iter != processData.end() or !waiting.empty())
  {
    // Queue all processes that arrived while the working process ran
    while (process_iter != processData.end() and process_iter->arrivalTime() <= time)
    {
      waiting.push(*process_iter++);
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
  return std::make_tuple(schedule, averageWaitingTime);
}
