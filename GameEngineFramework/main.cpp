#include "StandardIncludes.h"

static void DotProduct() {
	glm::vec3 source = { 0, 0, 0 };
	glm::vec3 a = { 0, 2, 0 };
	glm::vec3 b = { 1, 1, 0 };
	glm::vec3 aVec = a - source;
	glm::vec3 bVec = b - source;
	aVec = glm::normalize(aVec);
	bVec = glm::normalize(bVec);
	float dot = glm::dot(aVec, bVec);
	std::cout << "Dot = " << dot << std::endl;
}

static void CrossProduct() {
	glm::vec3 source = { 0, 0, 0 };
	glm::vec3 a = { 0, 2, 0 };
	glm::vec3 b = { 1, 1, 0 };
	glm::vec3 aVec = a - source;
	glm::vec3 bVec = b - source;
	glm::vec3 cross = glm::cross(aVec, bVec);
	cross = glm::normalize(cross);
	std::cout << "Cross = " << glm::to_string(cross) << std::endl;
}

int main() {
	DotProduct();
	CrossProduct();
	return 0;
}