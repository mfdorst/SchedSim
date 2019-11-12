//===- Process.h --- sched-sim: A CPU scheduling simulator ----------------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the `Process` class, which stores data about a particular process in the simulation.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

class Process {
  unsigned m_pid, m_arrivalTime, m_priority;
public:
  Process(unsigned pid, unsigned arrivalTime, unsigned burstTime, unsigned priority = 0)
      : m_pid(pid), m_arrivalTime(arrivalTime), burstTime(burstTime), m_priority(priority) {}
  unsigned burstTime;
  unsigned pid() const { return m_pid; }
  unsigned arrivalTime() const { return m_arrivalTime; }
  unsigned priority() const { return m_priority; }
};
