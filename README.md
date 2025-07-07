# Grafy

A C++ graph analysis utility that performs comprehensive graph calculations and analysis. This tool can read graph data from files or standard input, perform various graph computations, and output results to files or terminal.

## Features

- **Graph Analysis**: Analyzes graph structure, connectivity, and properties
- **Distance Calculations**: Computes shortest paths between vertices
- **Component Detection**: Identifies connected components in the graph
- **Matrix Operations**: Performs matrix power calculations for graph analysis
- **Triangle Counting**: Counts triangles in the graph
- **Graph Visualization**: Generates DOT format files for Graphviz rendering
- **Multiple Input/Output Formats**: Supports file and standard I/O
- **Silent Mode**: Option to suppress interactive output for batch processing
- **Multiple Output Formats**: SVG, PNG, PDF, JPEG visualization support

## Installation

### Prerequisites

- C++ compiler (GCC/G++)
- Make
- Graphviz (required for visualization features)

### Installing Graphviz

Graphviz is required for generating graph visualizations. Here are installation instructions for different platforms:

#### macOS
```bash
# Using Homebrew (recommended)
brew install graphviz

# Using MacPorts
sudo port install graphviz
```

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install graphviz
```

#### CentOS/RHEL/Fedora
```bash
# CentOS/RHEL
sudo yum install graphviz

# Fedora
sudo dnf install graphviz
```

#### Windows
```bash
# Using Chocolatey
choco install graphviz

# Using Scoop
scoop install graphviz

# Manual installation
# Download from https://graphviz.org/download/
```

#### Arch Linux
```bash
sudo pacman -S graphviz
```

#### FreeBSD
```bash
sudo pkg install graphviz
```

#### Verification
After installation, verify Graphviz is working:
```bash
dot -V
# Should display version information
```

### Building

```bash
# Clone or download the project
cd grafy

# Build the project
make

# The executable 'grafy' will be created in the current directory
```

### System Installation (Optional)

```bash
# Install to system path
make install

# Remove from system path
make uninstall
```

## Usage

### Basic Syntax

```bash
./grafy [options]
```

### Command Line Options

- `-h`: Display help information
- `-s`: Silent mode (suppresses interactive output)
- `-i <file>`: Input file containing edge data (uses stdin if not specified)
- `-o <directory>`: Output directory for results (uses stdout if not specified)

### Input Format

The input file should contain edge data in the following format:
```
vertex1 vertex2
vertex2 vertex3
vertex3 vertex4
...
```

Each line represents an edge between two vertices. Vertices are identified by integers.

### Examples

#### Basic Usage
```bash
# Read from file and output to terminal
./grafy -i input/line.txt

# Read from stdin
echo "1 2\n2 3\n3 4" | ./grafy

# Silent mode with file output
./grafy -s -i input/circle.txt -o output/
```

#### Visualization with Graphviz
```bash
# Run the example script
./run.sh

# This will:
# 1. Process input/line.txt
# 2. Generate output files in output/ directory
# 3. Create SVG visualization using Graphviz

# Manual visualization
./grafy -s -o output/ -i input/line.txt
dot -Tsvg -O output/graph.dot

# Other output formats
dot -Tpng -O output/graph.dot    # PNG format
dot -Tpdf -O output/graph.dot    # PDF format
dot -Tjpg -O output/graph.dot    # JPEG format
```

**Note**: The `dot` command is part of Graphviz. Make sure Graphviz is installed before running visualization commands.

#### Troubleshooting Graphviz

**Common Issues:**
- **Command not found**: Ensure Graphviz is properly installed and in your PATH
- **Permission denied**: Make sure the output directory exists and is writable
- **No output generated**: Check that the input file contains valid graph data

**Verification Commands:**
```bash
# Check if dot is available
which dot

# Test dot with a simple graph
echo 'digraph { A -> B; }' | dot -Tsvg -o test.svg

# Check Graphviz version
dot -V
```

## Example Input Files

The `input/` directory contains several example files:

- `line.txt`: Simple linear graph (1-2-3-4)
- `circle.txt`: Circular graph with 16 vertices
- `cycle.txt`: Small cycle graph
- `diamond.txt`: Diamond-shaped graph
- `bridge.txt`: Graph with bridge structure
- `multi.txt`: Multiple connected components
- `pairs.txt`: Complex graph with multiple edges
- `fail01.txt`, `fail02.txt`, `fail03.txt`: Test cases for error handling

## Output

The program generates comprehensive graph analysis including:

- **Graph Statistics**: Vertex count, edge count, component count
- **Connectivity Analysis**: Whether the graph is continuous
- **Distance Matrix**: Shortest paths between all vertex pairs
- **Triangle Count**: Number of triangles in the graph
- **Matrix Powers**: Adjacency matrix raised to various powers
- **Component Information**: Details about connected components

## Project Structure

```
grafy/
├── src/
│   ├── main.cpp              # Main application entry point
│   ├── model/                # Graph data structures
│   │   ├── Graph.cpp         # Main graph class implementation
│   │   ├── Matrix.cpp        # Matrix operations
│   │   ├── Tree.cpp          # Tree data structure
│   │   └── hpp/              # Header files
│   ├── io/                   # Input/Output processing
│   │   ├── InputProcessor.cpp
│   │   ├── OutputProcessor.cpp
│   │   ├── FileOutputProcessor.cpp
│   │   └── TerminalOutputProcessor.cpp
│   ├── util/                 # Utility functions
│   │   ├── Util.cpp          # Command line parsing
│   │   └── Util.hpp
│   └── exception/            # Exception handling
│       └── hpp/              # Custom exception classes
├── input/                    # Example input files
├── Makefile                  # Build configuration
├── run.sh                    # Example execution script
└── README.md                 # This file
```

## Technical Details

- **Language**: C++
- **Build System**: Make
- **Compilation**: GCC with debug symbols and optimization disabled
- **Architecture**: Object-oriented design with separate modules for I/O, graph processing, and utilities
- **Error Handling**: Comprehensive exception handling for invalid inputs and edge cases

## Development

### Building from Source

```bash
# Clean build artifacts
make clean

# Build with line count
make

# Install to system
make install
```

### Code Structure

The project follows a modular architecture:
- **Model Layer**: Graph, Matrix, Tree, and Vertex classes
- **I/O Layer**: Input and output processors for different formats
- **Utility Layer**: Command line parsing and helper functions
- **Exception Layer**: Custom exception classes for error handling

## License

This project is provided as-is for educational and research purposes.
