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

static void SubtractVectors() {
	glm::vec2 a = { 3, 5 };
	glm::vec2 b = { 2, -1 };
	glm::vec2 c = b - a;
	glm::vec2 d = a - b;
	std::cout << glm::to_string(c) << "		Magnitude: " << glm::length(c) << std::endl;
	std::cout << glm::to_string(d) << "		Magnitude: " << glm::length(d) << std::endl;
}

static void MultiplyVectors() {
	glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 dest = { 1, 0, 0 };
	glm::vec3 dir = dest - pos;
	dir = glm::normalize(dir);
	pos += (dir * 0.1f);
	std::cout << glm::to_string(pos) << std::endl;
}

int main() {
	// Add Vectors
	std::cout << "\nAdd Vectors" << std::endl;
	AddVectors();

	// Subtract Vectors
	std::cout << "\nSubtract Vectors" << std::endl;
	SubtractVectors();

	// Multiply Vectors
	std::cout << "\nultiply Vectors" << std::endl;
	MultiplyVectors();

	return 0;
}