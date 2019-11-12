// TODO: Write header

#pragma once

#include "MetaData.h"
#include "Util.h"

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

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

struct ProcessData {
  unsigned processCount;
  std::vector<Process> processes;
  
  ProcessData() : processCount(0) {}
};

std::tuple<MetaData, ProcessData> readProcessData(std::string const& path) {
  std::ifstream inputFile(path);
  MetaData metaData;
  ProcessData processData;
  metaData.algorithm = read<std::string>(inputFile);
  if (metaData.algorithm == "RR") {
    metaData.timeQuantum = read<unsigned>(inputFile);
  }
  processData.processCount = read<unsigned>(inputFile);
  processData.processes.reserve(processData.processCount);
  for (unsigned i = 0; i < processData.processCount; ++i) {
    const auto pid = read<unsigned>(inputFile);
    const auto arrivalTime = read<unsigned>(inputFile);
    const auto burstTime = read<unsigned>(inputFile);
    const auto priority = read<unsigned>(inputFile);
    processData.processes.emplace_back(pid, arrivalTime, burstTime, priority);
  }
  return std::make_tuple(metaData, processData);
}
