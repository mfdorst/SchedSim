#!/usr/bin/env bash

# for x = 1 -> 16
#   copy test_cases/input{x}.txt to input.txt
#   out/sched-sim
#   check that output.txt matches test_cases/output{x}.txt
#
# delete input.txt
# delete output.txt

for i in {1..16}; do
  cp "test_cases/input$i.txt" input.txt
  out/sched-sim
  git --no-pager diff --no-index "test_cases/output$i.txt" output.txt
done

rm input.txt
rm output.txt
