# 8-Puzzle Game

This project implements the classic **8-Puzzle Game** using the A* (A-star) search algorithm. The game is written entirely in C++.

## Overview

The 8-Puzzle Game is a sliding tile puzzle consisting of a 3x3 grid with 8 numbered tiles and one blank space. The objective is to rearrange the tiles to reach a specified goal state by sliding tiles into the blank space, using the fewest possible moves.

The A* algorithm is used to efficiently solve the puzzle, finding the shortest sequence of moves from the starting configuration to the goal configuration.

## Features

- Command-line interface for entering initial and goal states
- Solves the puzzle using the A* algorithm
- Supports custom initial and goal configurations
- Displays the sequence of moves and the solution path
- Written in modern C++ for performance and clarity

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later (e.g., g++, clang++)
- Make (optional, if a Makefile is provided)

### Compilation

You can compile the project using the following command:

```sh
g++ -std=c++11 -o 8puzzle main.cpp
```

Replace `main.cpp` with the name of your main source file if different.

### Usage

Run the compiled executable:

```sh
./8puzzle
```

Follow the prompts to enter the initial and goal states of the puzzle. The program will then display the steps to solve the puzzle.

## Example

```
Enter the initial state (use 0 for blank):
1 2 3
4 0 6
7 5 8

Enter the goal state (use 0 for blank):
1 2 3
4 5 6
7 8 0

Solving...

Solution found in 4 moves!
Step 1: ...
...
```

## Algorithm

This project uses the A* search algorithm, which combines the cost to reach a node and a heuristic estimate of the cost to reach the goal. The heuristic typically used for the 8-puzzle is the Manhattan distance.

## Contributing

Contributions are welcome! Please open issues or pull requests for improvements or bug fixes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Wikipedia: 8-puzzle](https://en.wikipedia.org/wiki/15_puzzle)
- [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)

*Created by AliHadi-RAI*
