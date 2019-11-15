//===- ProcessData.h --- sched-sim: A CPU scheduling simulator ------------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `Process` and `ProcessData` types, as well as the `readProcessData()` function.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ScheduleType.h"
#include "Util.h"

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

/// Represents a process specified in the input file.
class Process {
  unsigned m_pid, m_arrivalTime, m_priority;
public:
  Process(unsigned pid, unsigned arrivalTime, unsigned burstTime, unsigned priority = 0)
      : m_pid(pid), m_arrivalTime(arrivalTime), burstTime(burstTime), m_priority(priority) {}
      
  /// Specifies how long the process needs to be on the CPU before it will exit.
  unsigned burstTime;
  /// Specifies the Process ID
  unsigned pid() const { return m_pid; }
  /// Specifies at what time-point the process will be ready to be scheduled
  unsigned arrivalTime() const { return m_arrivalTime; }
  /// Specifies how important it is for this process to complete quickly (lower number = higher priority)
  unsigned priority() const { return m_priority; }
};

/// A collection of processes - used to represent all processes specified in the input file
typedef std::vector<Process> ProcessData;

/// Read algorithm and processes from the input file.
///
/// \param[in] path The path to the input file
/// \return The algorithm to be used to schedule, and the processes to be scheduled, as read from the input file
std::tuple<ScheduleType, ProcessData> readProcessData(std::string const& path) {
  std::ifstream inputFile(path);
  ScheduleType metaData;
  ProcessData processData;
  metaData.algorithm = read<std::string>(inputFile);
  if (metaData.algorithm == "RR") {
    metaData.timeQuantum = read<unsigned>(inputFile);
  }
  auto processCount = read<unsigned>(inputFile);
  processData.reserve(processCount);
  for (unsigned i = 0; i < processCount; ++i) {
    const auto pid = read<unsigned>(inputFile);
    const auto arrivalTime = read<unsigned>(inputFile);
    const auto burstTime = read<unsigned>(inputFile);
    const auto priority = read<unsigned>(inputFile);
    processData.emplace_back(pid, arrivalTime, burstTime, priority);
  }
  return std::make_tuple(metaData, processData);
}
