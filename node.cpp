#include "node.hpp"

Node::Node(const Problem& puzzle) {
    state_ = puzzle.GetStartPuzzle();
    path_cost_ = 0;
    heuristic_ = 0;
    total_cost_ = path_cost_ + heuristic_;
}

Node::Node(const Problem& puzzle, std::shared_ptr<Node> parent,
           const std::string& action) {
    state_ = puzzle.ToState(parent->state_, action);
    parent_ = parent;
    action_ = action;
    path_cost_ = parent->path_cost_ + puzzle.ActionCost(parent->state_, action);
    heuristic_ = 0;
    total_cost_ = path_cost_ + heuristic_;
}

std::shared_ptr<Node> Node::GetParent() const{
    return parent_;
}

std::vector<std::vector<int>> Node::GetState() const{
    return state_;
}

int Node::GetPathCost() const{
    return path_cost_;
}

double Node::GetDistanceToGoal() const{
    return heuristic_;
}

double Node::GetTotalCost() const{
    return total_cost_;
}

void Node::ApplyHeuristic(double heuristic) {
    heuristic_ = heuristic;
    total_cost_ = path_cost_ + heuristic_;
}

std::string Node::ToString() const {
    std::string str = "";
    for (int i = 0; i < state_.size(); i++) {
        for (int j = 0; j < state_.at(i).size(); j++) {
            str.append(std::to_string(state_.at(i).at(j)));
        }
    }
    return str;
}

bool operator>(const Node& lhs, const Node& rhs) {
    return lhs.total_cost_ > rhs.total_cost_;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "\n============================" << std::endl;
    os << "Node Details" << std::endl;
    os << "Puzzle State: " << std::endl;
    for (int i = 0; i < node.state_.size(); i++) {
        os << "[ ";
        for (int j = 0; j < node.state_.at(i).size(); j++) {
            os << node.state_.at(i).at(j) << " ";
        }
        os << "]" << std::endl;
    }
    os << "Action to get here: " <<
        (node.action_ == "" ? "None (start)" : node.action_) << std::endl;
    os << "Path Cost: " << node.path_cost_ << std::endl;
    os << "Heuristic Estimate: " << node.heuristic_ << std::endl;
    os << "Total Cost: " << node.total_cost_ << std::endl;
    os << "============================";
    return os;
}