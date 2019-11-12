// TODO: Add header

#pragma once

#include <string>

struct MetaData {
  std::string algorithm;
  unsigned timeQuantum;
  
  MetaData() : timeQuantum(0) {}
};
