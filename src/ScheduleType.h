//===- ScheduleType.h --- sched-sim: A CPU scheduling simulator -----------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `ScheduleType` struct
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

#include <string>

/// Specifies the type of schedule to be simulated
struct ScheduleType {
  /// The algorithm to be used
  std::string algorithm;
  /// The specified time quantum - (only applicable to the Round Robin scheduling algorithm)
  unsigned timeQuantum;
  
  ScheduleType() : timeQuantum(0) {}
};
