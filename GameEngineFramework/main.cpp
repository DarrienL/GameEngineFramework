#include "StandardIncludes.h"

static glm::vec3 pos = { 2, 2, 2 };
static void MultiplyVectors() {
	glm::vec3 dest = { 1, 0, 0 };
	glm::vec3 dir = dest - pos;
	dir = glm::normalize(dir);
	pos += (dir * 0.1f);
	std::cout << glm::to_string(pos) << std::endl;
}

int main() {
	for (int count = 0; count < 10; count++) {
		MultiplyVectors();
	}
	return 0;
}