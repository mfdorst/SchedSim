//===- RoundRobin.h --- sched-sim: A CPU scheduling simulator -------------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `roundRobin()` funciton, which simulates round robin scheduling.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ProcessAssignment.h"

#include <vector>
#include <queue>

/// Simulates round robin scheduling
///
/// \param processes The processes to be scheduled
/// \param timeQuantum The length of the time quantum given to each process in a given round
/// \return The process scedule
std::vector<ProcessAssignment> roundRobin(std::vector<Process>& processes, unsigned const timeQuantum)
{
  std::vector<ProcessAssignment> schedule;
  unsigned time = 0;
  auto process_iter = processes.begin();
  std::vector<Process> waiting = { *process_iter++ };
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
    }
    // Queue all the processes that arrived during the time quantum
    while (process_iter != processes.end() and process_iter->arrivalTime() <= time)
    {
      waiting.push_back(*process_iter++);
    }
    // Queue the current working process if it is not done yet
    if (working.burstTime > 0) {
      waiting.push_back(working);
    }
  }
  return schedule;
}
