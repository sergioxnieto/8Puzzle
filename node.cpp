#include "node.hpp"

Node* Node::getParent() {
    return parent;
}

std::vector<Node*> Node::getChildren() {
    return children;
}

std::vector<std::vector<int>> Node::getPuzzle() {
    return puzzle;
}

int Node::getG() {
    return g;
}

int Node::getH() {
    return h;
}

void Node::setH(int h) {
    this->h = h;
}

int Node::getF() {
    return f;
}

void Node::setF(int f) {
    this->f = f;
}

// Friend of Node class
bool operator==(const Node& lhs, const Node& rhs) {
    return (lhs.puzzle == rhs.puzzle);
}
