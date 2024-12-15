// Intermediate Example: Introduced obstacles to showcase collision avoidance.
#include <AutoRRT.h>

// Parameters for the RRT
float startX = 5;
float startY = 5;
float goalX = 50;
float goalY = 50;
float stepSize = 2.0;
float goalRadius = 2.0;

AutoRRT rrt(startX, startY, goalX, goalY, stepSize, goalRadius);

void setup() {
    Serial.begin(9600);

    // Set the bounds for the search space
    rrt.setBounds(0, 60, 0, 60);

    // Add circular obstacles
    rrt.addObstacle(20, 20, 5);
    rrt.addObstacle(30, 40, 8);
    rrt.addObstacle(40, 10, 6);

    // Plan the path with 500 iterations
    if (rrt.planPath(500)) {
        Serial.println("Path found!");
        for (const auto& point : rrt.getPath()) {
            Serial.print("Point: (");
            Serial.print(point.first);
            Serial.print(", ");
            Serial.print(point.second);
            Serial.println(")");
        }
    } else {
        Serial.println("No path found.");
    }
}

void loop() {
    // No continuous loop needed for this intermediate example.
}
