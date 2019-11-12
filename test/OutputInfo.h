// TODO: Add header

#pragma once

#include "../src/ProcessAssignment.h"

#include <string>
#include <vector>
#include <fstream>

struct OutputInfo {
  std::string algorithm;
  unsigned timeQuantum;
  std::vector<ProcessAssignment> processAssignments;
  
  OutputInfo() {
    timeQuantum = 0;
  }
};

template <class T>
T read(std::istream& in)
{
  T t;
  in >> t;
  return t;
}

OutputInfo readOutputInfo(std::string const& path) {
  std::ifstream outputFile(path);
  OutputInfo info;
  info.algorithm = read<std::string>(outputFile);
  if (info.algorithm == "RR") {
    info.timeQuantum = read<unsigned>(outputFile);
  }
  while (true) {
    auto const scheduleTime = read<unsigned>(outputFile);
    // When EOF is read, break
    if (!outputFile) break;
    auto const pid = read<unsigned>(outputFile);
    info.processAssignments.emplace_back(pid, scheduleTime);
  }
  return info;
}
