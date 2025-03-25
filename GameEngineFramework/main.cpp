#include "StandardIncludes.h"

float task2Perimeter(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	// Calculate perimeter
	float ab = glm::distance(a, b);
	float bc = glm::distance(b, c);
	float ca = glm::distance(c, a);
	return ab + bc + ca; // Perimeter = sum of all 3 sides (distances between points)
}

float task2Area(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	// Calculate area
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 cross = glm::cross(ab, ac);
	return 0.5f * glm::length(cross); // Area = 0.5 * magnitude of cross product of 2 sides
}

int main() {
	// Input
	glm::vec3 a = { 0, 0, 0 };
	glm::vec3 b = { 2, 0, 0 };
	glm::vec3 c = { 0, 2, 0 };
	cout << "The perimeter of the traingle is " << to_string(task2Perimeter(a, b, c)) << endl;
	cout << "The area of the traingle is " << to_string(task2Area(a, b, c)) << endl;
	return 0;
}