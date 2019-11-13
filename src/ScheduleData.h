//===- ScheduleData.h --- sched-sim: A CPU scheduling simulator -----------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains `ProcessAssignment` and `ScheduleData` types.
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
