//===- main.cpp -----------------------------------------------------------------------------------------*- C++ -*-===//
//
// sched-sim - A CPU scheduling simulator
// Author: Michael Dorst
//
// CSC 139
// Fall 2019
// Section 2
// Homework 3
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file is the entry point for sched-sim
///
//===--------------------------------------------------------------------------------------------------------------===//

#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;
using std::string;
using std::endl;

int main()
{
  ifstream in("input.txt");
  ofstream out("output.txt");
  string algorithm;
  unsigned timeQuantumLength = 0;
  in >> algorithm;
  out << algorithm;
  if (algorithm == "RR") {
    in >> timeQuantumLength;
    out << " " << timeQuantumLength;
  }
  out << endl;
  
  return 0;
}
