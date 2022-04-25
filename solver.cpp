#include "solver.hpp"

/// @brief Functor that is used to sort std::shared_ptr.
/// Compares the underlying object instead of the pointer address.
struct SharedPtrCompare {
    bool operator()(const std::shared_ptr<Node>& lhs,
                    const std::shared_ptr<Node>& rhs) {
        return (*lhs) > (*rhs);
    }
};

bool Solver::IsSolvable(const Problem& puzzle) const {
    std::vector<std::vector<int>> state = puzzle.GetStartPuzzle();
    std::vector<int> flattened;
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.at(i).size(); j++) {
            if (state.at(i).at(j))  {
                flattened.push_back(state.at(i).at(j));
            }
        }
    }
    int inversion_count = 0;
    for (int i = 0; i < flattened.size() - 1; i++) {
        for (int j = i + 1; j < flattened.size(); j++) {
            if (flattened.at(j) > flattened.at(i)) {
                inversion_count++;
            }
        }
    }
    return (inversion_count % 2 == 0);
}

std::shared_ptr<Node> Solver::UniformCostSearch(const Problem& puzzle) const {
    SharedPtrCompare desc_order;
    std::vector<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::string> explored;
    int max_frontier_size = 0;
    int num_nodes_expanded = 0;
    std::shared_ptr<Node> node = std::make_shared<Node>(puzzle);

    frontier.push_back(std::move(node));
    while (!frontier.empty()) {
        if (frontier.size() > max_frontier_size) {
            max_frontier_size = frontier.size();
        }

        std::sort(frontier.begin(), frontier.end(), desc_order);

        node = frontier.back();  // Lowest-cost node
        frontier.pop_back();  // Removes the reference

        if (puzzle.IsGoal(node->GetState())) {
            std::cout << "To solve this problem the search algorithm " <<
                "expanded a total of " << num_nodes_expanded <<
                " node(s)." << std::endl;
            std::cout << "The maximum number of nodes in the queue " <<
                "at any one time: " << max_frontier_size << std::endl;
            return node;
        }
        explored.insert(node->ToString());

        // Expand the node by generating children
        std::vector<std::string> actions = puzzle.GetActions();
        for (const std::string& action : actions) {
            std::shared_ptr<Node> child = std::make_shared<Node>(puzzle, node,
                                                                 action);
            std::pair<bool, int> in_frontier = StateFound(child.get(),
                                                          frontier);
            int in_explored = explored.count(child->ToString());
            if (!in_frontier.first && !in_explored) {
                frontier.push_back(std::move(child));
            } else if (in_frontier.first) {
                int i = in_frontier.second;
                if (frontier.at(i)->GetTotalCost() > child->GetTotalCost()) {
                    frontier.at(i) = child;
                }
            }
        }
        num_nodes_expanded++;
    }
    // Failed if we reach here
    return nullptr;
}

std::shared_ptr<Node> Solver::UniformCostSearchTrace(
        const Problem& puzzle) const {
    SharedPtrCompare desc_order;
    std::vector<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::string> explored;
    bool first_run = true;
    int max_frontier_size = 0;
    int num_nodes_expanded = 0;
    std::shared_ptr<Node> node = std::make_shared<Node>(puzzle);

    std::cout << "\nExpanding State" << std::endl;
    puzzle.PrintPuzzleState(node->GetState());

    frontier.push_back(std::move(node));
    while (!frontier.empty()) {
        if (frontier.size() > max_frontier_size) {
            max_frontier_size = frontier.size();
        }

        std::sort(frontier.begin(), frontier.end(), desc_order);

        node = frontier.back();  // Lowest-cost node
        frontier.pop_back();  // Removes the reference

        if (!first_run){
            std::cout << "Best state to expand with g(n) = " <<
                node->GetPathCost() << " and h(n) = " <<
                node->GetDistanceToGoal() << " is... " << std::endl;
            puzzle.PrintPuzzleState(node->GetState());
            std::cout << "Expanding this node..." << std::endl;
        }
        if (puzzle.IsGoal(node->GetState())) {
            std::cout << "\nGoal!!!" << std::endl;
            std::cout << "To solve this problem the search algorithm " <<
                "expanded a total of " << num_nodes_expanded <<
                " node(s)." << std::endl;
            std::cout << "The maximum number of nodes in the queue " <<
                "at any one time: " << max_frontier_size << std::endl;
            return node;
        }
        explored.insert(node->ToString());

        // Expand the node by generating children
        std::vector<std::string> actions = puzzle.GetActions();
        for (const std::string& action : actions) {
            std::shared_ptr<Node> child = std::make_shared<Node>(puzzle, node,
                                                                 action);
            std::pair<bool, int> in_frontier = StateFound(child.get(),
                                                          frontier);
            int in_explored = explored.count(child->ToString());
            if (!in_frontier.first && !in_explored) {
                frontier.push_back(std::move(child));
            } else if (in_frontier.first) {
                int i = in_frontier.second;
                if (frontier.at(i)->GetTotalCost() > child->GetTotalCost()) {
                    frontier.at(i) = child;
                }
            }
        }
        num_nodes_expanded++;
        first_run = false;
    }
    // Failed if we reach here
    return nullptr;
}

