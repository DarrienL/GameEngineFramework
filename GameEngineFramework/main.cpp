#include "StandardIncludes.h"

static void Distance() {
	glm::vec3 p1 = { 1, 1, 0 };
	glm::vec3 p2 = { 2, 1, 2 };
	float distance = glm::distance(p1, p2);
	std::cout << "Distance = " << distance << std::endl;
}

int main() {
	Distance();
	return 0;
}