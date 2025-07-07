#!/bin/bash

# Create output directory if it doesn't exist
mkdir -p output

# Clean previous output files
rm -rf output/*

# Process the graph and generate output files
./grafy -s -o output -i input/line.txt

# Generate SVG visualization
dot -Tsvg -O output/graph.dot

# Optional: Open the SVG file (uncomment for your platform)
# xdg-open output/graph.dot.svg   # Linux
# open output/graph.dot.svg       # macOS
# start output/graph.dot.svg      # Windows
