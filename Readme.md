### AutoRRT Library - README

---

#### **Introduction**
The `AutoRRT` library provides an easy-to-use implementation of the **Rapidly-Exploring Random Tree (RRT)** algorithm for path planning in robotics. This library is ideal for applications involving autonomous navigation, robotic arm motion planning, and obstacle avoidance. It supports configurable bounds, step sizes, and obstacles, making it adaptable for both simple and complex use cases.

---

#### **Features**
- Rapidly-Exploring Random Tree (RRT) algorithm.
- Support for goal proximity radius to mark successful pathfinding.
- Customizable bounds for the planning area.
- Collision avoidance with circular obstacles.
- Efficient distance calculation and path construction.
- Lightweight and optimized for Arduino boards.

---

#### **Installation**

1. Download the library as a ZIP file
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library
3. Select the downloaded ZIP file
4. Restart the Arduino IDE

---

#### **How to Use**
1. **Initialization**:
   Create an instance of `AutoRRT` by specifying:
   - Start coordinates (`startX`, `startY`).
   - Goal coordinates (`goalX`, `goalY`).
   - Step size for node generation (`stepSize`).
   - Goal radius to determine success (`goalRadius`).

2. **Set Bounds**:
   Define the boundaries of the search space using:
   ```cpp
   rrt.setBounds(minX, maxX, minY, maxY);
   ```

3. **Add Obstacles**:
   Specify circular obstacles using:
   ```cpp
   rrt.addObstacle(obstacleX, obstacleY, obstacleRadius);
   ```

4. **Plan Path**:
   Run the `planPath()` method with the maximum number of iterations:
   ```cpp
   bool success = rrt.planPath(maxIterations);
   ```

5. **Retrieve Path**:
   If a path is found, retrieve it as a vector of `(x, y)` points using:
   ```cpp
   std::vector<std::pair<float, float>> path = rrt.getPath();
   ```

---

#### **API Reference**
Below is a summary of the key methods and their functionality:

| **Method**                | **Description**                                                                                                                                      |
|---------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|
| `AutoRRT(...)`            | Constructor to initialize the RRT instance with start/goal coordinates, step size, and goal radius.                                                |
| `setBounds(...)`          | Sets the boundaries of the search space.                                                                                                           |
| `addObstacle(...)`        | Adds a circular obstacle to the environment.                                                                                                      |
| `planPath(...)`           | Attempts to plan a path to the goal within the specified maximum number of iterations. Returns `true` if successful, otherwise `false`.            |
| `getPath()`               | Returns the path as a vector of `(x, y)` pairs from the start to the goal.                                                                         |
| `isGoalReached(...)`      | Checks whether a node is within the goal radius.                                                                                                  |
| `isCollisionFree(...)`    | Determines if a path between two nodes is free of collisions.                                                                                     |
| `calculateDistance(...)`  | Computes the Euclidean distance between two points.                                                                                               |

---

#### **Example Applications**
- **Simple Pathfinding**: Navigate from one point to another in an empty space.
- **Obstacle Avoidance**: Plan a path that avoids collisions with static or dynamic obstacles.
- **Large Search Spaces**: Use the library to explore expansive environments efficiently.

---

#### **Library Limitations**
- Currently supports 2D environments only.
- Obstacle shapes are limited to circles.
- Performance may vary depending on the number of obstacles and the size of the search space.

---

#### **Future Enhancements**
- Support for RRT* (optimized RRT).
- Path smoothing for more natural movements.
- 3D environment support.

---

#### **Contributing**
Contributions are welcome! To contribute:
1. Fork the repository.
2. Make changes and test thoroughly.
3. Submit a pull request with a clear description of your changes.

---

#### **License**
This library is open-source and available under the MIT License. Feel free to use, modify, and distribute it.

---

If you have any questions or encounter issues, feel free to reach out or open an issue in the repository.
