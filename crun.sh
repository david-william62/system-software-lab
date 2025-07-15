#!/bin/bash

# Check if a file argument is passed
if [ -z "$1" ]; then
  echo "Please provide a C file to compile."
  exit 1
fi

# Check if the provided file exists
if [ ! -f "$1" ]; then
  echo "File $1 not found!"
  exit 1
fi

# Compile the C file
gcc "$1" -o a.out

# Check if compilation was successful
if [ $? -eq 0 ]; then
  # Run the compiled program
  ./a.out
else
  echo "Compilation failed."
  exit 1
fi

