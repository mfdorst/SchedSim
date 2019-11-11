//===- ProcessAssignment.h --- sched-sim: A CPU scheduling simulator ------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `ProcessAssignment` struct.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

/// Tracks a time at which a process will assigned to the CPU.
struct ProcessAssignment {
  /// The process ID
  unsigned pid;
  /// The time at which the process will be assigned to the CPU
  unsigned timePoint;
  
  ProcessAssignment(unsigned pid, unsigned timePoint) : pid(pid), timePoint(timePoint) {}
};
