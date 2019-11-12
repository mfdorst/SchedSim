// TODO: Add header

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "../src/MetaData.h"
#include "../src/ScheduleData.h"

template <class T>
std::string fail(std::string const& message, T const& expected, T const& actual);

int main()
{
  unsigned const testCount = 16;
  unsigned failed = 0;
  std::vector<std::vector<std::string>> allFailures;
  allFailures.reserve(testCount);
  for (unsigned testNum = 1; testNum <= testCount; ++testNum)
  {
    // Set up the test input
    system(("cp test_cases/input" + std::to_string(testNum) + ".txt input.txt").c_str());
    // Run sched-sim on the test input
    system("../src/sched-sim");
    // Read the output and compare it with the expected output
    MetaData actualMetaData;
    MetaData expectedMetaData;
    ScheduleData actualSchedule;
    ScheduleData expectedSchedule;
    std::tie(actualMetaData, actualSchedule) = readScheduleData("output.txt");
    std::tie(expectedMetaData, expectedSchedule) =
        readScheduleData("test_cases/output" + std::to_string(testNum) + ".txt");
    // Fail if there are differences between actual and expected
    std::vector<std::string> failures;
    if (actualMetaData.algorithm != expectedMetaData.algorithm)
    {
      failures.push_back(fail("Wrong algorithm.", expectedMetaData.algorithm, actualMetaData.algorithm));
    }
    if (expectedMetaData.algorithm == "RR" and actualMetaData.timeQuantum != expectedMetaData.timeQuantum)
    {
      failures.push_back(fail("Wrong time quantum.", expectedMetaData.timeQuantum, expectedMetaData.timeQuantum));
    }
    if (expectedSchedule.size() != actualSchedule.size())
    {
      failures.push_back(fail("Incorrect number of CPU assignments.", expectedSchedule.size(), actualSchedule.size()));
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
      std::cout << "Test " << i + 1 << " failed.\n";
    }
    for (auto const& failureMessage : allFailures[i])
    {
      std::cout << failureMessage << "\n";
    }
  }
  std::cout << "\033[0m" << std::flush;
}

template <class T>
std::string fail(std::string const& message, T const& expected, T const& actual)
{
  std::stringstream ss;
  ss << message << "\n" << "Expected: " << expected << "\nActual: " << actual << "\n";
  return ss.str();
}
