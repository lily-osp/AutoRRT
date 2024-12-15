// Simple Example: Straightforward usage with no obstacles.
#include <AutoRRT.h>

// Parameters for the RRT
float startX = 0;
float startY = 0;
float goalX = 10;
float goalY = 10;
float stepSize = 1.0;
float goalRadius = 1.0;

AutoRRT rrt(startX, startY, goalX, goalY, stepSize, goalRadius);

void setup() {
    Serial.begin(9600);

    // Set the bounds for the search space
    rrt.setBounds(0, 20, 0, 20);

    // Plan the path with 100 iterations
    if (rrt.planPath(100)) {
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
    // No continuous loop needed for this simple example.
}
