//===- test-sched-sim.cpp --- test-sched-sim-sched-sim: Test suite for sched-sim ------------------------------------------------------===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file is the entry point for `test-sched-sim` - the `sched-sim` test suite.
///
//===--------------------------------------------------------------------------------------------------------------===//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <tuple>
#include <regex>

#include "../sched-sim/ScheduleType.h"
#include "../sched-sim/ScheduleData.h"

template <class T>
std::string fail(std::string const& message, T const& expected, T const& actual);
std::tuple<ScheduleType, ScheduleData, float> readScheduleData(std::string const& path);

/// Copies the input from each test case one at a time, runs `sched-sim` on each, tests the output to verify
/// correctnes, and tells the user which tests fail.
int main()
{
  unsigned const testCount = 16;
  unsigned failed = 0;
  std::vector<std::vector<std::string>> allFailures;
  allFailures.reserve(testCount);
  std::vector<std::string> allAlgorithms;
  allAlgorithms.reserve(testCount);
  for (unsigned testNum = 1; testNum <= testCount; ++testNum)
  {
    // Set up the test-sched-sim input
    system(("cp test_cases/input" + std::to_string(testNum) + ".txt input.txt").c_str());
    // Run sched-sim on the test-sched-sim input
    system("../sched-sim/sched-sim");
    // Read the output and compare it with the expected output
    ScheduleType actualScheduleType, expectedScheduleType;
    ScheduleData actualSchedule, expectedSchedule;
    float actualAverageWaitingTime, expectedAverageWaitingTime;
    std::tie(actualScheduleType, actualSchedule, actualAverageWaitingTime) = readScheduleData("output.txt");
    std::tie(expectedScheduleType, expectedSchedule, expectedAverageWaitingTime) =
        readScheduleData("test_cases/output" + std::to_string(testNum) + ".txt");
    // Fail if there are differences between actual and expected
    allAlgorithms.push_back(expectedScheduleType.algorithm);
    std::vector<std::string> failures;
    if (actualScheduleType.algorithm != expectedScheduleType.algorithm)
    {
      failures.push_back(fail("Wrong algorithm.", expectedScheduleType.algorithm, actualScheduleType.algorithm));
    }
    if (expectedScheduleType.algorithm == "RR" and actualScheduleType.timeQuantum != expectedScheduleType.timeQuantum)
    {
      failures.push_back(
          fail("Wrong time quantum.", expectedScheduleType.timeQuantum, expectedScheduleType.timeQuantum));
    }
    if (expectedSchedule.size() != actualSchedule.size())
    {
      failures.push_back(fail("Wrong number of CPU assignments.", expectedSchedule.size(), actualSchedule.size()));
    }
    else
    {
      for (size_t i = 0; i < expectedSchedule.size(); ++i)
      {
        if (expectedSchedule[i].timePoint != actualSchedule[i].timePoint)
        {
          failures.push_back(fail("Wrong time-point.", expectedSchedule[i].timePoint, actualSchedule[i].timePoint));
        }
      }
    }
    if (actualAverageWaitingTime != expectedAverageWaitingTime)
    {
      failures.push_back(fail("Wrong average waiting time.", expectedAverageWaitingTime, actualAverageWaitingTime));
    }
    if (!failures.empty())
    {
      failed++;
      std::cout << "\033[31mF";
    }
    else
    {
      std::cout << "\033[32m.";
    }
    allFailures.push_back(failures);
  }
  std::cout << "\n\033[32mPassed: " << testCount - failed << "  \033[31mFailed: " << failed << std::endl;
  
  for (size_t i = 0; i < allFailures.size(); ++i)
  {
    if (!allFailures[i].empty())
    {
      std::cout << "Test " << i + 1 << " failed.\n"
      << "Algorithm: " << allAlgorithms[i] << "\n\n";
    }
    for (auto const& failureMessage : allFailures[i])
    {
      std::cout << failureMessage << "\n";
    }
  }
  std::cout << "\033[0m" << std::flush;
  
  system("rm input.txt output.txt");
}

/// Constructs a message which details the cause of a test failure
template <class T>
std::string fail(std::string const& message, T const& expected, T const& actual)
{
  std::stringstream ss;
  ss << message << "\n" << "Expected: " << expected << "\nActual: " << actual << "\n";
  return ss.str();
}

std::tuple<unsigned, bool> readIfUInt(std::istream& in);

/// Reads the output of `sched-sim` so that the program results can be verified.
std::tuple<ScheduleType, ScheduleData, float> readScheduleData(std::string const& path)
{
  std::ifstream outputFile(path);
  ScheduleType metaData;
  ScheduleData scheduleData;
  metaData.algorithm = read<std::string>(outputFile);
  if (metaData.algorithm == "RR")
  {
    metaData.timeQuantum = read<unsigned>(outputFile);
  }
  while (true)
  {
    unsigned scheduleTime;
    bool isNum;
    // If the next thing in the file is a number, keep reading schedule data.
    std::tie(scheduleTime, isNum) = readIfUInt(outputFile);
    if (!isNum) break;
    auto const pid = read<unsigned>(outputFile);
    scheduleData.emplace_back(pid, scheduleTime);
  }
  // End of file contains: AVG waiting time: <some real number>
  // "AVG" has already been consumed. Consume next two words before reading number.
  read<std::string>(outputFile); // Disacrd "waiting"
  read<std::string>(outputFile); // Discard "time:"
  auto const averageWaitingTime = read<float>(outputFile);
  return std::make_tuple(metaData, scheduleData, averageWaitingTime);
}

std::tuple<unsigned, bool> readIfUInt(std::istream& in)
{
  std::string input;
  std::regex uintPattern("[0-9]+");
  in >> input;
  if (std::regex_match(input, uintPattern))
  {
    return std::make_tuple(std::stod(input), true);
  }
  else
  {
    return std::make_tuple(0, false);
  }
}
