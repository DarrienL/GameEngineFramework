#include "StandardIncludes.h"

int main() {
	// Translate
	cout << "\nTranslate" << endl;

	glm::mat4 matrix1 = glm::mat4(1.0f);
	glm::vec3 pos1 = { 0, 0, 0 };
	matrix1 = glm::translate(matrix1, pos1);
	cout << "Translation Matrix 1: " << glm::to_string(matrix1) << endl;

	glm::mat4 matrix2 = glm::mat4(1.0f);
	glm::vec3 pos2 = { 1, 2, 3 };
	matrix2 = glm::translate(matrix2, pos2);
	cout << "Translation Matrix 2: " << glm::to_string(matrix2) << endl;

	// Scale
	cout << "\nScale" << endl;

	matrix1 = glm::mat4(1.0f);
	glm::vec3 scale = { 2, 2, 2 };
	matrix1 = glm::scale(matrix1, scale);
	cout << "Scale Matrix: " << glm::to_string(matrix1) << endl;

	// Rotate
	cout << "\nRotate" << endl;
	matrix1 = glm::mat4(1.0f);
	float angle = 0.1f;
	glm::vec3 axis = { 0, 1, 0 };
	matrix1 = glm::rotate(matrix1, angle, axis);
	cout << "Rotation Matrix: " << glm::to_string(matrix1) << endl;

	return 0;
}