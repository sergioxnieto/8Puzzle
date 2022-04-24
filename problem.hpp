#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

/// @brief Problem should be used whenever one wants to create a new 8Puzzle
/// instance. In order to work properly, Problem::Init() needs to be called
/// to set everything up.
class Problem {
 public:

    /// @brief Intializes a Problem instance by setting the starting puzzle
    /// configuration, the goal, and available actions.
    void Init();

    /// @brief Get this problem's starting puzzle configuration.
    /// @return 2D vector representing the starting configuration.
    std::vector<std::vector<int>> GetStartPuzzle() const;

    /// @brief Get this problem's available actions.
    /// @return Vector of the available actions: "UP", "DOWN", "LEFT", "RIGHT".
    std::vector<std::string> GetActions() const;


    /// @brief Generates the state reached by performing an action on the
    /// current state.
    /// @param state  Current puzzle state.
    /// @param action One of the actions: "UP", "DOWN", "LEFT", "RIGHT".
    /// @return 2D vector of the new state after doing the action. If the action
    /// can't be done, due to the blank tile being on the edge, it returns the
    /// original state.
    std::vector<std::vector<int>> ToState(std::vector<std::vector<int>> state,
                                          const std::string& action) const;

    /// @brief Provides the cost it takes to execute an action on a state.
    /// @param state Current puzzle state.
    /// @param action One of the actions: "UP", "DOWN", "LEFT", "RIGHT".
    /// @return 1 since each move carries the same weight.
    int ActionCost(const std::vector<std::vector<int>>& state,
                   const std::string& action) const;

    /// @brief Checks if we reached the goal and solved the puzzle.
    /// @param state Current puzzle state.
    /// @return true if current state matches the goal state.
    bool IsGoal(const std::vector<std::vector<int>>& state) const;

    /// @brief Prints the given state to the console.
    /// @param state Current puzzle state.
    void PrintPuzzleState(const std::vector<std::vector<int>>& state) const;

 private:
    std::vector<std::vector<int>> initial_state_;
    std::vector<std::vector<int>> goal_state_;
    std::vector<std::string> actions_;

    /// @brief Prompts the user to choose a pre-configured
    /// puzzle out of 1-6 (inclusive) options.
    /// @return 2D vector representing a pre-configured puzzle.
    std::vector<std::vector<int>> ChooseDefaultPuzzle();

    /// @brief Creates a custom puzzle configuration based on the user's input.
    /// @return 2D vector representing a user-made puzzle.
    std::vector<std::vector<int>> MakeCustomPuzzle();

    /// @brief Extracts the numbers from a user-supplied string and adds
    /// them to a vector.
    /// @param input String of numbers separated by whitespace.
    /// @return A vector that represents a row in an 8-Puzzle.
    std::vector<int> ParseCustomInput(const std::string& input);
};
#endif // PROBLEM_HPP