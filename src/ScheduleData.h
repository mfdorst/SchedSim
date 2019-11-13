//===- ScheduleData.h --- sched-sim: A CPU scheduling simulator -----------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains `ProcessAssignment` and `ScheduleData` types, as well as the `readScheduleData()` function.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include "ScheduleType.h"
#include "Util.h"

#include <vector>
#include <tuple>
#include <fstream>
#include <string>

/// Tracks a time at which a process will assigned to the CPU.
struct ProcessAssignment {
  /// The process ID
  unsigned pid;
  /// The time at which the process will be assigned to the CPU
  unsigned timePoint;
  
  ProcessAssignment(unsigned pid, unsigned timePoint) : pid(pid), timePoint(timePoint) {}
};

/// A collection of process assignments which represent a simulated CPU schedule
typedef std::vector<ProcessAssignment> ScheduleData;

/// A test helper - reads the output of `sched-sim` so that the program results can be verified.
std::tuple<ScheduleType, ScheduleData> readScheduleData(std::string const& path) {
  std::ifstream outputFile(path);
  ScheduleType metaData;
  ScheduleData scheduleData;
  metaData.algorithm = read<std::string>(outputFile);
  if (metaData.algorithm == "RR") {
    metaData.timeQuantum = read<unsigned>(outputFile);
  }
  while (true) {
    auto const scheduleTime = read<unsigned>(outputFile);
    // When EOF is read, break
    if (!outputFile) break;
    auto const pid = read<unsigned>(outputFile);
    scheduleData.emplace_back(pid, scheduleTime);
  }
  return std::make_tuple(metaData, scheduleData);
}
