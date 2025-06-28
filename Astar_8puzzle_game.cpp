#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 3;

// Function to print the puzzle
void printPuzzle(const vector<vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (int val : row) {
            cout << (val ? to_string(val) : " ") << " ";
        }
        cout << endl;
    }
    cout << "-------" << endl;
}

// Function to check if two states are equal
bool areStatesEqual(const vector<vector<int>>& state1, const vector<vector<int>>& state2) {
    return state1 == state2;
}

// Function to find the position of the blank tile (0)
pair<int, int> findBlankTile(const vector<vector<int>>& puzzle) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should not happen if puzzle is valid
}

// Function to generate new states by moving the blank tile
vector<pair<string, vector<vector<int>>>> generateNewStates(const vector<vector<int>>& puzzle) {
    pair<int, int> blankPos = findBlankTile(puzzle);
    int row = blankPos.first, col = blankPos.second;

    vector<pair<string, pair<int, int>>> moves = {
        {"up", {-1, 0}}, {"down", {1, 0}}, {"left", {0, -1}}, {"right", {0, 1}}
    };

    vector<pair<string, vector<vector<int>>>> newStates;

    for (const auto& move : moves) {
        int newRow = row + move.second.first, newCol = col + move.second.second;
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
            vector<vector<int>> newPuzzle = puzzle;
            swap(newPuzzle[row][col], newPuzzle[newRow][newCol]);
            newStates.push_back({move.first, newPuzzle});
        }
    }
    return newStates;
}

// Heuristic h1: Number of misplaced tiles
int heuristicMisplacedTiles(const vector<vector<int>>& puzzle, const vector<vector<int>>& goal) {
    int h1 = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j]) {
                h1++;
            }
        }
    }
    return h1;
}

// Heuristic h2: Manhattan distance
int heuristicManhattanDistance(const vector<vector<int>>& puzzle, const vector<vector<int>>& goal) {
    int distance = 0;
    map<int, pair<int, int>> goalPositions;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            goalPositions[goal[i][j]] = {i, j};

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] != 0) {
                auto [goalRow, goalCol] = goalPositions[puzzle[i][j]];
                distance += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }
    return distance;
}

// Function to reconstruct the solution path
vector<vector<vector<int>>> reconstructPath(map<vector<vector<int>>, vector<vector<int>>>& parentMap, vector<vector<int>> goal) {
    vector<vector<vector<int>>> path;
    while (parentMap.find(goal) != parentMap.end()) {
        path.push_back(goal);
        goal = parentMap[goal];
    }
    path.push_back(goal); // Add the start state
    reverse(path.begin(), path.end());
    return path;
}

// A* search algorithm
vector<vector<vector<int>>> aStarSearch(vector<vector<int>> start, vector<vector<int>> goal, int heuristicType) {
    auto compare = [](const pair<int, pair<int, vector<vector<int>>>>& a, const pair<int, pair<int, vector<vector<int>>>>& b) {
        return a.first > b.first;
    };

    priority_queue<pair<int, pair<int, vector<vector<int>>>>, vector<pair<int, pair<int, vector<vector<int>>>>>, decltype(compare)> openList(compare);
    set<vector<vector<int>>> visited;
    map<vector<vector<int>>, vector<vector<int>>> parentMap;

    int initialH = heuristicType == 1 ? heuristicMisplacedTiles(start, goal) : heuristicManhattanDistance(start, goal);
    openList.push({initialH, {0, start}});

    while (!openList.empty()) {
        auto current = openList.top();
        openList.pop();

        vector<vector<int>> currentState = current.second.second;
        int g = current.second.first;

        if (areStatesEqual(currentState, goal)) {
            return reconstructPath(parentMap, goal);
        }

        if (visited.find(currentState) != visited.end()) {
            continue;
        }

        visited.insert(currentState);

        for (const auto& neighbor : generateNewStates(currentState)) {
            vector<vector<int>> newState = neighbor.second;

            if (visited.find(newState) == visited.end()) {
                int h = heuristicType == 1 ? heuristicMisplacedTiles(newState, goal) : heuristicManhattanDistance(newState, goal);
                openList.push({g + 1 + h, {g + 1, newState}});
                parentMap[newState] = currentState;
            }
        }
    }
    return {};  // Return empty on failure.
}

// Main function
int main() {
    vector<vector<int>> startState(N, vector<int>(N));
    vector<vector<int>> goalState(N, vector<int>(N));

    cout << "Enter the start state (tile by tile, use 0 for blank):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Enter tile at position (" << i << ", " << j << "): ";
            cin >> startState[i][j];
        }
    }

    cout << "Enter the goal state (tile by tile, use 0 for blank):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Enter tile at position (" << i << ", " << j << "): ";
            cin >> goalState[i][j];
        }
    }

    int heuristicType;
    cout << "Choose the heuristic to use (1 for Misplaced Tiles, 2 for Manhattan Distance): ";
    cin >> heuristicType;

    cout << "Start State:" << endl;
    printPuzzle(startState);

    cout << "Goal State:" << endl;
    printPuzzle(goalState);

    cout << "Running A* search..." << endl;
    vector<vector<vector<int>>> solutionPath = aStarSearch(startState, goalState, heuristicType);

    if (!solutionPath.empty()) {
        cout << "Solution found in " << solutionPath.size() - 1 << " moves:" << endl;
        for (size_t i = 0; i < solutionPath.size(); ++i) {
            cout << "Step " << i << ":" << endl;
            printPuzzle(solutionPath[i]);
        }
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