std::shared_ptr<Node> Solver::AStarSearch(const Problem& puzzle,
                                          int option) const {
    SharedPtrCompare desc_order;
    std::vector<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::string> explored;
    int max_frontier_size = 0;
    int num_nodes_expanded = 0;
    std::shared_ptr<Node> node = std::make_shared<Node>(puzzle);
    if (option == 0) {
        node->ApplyHeuristic(MisplacedTile(node->GetState()));
    } else {
        node->ApplyHeuristic(EuclidianDistance(node->GetState()));
    }

    frontier.push_back(std::move(node));
    while (!frontier.empty()) {
        if (frontier.size() > max_frontier_size) {
            max_frontier_size = frontier.size();
        }

        std::sort(frontier.begin(), frontier.end(), desc_order);

        node = frontier.back();  // Lowest-cost node
        frontier.pop_back();  // Removes the reference

        if (puzzle.IsGoal(node->GetState())) {
            std::cout << "To solve this problem the search algorithm " <<
                "expanded a total of " << num_nodes_expanded <<
                " node(s)." << std::endl;
            std::cout << "The maximum number of nodes in the queue " <<
                "at any one time: " << max_frontier_size << std::endl;
            return node;
        }
        explored.insert(node->ToString());

        // Expand the node by generating children
        std::vector<std::string> actions = puzzle.GetActions();
        for (const std::string& action : actions) {
            std::shared_ptr<Node> child = std::make_shared<Node>(puzzle,
                                                                 node, action);
            if (option == 0) {
                child->ApplyHeuristic(MisplacedTile(child->GetState()));
            } else {
                child->ApplyHeuristic(EuclidianDistance(child->GetState()));
            }
            std::pair<bool, int> in_frontier = StateFound(child.get(),
                                                          frontier);
            int in_explored = explored.count(child->ToString());

            if (!in_frontier.first && !in_explored) {
                frontier.push_back(std::move(child));
            } else if (in_frontier.first) {
                int i = in_frontier.second;
                if (frontier.at(i)->GetTotalCost() > child->GetTotalCost()) {
                    frontier.at(i) = child;
                }
            }
        }
        num_nodes_expanded++;
    }
    // Failed if we reach here
    return nullptr;
}

