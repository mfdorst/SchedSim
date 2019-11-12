// TODO: Write header

#pragma once

#include "Process.h"
#include "MetaData.h"
#include "Util.h"

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

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
