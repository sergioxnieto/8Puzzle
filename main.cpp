#include "problem.hpp"
#include "solver.hpp"
#include "node.hpp"
#include <cctype>
#include <stack>

int main() {
    Problem puzzle;
    puzzle.Init();

    Solver solve;
    if (!solve.IsSolvable(puzzle)) {
        std::cout << "\nThis puzzle cannot be solved." << std::endl;
        return -1;
    }

    std::cout << "\nEnter your choice of Algorithm\n" <<
            "(1) Uniform Cost Search\n" <<
            "(2) A* with the Misplaced Tile heuristic\n" <<
            "(3) A* with the Euclidian Distance heuristic" <<
            std::endl;

    std::string input;
    int selection;
    do {
        getline(std::cin, input);
        selection = std::stoi(input);

        switch (selection) {
            case 1: break;
            case 2: break;
            case 3: break;
            default: std::cout << "Type the number of your choice\n" <<
                    "(1) Uniform Cost Search\n" <<
                    "(2) A* with the Misplaced Tile Heuristic\n" <<
                    "(3) A* with the Euclidian Distance heuristic" <<
                    std::endl; break;
        }
    } while (selection < 1 || selection > 3);

    char debug;
    do {
        std::cout << "\nEnable live trace? Y or N: " << std::endl;
        std::cin >> debug;
        debug = std::tolower(debug);
    } while (debug != 'y' && debug != 'n');

    std::cout << "\nFinding solution..." << std::endl;

    std::shared_ptr<Node> result;
    if (debug == 'y') {
        switch (selection) {
            case 2: result = solve.AStarSearchTrace(puzzle, 0); break;
            case 3: result = solve.AStarSearchTrace(puzzle, 1); break;
            default: result = solve.UniformCostSearchTrace(puzzle); break;
        }
    } else {
        switch (selection) {
            case 2: result = solve.AStarSearch(puzzle, 0); break;
            case 3: result = solve.AStarSearch(puzzle, 1); break;
            default: result = solve.UniformCostSearch(puzzle); break;
        }
    }

    do {
        std::cout << "\nPrint solution? Y or N: " << std::endl;
        std::cin >> debug;
        debug = std::tolower(debug);
    } while (debug != 'y' && debug != 'n');

    if (debug == 'y') {
        std::stack<std::shared_ptr<Node>> instructions;
        while (result != nullptr) {
            instructions.push(result);
            result = result->GetParent();
        }
        while (!instructions.empty()) {
            result = instructions.top();
            std::cout << (*result) << std::endl;
            instructions.pop();
        }
    }

    std::cout << "\nDone!" << std::endl;

    return 0;
}