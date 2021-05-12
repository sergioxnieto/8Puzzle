#include "problem.hpp"

/* Problem(): Default constructor to initilize the problem
upon any new instances */
Problem::Problem() {
    init();
}

/* init(): Core function to fully initialize a Problem instance. 
Allows for default or custom puzzle selection, algorithm selection,
and sets the goal (a fully solved 8Puzzle). */
void Problem::init() {
    std::string tmp;
    int selection;
    std::vector<std::vector<int>> end = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    std::cout << "Welcome to 862154854's 8 puzzle solver.\n"
        << "Type \"1\" to use a default puzzle, or \"2\" to enter" 
        << " your own puzzle.\n";
    do {
        getline(std::cin, tmp);
        selection = std::stoi(tmp);
        switch (selection) {
            case 1: start = defaultPuzzle(); break;
            case 2: start = customPuzzle(); break;
            default: std::cout << "Enter \"1\" for a default puzzle "
                << "or \"2\" to enter your own puzzle\n"; break;
        }
    } while (selection < 1 || selection > 2);
    // algorithm = algorithmChoice();
    goal = end;

}

/* getStartPuzzle(): Caller will receive the 8Puzzle starting
configuration that the user created */
std::vector<std::vector<int>> Problem::getStartPuzzle() const {
    return start;
}

/* getGoalPuzzle(): Caller will receive the 2D array of a fully
completed 8Puzzle */
std::vector<std::vector<int>> Problem::getGoalPuzzle() const {
    return goal;
}

/* DefaultPuzzle(): Allows the user to make a choice between 1-6
and will return a pre-configured puzzle based on the choice */
std::vector<std::vector<int>> Problem::defaultPuzzle() {
    std::string tmp;
    int selection;
    std::vector<std::vector<int>> trivial = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    std::vector<std::vector<int>> veryEasy = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
    std::vector<std::vector<int>> easy = {{1, 2, 0}, {4, 5, 3}, {7, 8, 6}};
    std::vector<std::vector<int>> doable = {{0, 1, 2}, {4, 5, 3}, {7, 8, 6}};
    std::vector<std::vector<int>> ohBoy = {{8, 7, 1}, {6, 0, 2}, {5, 4, 3}};
    std::vector<std::vector<int>> noChance = {{1, 2, 3}, {4, 5, 6}, {8, 7, 0}};

    std::cout << "\nChoose the level of difficulty:\n" 
        << "(1) Trivial (2) Very Easy (3) Easy\n" 
        << "(4) Doable (5) Oh Boy (6) Impossible\n";
    do {
        getline(std::cin, tmp);
        selection = std::stoi(tmp);
        switch (selection) {
            case 1: return trivial;
            case 2: return veryEasy;
            case 3: return easy;
            case 4: return doable;
            case 5: return ohBoy;
            case 6: return noChance;
            default: std::cout << "Enter a value between 1-6\n"; break;
        }
    } while (selection < 1 || selection > 6);

    // Shouldn't reach here
    return easy;
}

/* customPuzzle(): Helper function that allows the user to input their own custom 
puzzle and returns it as a 2D vector for later usage */
std::vector<std::vector<int>> Problem::customPuzzle() {
    std::vector<std::vector<int>> puzzle;
    std::string row1, row2, row3;
    std::cout << "\nEnter your puzzle, use a zero to represent the blank\n"
        << "Enter the first row, use space or tabs between numbers:  ";
    getline(std::cin, row1);
    std::cout << "Enter the second row, use space or tabs between numbers:  ";
    getline(std::cin, row2);
    std::cout << "Enter the third row, use space or tabs between numbers:  ";
    getline(std::cin, row3);

    puzzle.push_back(parseInput(row1));
    puzzle.push_back(parseInput(row2));
    puzzle.push_back(parseInput(row3));
    return puzzle;
}

/* parseInput(string input): Helper function to tokenize the input string. 
This returns a vector with all the numbers inputted by the user. */
std::vector<int> Problem::parseInput(const std::string& input) {
    std::vector<int> row; 
    std::string tmp;

    std::istringstream nums(input);
    while (nums >> tmp) {
        row.push_back(std::stoi(tmp));
    }
    return row;
}