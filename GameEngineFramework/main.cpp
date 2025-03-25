#include "StandardIncludes.h"

int task1(glm::vec3 pos, glm::vec3 dest, float speed) {
	glm::vec3 dir = dest - pos;
	dir = glm::normalize(dir);
	int steps = 0;
	while (glm::distance(pos, dest) > speed) {
		pos += (dir * speed);
		steps++;
	}
	// While distance between current position and destination is greater than the speed of a step
	// move a step and increment int steps
	return steps;
}

int main() {
	// Input
	glm::vec3 a = { 3, 0, 8 };
	glm::vec3 b = { 9, 2, 1 };
	float s = 0.2f;
	cout << "It would take " << to_string(task1(a, b, s)) << " steps to reach the destination." << endl;

	return 0;
}