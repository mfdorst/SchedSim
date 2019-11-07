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
  unsigned m_pid, m_arrivalTime, m_burstTime, m_priority;
public:
  Process(unsigned pid, unsigned arrivalTime, unsigned burstTime, unsigned priority = 0)
      : m_pid(pid), m_arrivalTime(arrivalTime), m_burstTime(burstTime), m_priority(priority) {}
  
  unsigned pid() { return m_pid; }
  unsigned arrivalTime() { return m_arrivalTime; }
  unsigned burstTime() { return m_burstTime; }
  unsigned priority() { return m_priority; }
};
