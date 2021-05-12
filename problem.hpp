#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Problem {
 public:
    Problem();
    void init();

    std::vector<std::vector<int>> getStartPuzzle() const;
    std::vector<std::vector<int>> getGoalPuzzle() const;

 private:
    std::vector<std::vector<int>> start;
    std::vector<std::vector<int>> goal;

    std::vector<std::vector<int>> defaultPuzzle();
    std::vector<std::vector<int>> customPuzzle();
    std::vector<int> parseInput(const std::string& input);
};
#endif // PROBLEM_HPP