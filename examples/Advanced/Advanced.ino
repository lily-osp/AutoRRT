// Advanced Example: Demonstrated dynamic obstacles in a larger search space.
#include <AutoRRT.h>

// Parameters for the RRT
float startX = 10;
float startY = 10;
float goalX = 90;
float goalY = 90;
float stepSize = 3.0;
float goalRadius = 3.0;

AutoRRT rrt(startX, startY, goalX, goalY, stepSize, goalRadius);

void setup() {
    Serial.begin(9600);

    // Set the bounds for the search space
    rrt.setBounds(0, 100, 0, 100);

    // Add static obstacles
    rrt.addObstacle(30, 30, 10);
    rrt.addObstacle(60, 60, 15);

    // Add dynamic obstacles (example: moving in a loop)
    for (int t = 0; t < 100; t++) {
        float dynamicX = 50 + 10 * cos(t * PI / 50);
        float dynamicY = 50 + 10 * sin(t * PI / 50);
        rrt.addObstacle(dynamicX, dynamicY, 5);

        // Attempt to plan the path with 1000 iterations
        if (rrt.planPath(1000)) {
            Serial.print("Path found at time ");
            Serial.print(t);
            Serial.println("!");
            for (const auto& point : rrt.getPath()) {
                Serial.print("Point: (");
                Serial.print(point.first);
                Serial.print(", ");
                Serial.print(point.second);
                Serial.println(")");
            }
            break; // Exit the loop when a path is found
        }
        rrt.addObstacle(dynamicX, dynamicY, 5); // Update dynamic obstacles
    }
}

void loop() {
    // This example terminates once a path is found or no path is possible.
}
