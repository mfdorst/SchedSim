// TODO: Add header

#pragma once

#include "ProcessAssignment.h"
#include "MetaData.h"
#include "Util.h"

#include <vector>
#include <tuple>
#include <fstream>
#include <string>

typedef std::vector<ProcessAssignment> ScheduleData;

std::tuple<MetaData, ScheduleData> readScheduleData(std::string const& path) {
  std::ifstream outputFile(path);
  MetaData metaData;
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
