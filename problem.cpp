#include "problem.hpp"

void Problem::Init() {
    std::cout << "\nWelcome to Sergio's 8 puzzle solver.\n" <<
        "Type \"1\" to use a default puzzle, or \"2\" to" <<
        " enter your own puzzle." << std::endl;

    std::string input;
    int selection;
    do {
        getline(std::cin, input);
        selection = std::stoi(input);

        switch (selection) {
            case 1: initial_state_ = ChooseDefaultPuzzle(); break;
            case 2: initial_state_ = MakeCustomPuzzle(); break;
            default: std::cout << "Enter \"1\" for a default puzzle " <<
                        "or \"2\" to enter your own puzzle." <<
                        std::endl; break;
        }
    } while (selection < 1 || selection > 2);

    std::vector<std::vector<int>> end_matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0} };
    goal_state_ = end_matrix;

    std::vector<std::string> actions = { "UP", "DOWN", "LEFT", "RIGHT" };
    actions_ = actions;
}

std::vector<std::vector<int>> Problem::GetStartPuzzle() const {
    return initial_state_;
}

std::vector<std::string> Problem::GetActions() const {
    return actions_;
}

std::vector<std::vector<int>> Problem::ToState(
        std::vector<std::vector<int>> state,
        const std::string& action) const {
    int row, col;
    bool found = false;
    // Locate the blank tile
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.at(i).size(); j++) {
            if (state.at(i).at(j) == 0) {
                row = i;
                col = j;
                found = true;
                break;
            }
        }
        if (found) { break; }
    }

    int placeholder;
    // Tile movement logic
    if (action == "UP") {
        if (row == 0) { return state; }
        placeholder = state.at(row - 1).at(col);
        state.at(row - 1).at(col) = state.at(row).at(col);
        state.at(row).at(col) = placeholder;
    } else if (action == "DOWN") {
        if (row == state.size() - 1) { return state; }
        placeholder = state.at(row + 1).at(col);
        state.at(row + 1).at(col) = state.at(row).at(col);
        state.at(row).at(col) = placeholder;
    } else if (action == "LEFT") {
        if (col == 0) { return state; }
        placeholder = state.at(row).at(col - 1);
        state.at(row).at(col - 1) = state.at(row).at(col);
        state.at(row).at(col) = placeholder;
    } else if (action == "RIGHT") {
        if (col == state.at(row).size() - 1) { return state; }
        placeholder = state.at(row).at(col + 1);
        state.at(row).at(col + 1) = state.at(row).at(col);
        state.at(row).at(col) = placeholder;
    }
    return state;
}

int Problem::ActionCost(const std::vector<std::vector<int>>& state,
                        const std::string& action) const {
    return 1;
}

bool Problem::IsGoal(const std::vector<std::vector<int>>& state) const {
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.at(i).size(); j++) {
            if (state.at(i).at(j) != goal_state_.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

void Problem::PrintPuzzleState(
        const std::vector<std::vector<int>>& state) const {
    for (int i = 0; i < state.size(); i++) {
        std::cout << "[ ";
        for (int j = 0; j < state.at(i).size(); j++) {
            std::cout << state.at(i).at(j) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

std::vector<std::vector<int>> Problem::ChooseDefaultPuzzle() {
    std::vector<std::vector<int>> trivial = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}};
    std::vector<std::vector<int>> veryEasy = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 0, 8}};
    std::vector<std::vector<int>> easy = {
            {1, 2, 0},
            {4, 5, 3},
            {7, 8, 6}};
    std::vector<std::vector<int>> doable = {
            {0, 1, 2},
            {4, 5, 3},
            {7, 8, 6}};
    std::vector<std::vector<int>> ohBoy = {
            {8, 7, 1},
            {6, 0, 2},
            {5, 4, 3}};
    std::vector<std::vector<int>> noChance = {
            {1, 2, 3},
            {4, 5, 6},
            {8, 7, 0}};
    std::string input;
    int selection;

    std::cout << "\nChoose the level of difficulty:\n" <<
        "(1) Trivial (2) Very Easy (3) Easy\n" <<
        "(4) Doable (5) Oh Boy (6) Impossible" <<
        std::endl;
    do {
        getline(std::cin, input);
        selection = std::stoi(input);
        switch (selection) {
            case 1: return trivial;
            case 2: return veryEasy;
            case 3: return easy;
            case 4: return doable;
            case 5: return ohBoy;
            case 6: return noChance;
            default: std::cout << "Enter a value between 1-6" <<
                            std::endl; break;
        }
    } while (selection < 1 || selection > 6);
    // Shouldn't reach here
    return easy;
}

std::vector<std::vector<int>> Problem::MakeCustomPuzzle() {
    std::vector<std::vector<int>> puzzle;
    std::string row;
    std::vector<std::string> messages = {
        "\nEnter your puzzle, use a zero to represent the blank\nEnter the first row, use space or tabs between numbers:  ",
        "Enter the second row, use space or tabs between numbers:  ",
        "Enter the third row, use space or tabs between numbers:  "
    };
    for (int i = 0; i < messages.size(); i++) {
        std::cout << messages.at(i);
        getline(std::cin, row);
        puzzle.push_back(ParseCustomInput(row));
    }
    return puzzle;
}

std::vector<int> Problem::ParseCustomInput(const std::string& input) {
    std::vector<int> row;
    std::string numbers;
    std::istringstream iss(input);  // Parses around whitespace
    while (iss >> numbers) {
        row.push_back(std::stoi(numbers));
    }
    return row;
}