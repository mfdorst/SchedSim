#!/usr/bin/env bash

if command -v cmake &> /dev/null; then
  echo "\e[33mBuilding...\e[0m"
  cmake out
fi

for i in {1..16}; do
  cp "test_cases/input$i.txt" input.txt
  out/sched-sim
  git --no-pager diff --no-index "test_cases/output$i.txt" output.txt
done

rm input.txt
rm output.txt

if ! command -v cmake &> /dev/null; then
  echo "\e[31mCMake is not installed. \e[33mRemember to build before testing!\e[0m"
fi
