#include "AutoRRT.h"

AutoRRT::AutoRRT(float startX, float startY, float goalX, float goalY, float stepSize, float goalRadius)
    : startX(startX), startY(startY), goalX(goalX), goalY(goalY), stepSize(stepSize), goalRadius(goalRadius),
      minX(0), maxX(100), minY(0), maxY(100) {
    nodes.push_back(createNode(startX, startY));
}

void AutoRRT::setBounds(float minX, float maxX, float minY, float maxY) {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
}

void AutoRRT::addObstacle(float x, float y, float radius) {
    obstacles.emplace_back(x, y);
}

bool AutoRRT::planPath(size_t maxIterations) {
    for (size_t i = 0; i < maxIterations; ++i) {
        Node* randomNode = getRandomNode();
        Node* nearestNode = getNearestNode(randomNode);

        float dx = randomNode->x - nearestNode->x;
        float dy = randomNode->y - nearestNode->y;
        float dist = calculateDistance(nearestNode->x, nearestNode->y, randomNode->x, randomNode->y);

        if (dist > stepSize) {
            dx = (dx / dist) * stepSize;
            dy = (dy / dist) * stepSize;
        }

        Node* newNode = createNode(nearestNode->x + dx, nearestNode->y + dy, nearestNode);

        if (isCollisionFree(nearestNode, newNode)) {
            nodes.push_back(newNode);

            if (isGoalReached(newNode)) {
                Node* current = newNode;
                path.clear();
                while (current) {
                    path.emplace_back(current->x, current->y);
                    current = current->parent;
                }
                cleanupNodes();
                return true;
            }
        }
        delete randomNode;
    }
    cleanupNodes();
    return false;
}

std::vector<std::pair<float, float>> AutoRRT::getPath() const {
    return path;
}

AutoRRT::Node* AutoRRT::getRandomNode() {
    float x = random(minX * 1000, maxX * 1000) / 1000.0f;
    float y = random(minY * 1000, maxY * 1000) / 1000.0f;
    return createNode(x, y);
}

AutoRRT::Node* AutoRRT::getNearestNode(Node* randomNode) {
    Node* nearest = nullptr;
    float minDist = std::numeric_limits<float>::infinity();

    for (Node* node : nodes) {
        float dist = calculateDistance(node->x, node->y, randomNode->x, randomNode->y);
        if (dist < minDist) {
            minDist = dist;
            nearest = node;
        }
    }
    return nearest;
}

bool AutoRRT::isCollisionFree(const Node* fromNode, const Node* toNode) const {
    for (const auto& obstacle : obstacles) {
        float ox = obstacle.first;
        float oy = obstacle.second;

        float dx = toNode->x - fromNode->x;
        float dy = toNode->y - fromNode->y;
        float a = dx * dx + dy * dy;
        float b = 2 * (dx * (fromNode->x - ox) + dy * (fromNode->y - oy));
        float c = ox * ox + oy * oy + fromNode->x * fromNode->x + fromNode->y * fromNode->y -
                  2 * (ox * fromNode->x + oy * fromNode->y) - stepSize * stepSize;

        if (b * b - 4 * a * c >= 0) {
            return false;
        }
    }
    return true;
}

bool AutoRRT::isGoalReached(const Node* node) const {
    return calculateDistance(node->x, node->y, goalX, goalY) <= goalRadius;
}

float AutoRRT::calculateDistance(float x1, float y1, float x2, float y2) const {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

AutoRRT::Node* AutoRRT::createNode(float x, float y, Node* parent) {
    return new Node(x, y, parent);
}

void AutoRRT::cleanupNodes() {
    for (Node* node : nodes) {
        delete node;
    }
    nodes.clear();
}
