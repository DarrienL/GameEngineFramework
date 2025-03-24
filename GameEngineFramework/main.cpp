#include "StandardIncludes.h"

static void AddVectors() {
	glm::vec2 a = { 3, 5 };
	glm::vec2 b = { 2, -1 };
	glm::vec2 c = a + b;
	std::cout << glm::to_string(c) << std::endl;

	glm::vec3 d = { 3, 5, 1 };
	glm::vec3 e = { 2, -1, -1 };
	glm::vec3 f = d + e;
	std::cout << glm::to_string(f) << std::endl;
}

int main() {
	AddVectors();
	return 0;
}