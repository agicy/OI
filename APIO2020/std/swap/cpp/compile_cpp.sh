#!/bin/bash

problem=swap

g++ -std=c++11 -o "${problem}" "${problem}.cpp" "grader.cpp" -O2 -lm
