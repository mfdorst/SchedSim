// TODO: Write header

#pragma once

#include "Process.h"

#include <string>
#include <vector>
#include <fstream>

struct InputInfo {
  std::string algorithm;
  unsigned timeQuantum;
  unsigned processCount;
  std::vector<Process> processes;
  
  InputInfo() {
    timeQuantum = 0;
    processCount = 0;
  }
};

template <class T>
T read(std::istream& in)
{
  T t;
  in >> t;
  return t;
}

InputInfo readInputInfo(std::string const& path) {
  std::ifstream inputFile(path);
  InputInfo info;
  info.algorithm = read<std::string>(inputFile);
  if (info.algorithm == "RR") {
    info.timeQuantum = read<unsigned>(inputFile);
  }
  info.processCount = read<unsigned>(inputFile);
  info.processes.reserve(info.processCount);
  for (unsigned i = 0; i < info.processCount; ++i) {
    const auto pid = read<unsigned>(inputFile);
    const auto arrivalTime = read<unsigned>(inputFile);
    const auto burstTime = read<unsigned>(inputFile);
    const auto priority = read<unsigned>(inputFile);
    info.processes.emplace_back(pid, arrivalTime, burstTime, priority);
  }
  return info;
}
