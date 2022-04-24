#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "node.hpp"
#include "problem.hpp"

#include <unordered_set>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <cmath>

/// @brief Solver is a collection of algorithms that can be used to find a
/// solution path from a root Node to a Node with the goal state.
class Solver {
 public:
    /// @brief Applies the Uniform Cost Search algorithm to the search graph.
    /// @param puzzle Fully initialized Puzzle instance.
    /// @return Shared pointer to a Node that contains the goal state. Nullptr
    /// if queue is ever empty and a Node with the goal state is not found.
    std::shared_ptr<Node> UniformCostSearch(const Problem& puzzle) const;

    /// @brief Applies the Uniform Cost Search algorithm to the search graph
    /// and prints out a live trace of the Node's that are being expanded.
    /// @param puzzle Fully initialized Puzzle instance.
    /// @return Shared pointer to a Node that contains the goal state. Nullptr
    /// if queue is ever empty and a Node with the goal state is not found.
    std::shared_ptr<Node> UniformCostSearchTrace(const Problem& puzzle) const;

    /// @brief Applies the A* Search algorithm to the search graph. The
    /// heuristic used depends on the value of 'option'.
    /// @param puzzle Fully initialized Puzzle instance.
    /// @param option 0 to use Misplaced Tile as the heuristic. 1 to use
    /// Euclidian Distance as the heuristic.
    /// @return Shared pointer to a Node that contains the goal state. Nullptr
    /// if queue is ever empty and a Node with the goal state is not found.
    std::shared_ptr<Node> AStarSearch(const Problem& puzzle, int option) const;

    /// @brief Applies the A* Search algorithm to the search graph and prints
    /// out a live trace of the Node's that are being expanded. The
    /// heuristic used depends on the value of 'option'.
    /// @param puzzle Fully initialized Puzzle instance.
    /// @param option 0 to use Misplaced Tile as the heuristic. 1 to use
    /// Euclidian Distance as the heuristic.
    /// @return Shared pointer to a Node that contains the goal state. Nullptr
    /// if queue is ever empty and a Node with the goal state is not found.
    std::shared_ptr<Node> AStarSearchTrace(const Problem& puzzle,
                                           int option) const;

 private:
    /// @brief Searches the 'frontier' for the existence of Node's state.
    /// @param node Raw pointer to a Node. A std::shared_ptr is not needed
    /// since we only need to access the underlying object.
    /// @param frontier Vector of std::shared_ptr to search through.
    /// @return true, and the index if the Node's state is found, false and
    /// -1 if the state is not found.
    std::pair<bool, int> StateFound(
            const Node* node,
            const std::vector<std::shared_ptr<Node>>& frontier) const;

    /// @brief Calculates the expected position of 'target' in a
    /// completed puzzle.
    /// @param target Tile we want the expected position of.
    /// @param state_size Size N of an (NxN)-1 Puzzle. Example: an 8 Puzzle
    /// is of size 3... (3x3)-1 = 8.
    /// @return The row and column where 'target' should be found.
    std::pair<int, int> FindExpectedLocation(int target, int state_size) const;

    /// @brief Counts the number of tiles out of place. That value is used
    /// to find a better route to the goal state. This does not account
    /// for the position of the blank tile.
    /// @param state A Node's state that the heuristic will be applied on.
    /// @return Number of tiles that are not in their expected  position.
    int MisplacedTile(const std::vector<std::vector<int>>& state) const;

    /// @brief Finds the total distance that tiles need to travel to reach
    /// their expected location. That value is used to find a better route
    /// to the goal state. This does not account for the blank tile.
    /// @param state A Node's state that the heuristic will be applied on.
    /// @return Sum of the Euclidian Distance from each tile to its
    /// expected position.
    double EuclidianDistance(const std::vector<std::vector<int>>& state) const;
};

#endif // SOLVER_HPP