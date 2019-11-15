cmake_minimum_required(VERSION 3.15)
project(sched-sim)

set(CMAKE_CXX_STANDARD 11)

add_executable(sched-sim main.cpp RoundRobin.h ProcessData.h ScheduleType.h ScheduleData.h Util.h ShortestJobFirst.h)
