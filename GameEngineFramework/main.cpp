#include "StandardIncludes.h"

vector<glm::vec3> task3(glm::vec3 a, glm::vec3 b, glm::vec3 c, float depth) {
	// Finding 4th point to complete parallelogram
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 d = a + b + c;

	// Extrusion vector (perpendicular to the parallelogram)
	glm::vec3 depthVec = glm::cross(ab, ac);
	depthVec = glm::normalize(depthVec);

	// Finding remaining vertices
	glm::vec3 e = a + (depthVec * depth);
	glm::vec3 f = b + (depthVec * depth);
	glm::vec3 g = c + (depthVec * depth);
	glm::vec3 h = d + (depthVec * depth);

	return { a, b, c, d, e, f, g, h };
}


int main() {
	// Input
	glm::vec3 a = { 0, 0, 0 };
	glm::vec3 b = { 2, 0, 0 };
	glm::vec3 c = { 0, 2, 0 };
	float depth = 3.0f;

	vector<glm::vec3> vertices = task3(a, b, c, depth);

	cout << "Vertices of Cuboid:" << endl;
	for (glm::vec3 vertex : vertices) {
		cout << glm::to_string(vertex) << endl;
	}

	return 0;
}