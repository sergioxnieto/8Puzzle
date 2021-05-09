#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Problem {
 public:
    void init();

 private:
    int algorithmChoice();
    std::vector<std::vector<int>> defaultPuzzle();
    std::vector<std::vector<int>> customPuzzle();
    std::vector<int> parseInput(std::string input);

    std::vector<std::vector<int>> start;
    std::vector<std::vector<int>> goal;
    int algorithm;
};
#endif // PROBLEM_HPP