std::shared_ptr<Node> Solver::AStarSearchTrace(const Problem& puzzle,
                                               int option) const {
    SharedPtrCompare desc_order;
    std::vector<std::shared_ptr<Node>> frontier;
    std::unordered_set<std::string> explored;
    bool first_run = true;
    int max_frontier_size = 0;
    int num_nodes_expanded = 0;
    std::shared_ptr<Node> node = std::make_shared<Node>(puzzle);
    if (option == 0) {
        node->ApplyHeuristic(MisplacedTile(node->GetState()));
    } else {
        node->ApplyHeuristic(EuclidianDistance(node->GetState()));
    }

    std::cout << "\nExpanding State" << std::endl;
    puzzle.PrintPuzzleState(node->GetState());

    frontier.push_back(std::move(node));
    while (!frontier.empty()) {
        if (frontier.size() > max_frontier_size) {
            max_frontier_size = frontier.size();
        }

        std::sort(frontier.begin(), frontier.end(), desc_order);

        node = frontier.back();  // Lowest-cost node
        frontier.pop_back();  // Removes the reference

        if (!first_run){
            std::cout << "Best state to expand with g(n) = " <<
                node->GetPathCost() << " and h(n) = " <<
                node->GetDistanceToGoal() << " is... " << std::endl;
            puzzle.PrintPuzzleState(node->GetState());
            std::cout << "Expanding this node..." << std::endl;
        }
        if (puzzle.IsGoal(node->GetState())) {
            std::cout << "\nGoal!!!" << std::endl;
            std::cout << "To solve this problem the search algorithm " <<
                "expanded a total of " << num_nodes_expanded <<
                " node(s)." << std::endl;
            std::cout << "The maximum number of nodes in the queue " <<
                "at any one time: " << max_frontier_size << std::endl;
            return node;
        }
        explored.insert(node->ToString());

        // Expand the node by generating children
        std::vector<std::string> actions = puzzle.GetActions();
        for (const std::string& action : actions) {
            std::shared_ptr<Node> child = std::make_shared<Node>(puzzle,
                                                                 node, action);
            if (option == 0) {
                child->ApplyHeuristic(MisplacedTile(child->GetState()));
            } else {
                child->ApplyHeuristic(EuclidianDistance(child->GetState()));
            }
            std::pair<bool, int> in_frontier = StateFound(child.get(),
                                                          frontier);
            int in_explored = explored.count(child->ToString());
            if (!in_frontier.first && !in_explored) {
                frontier.push_back(std::move(child));
            } else if (in_frontier.first) {
                int i = in_frontier.second;
                if (frontier.at(i)->GetTotalCost() > child->GetTotalCost()) {
                    frontier.at(i) = child;
                }
            }
        }
        num_nodes_expanded++;
        first_run = false;
    }
    // Failed if we reach here
    return nullptr;
}

std::pair<bool, int> Solver::StateFound(
        const Node* node,
        const std::vector<std::shared_ptr<Node>>& frontier) const {
    std::pair<bool, int> result;
    for (int i = 0; i < frontier.size(); i++) {
        if (node->GetState() == frontier.at(i)->GetState()) {
            result.first = true;
            result.second = i;
            return result;
        }
    }
    result.first = false;
    result.second = -1;
    return result;
}

std::pair<int, int> Solver::FindExpectedLocation(int target,
                                                 int state_size) const {
    if (target == 0) {
        return std::make_pair(state_size - 1, state_size - 1);
    }

    int row_loc;
    int column_loc = target % state_size;
    // When column_loc == 0 that means we have a number on the right edge
    // of the puzzle (not including 0). Example: 3 is on the top right of an
    // 8 Puzzle and 3 mod 3 == 0. We subtract 1 to (target / state_size),
    // because 3 / 3 = 1 which is not the row location for a 3.
    if (column_loc == 0) {
        column_loc = state_size - 1;
        row_loc = (target / state_size) - 1;
    } else {
        column_loc -= 1;
        row_loc = target / state_size;
    }
    return std::make_pair(row_loc, column_loc);
}

int Solver::MisplacedTile(const std::vector<std::vector<int>>& state) const {
    int expected = 1;
    int num_misplaced = 0;
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.at(i).size(); j++) {
            // We don't account for the blank tile position
            if (!(i == state.size() - 1 && j == state.at(i).size() - 1)) {
                if (state.at(i).at(j) != expected++) {
                    num_misplaced++;
                }
            }
        }
    }
    return num_misplaced;
}

double Solver::EuclidianDistance(
        const std::vector<std::vector<int>>& state) const {
    int size = state.size();
    std::pair<int, int> correct_loc;
    double total = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (state.at(i).at(j) == 0) { continue; }
            correct_loc = FindExpectedLocation(state.at(i).at(j), size);
            int row_dist = correct_loc.first - i;
            int col_dist = correct_loc.second - j;
            total += std::sqrt(std::pow(row_dist, 2) + std::pow(col_dist, 2));
        }
    }
    return total;
}