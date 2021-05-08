#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

class Node {
 public:
    Node() {
        parent = nullptr;
        g = 0;
        h = 0;
        f = 0;
    }
    Node(Node* parent, int g, std::vector<std::vector<int>> puzzle) {
        this->parent = parent;
        this->g = g;
        this->puzzle = puzzle;
        h = 0;
        f = 0;
    }

    Node* getParent();
    std::vector<Node*> getChildren();
    std::vector<std::vector<int>> getPuzzle();
    int getG();
    int getH();
    int getF();
    void setH(int h);
    void setF(int f);

    friend bool operator==(const Node& lhs, const Node& rhs);    

 private:
    Node* parent;
    std::vector<Node*> children;
    std::vector<std::vector<int>> puzzle;
    int g; // Distance from parent root node
    int h; // Estimated distance to goal
    int f; // Heuristic function f = g + h 
};

#endif // NODE_HPP