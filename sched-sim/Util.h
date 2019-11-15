//===- Util.h --- sched-sim: A CPU scheduling simulator -------------------------------------------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===--------------------------------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains general utility functions - specifically the `read()` function.
///
//===--------------------------------------------------------------------------------------------------------------===//

#pragma once

/// Reads a single value from an input stream.
///
/// \tparam T The type of data to read
/// \param in The input stream to read from
/// \return The value read from the input stream
template <class T>
T read(std::istream& in)
{
  T t;
  in >> t;
  return t;
}
