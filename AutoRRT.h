#ifndef AUTORRT_H
#define AUTORRT_H

#include <Arduino.h>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>

class AutoRRT {
public:
    struct Node {
        float x, y;
        Node* parent;
        Node(float x, float y, Node* parent = nullptr) : x(x), y(y), parent(parent) {}
    };

    AutoRRT(float startX, float startY, float goalX, float goalY, float stepSize, float goalRadius);

    void setBounds(float minX, float maxX, float minY, float maxY);
    void addObstacle(float x, float y, float radius);
    bool planPath(size_t maxIterations);
    std::vector<std::pair<float, float>> getPath() const;

private:
    Node* getRandomNode();
    Node* getNearestNode(Node* randomNode);
    bool isCollisionFree(const Node* fromNode, const Node* toNode) const;
    bool isGoalReached(const Node* node) const;

    float calculateDistance(float x1, float y1, float x2, float y2) const;
    Node* createNode(float x, float y, Node* parent = nullptr);

    void cleanupNodes();

    float startX, startY, goalX, goalY, stepSize, goalRadius;
    float minX, maxX, minY, maxY;

    std::vector<Node*> nodes;
    std::vector<std::pair<float, float>> obstacles;
    std::vector<std::pair<float, float>> path;
};

#endif
