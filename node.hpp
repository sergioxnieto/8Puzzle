#ifndef NODE_HPP
#define NODE_HPP

#include "problem.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

/// @brief Nodes are the tools used to construct a search graph that allows
/// us to find a solution from the root Node to the goal state. It is important
/// that a Node's path cost, heuristic, and total cost values are initialized
/// since the tools in Solver rely on those values to perform calculations.
/// The reason we store a shared pointer is because many Nodes can have the
/// same parent so a unique pointer would not be helpful.
class Node {
 public:
    /// @brief Constructs a Node to be used as the root of the search graph.
    /// @param puzzle Fully initialized Puzzle object to set this node's state.
    Node(const Problem& puzzle);

    /// @brief Constructs a Node to be used as a child of another Node.
    /// @param puzzle Fully initialized Puzzle object used to set this Node's
    /// state by performing an action on the parent Node's state.
    /// @param parent A root or child Node pointer that is stored in this
    /// Node and is used to print the solution path.
    /// @param action String representing the action performed to get
    /// to this Node's state.
    Node(const Problem& puzzle, std::shared_ptr<Node> parent,
         const std::string& action);

    /// @brief Accesses this Node's parent Node.
    /// @return Shared pointer to this Node's parent. Null if this Node
    /// is the root node.
    std::shared_ptr<Node> GetParent() const;

    /// @brief Accesses this Node's puzzle state.
    /// @return 2D vector representing this Node's current state.
    std::vector<std::vector<int>> GetState() const;

    /// @brief Accesses the cost of that path that led to this Node.
    /// @return The depth of this Node in the search tree.
    int GetPathCost() const;

    /// @brief Accesses the heuristic value stored for this Node.
    /// @return The estimated cost for this Node to reach the goal.
    double GetDistanceToGoal() const;

    /// @brief  Accesses the total cost stored for this Node.
    /// @return The sum of the path cost and heuristic of this Node.
    double GetTotalCost() const;

    /// @brief Modifies the heuristic value of this Node, and updates
    /// the total cost to reflect the sum of this Node's path cost
    /// and newly updated heuristic value.
    /// @param heuristic Value returned by any heuristic function (i.e.
    /// Misplaced Tile or Euclidian Distance)
    void ApplyHeuristic(double heuristic);

    /// @brief Converts this Node's state to a string. This is done to
    /// use std::unordered_set<std::string>'s default hashing method
    /// for strings.
    /// @return String representation of this Node's state
    std::string ToString() const;

    /// @brief Uses the Node's total cost to compare two Nodes.
    /// @return true if the left Node has a higher total cost than
    /// the right Node.
    friend bool operator>(const Node& lhs, const Node& rhs);

    /// @brief Prints a Node's state, action that led to it, the path
    /// cost, heuristic, and total cost.
    friend std::ostream& operator<<(std::ostream& os, const Node& node);

 private:
    std::shared_ptr<Node> parent_;
    std::vector<std::vector<int>> state_;
    std::string action_;  // Action taken from parent to reach this Node.
    int path_cost_;  // Distance from the root Node.
    double heuristic_;  // Estimated distance to goal.
    double total_cost_;  // Path cost + heuristic.
};

#endif // NODE_HPP