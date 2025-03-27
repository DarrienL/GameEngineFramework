#include "StandardIncludes.h"
#include "Matrix.h"

int main() {
	// Using custom matrix class
	cout << "\nCustom matrix class usage" << endl;

	// Input
	float matrixInput1[16] = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 };
	float matrixInput2[16] = { 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8 };

	Matrix matrix1(matrixInput1);
	Matrix matrix2(matrixInput2);

	Matrix matrixAdd = matrix1 + matrix2;
	cout << "\nMatrix addition: ";
	matrixAdd.ToString();

	Matrix matrixSubtract = matrix1 - matrix2;
	cout << "\nMatrix subtraction: ";
	matrixSubtract.ToString();

	Matrix matrixMultiply = matrix2 * matrix1;
	cout << "\nMatrix multiplication: ";
	matrixMultiply.ToString();

	// Using GLM matrices
	cout << "\nGLM matrix usage" << endl;

	// Input
	glm::mat4 matrix3 = { { 1, 1, 1, 1 }, { 2, 2, 2, 2 }, { 3, 3, 3, 3 }, { 4, 4, 4, 4 } };
	glm::mat4 matrix4 = { { 5, 5, 5, 5 }, { 6, 6, 6, 6 }, { 7, 7, 7, 7 }, { 8, 8, 8, 8 } };
	cout << "\nMatrix addition: " << glm::to_string(matrix3 + matrix4) << endl;
	cout << "\nMatrix substraction: " << glm::to_string(matrix3 - matrix4) << endl;
	cout << "\nMatrix multiplication: " << glm::to_string(matrix4 * matrix3) << endl;

	return 0;
}