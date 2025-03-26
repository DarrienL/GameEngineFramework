#include "StandardIncludes.h"

int main() {
	// Declare and initialize identity matrix
	glm::mat4 matrix1 = glm::mat3(1.0f);
	cout << "\nIdentity Matrix Initialization" << endl;
	cout << glm::to_string(matrix1) << endl;

	// Matrix addition
	glm::mat4 matrix2 = { { 1, 1, 1, 1 }, { 2, 2, 2, 2 }, { 3, 3, 3, 3 }, { 4, 4, 4, 4 } };
	glm::mat4 matrix3 = { { 5, 5, 5, 5 }, { 6, 6, 6, 6 }, { 7, 7, 7, 7 }, { 8, 8, 8, 8 } };
	cout << "\nMatrix addition" << endl;
	cout << "Matrix1: " << glm::to_string(matrix2) << endl;
	cout << "Matrix2: " << glm::to_string(matrix3) << endl;
	cout << "Add M1 to M2: " << glm::to_string(matrix2 + matrix3) << endl;

	// Matrix subtraction
	cout << "\nMatrix subtraction" << endl;
	cout << "Matrix1: " << glm::to_string(matrix2) << endl;
	cout << "Matrix2: " << glm::to_string(matrix3) << endl;
	cout << "Subtract M2 from M1: " << glm::to_string(matrix2 - matrix3) << endl;

	// Matrix multiplication 1
	cout << "\nMatrix multiplication 1" << endl;
	cout << "Matrix1: " << glm::to_string(matrix2) << endl;
	cout << "Matrix2: " << glm::to_string(matrix3) << endl;
	cout << "Multiply M1 and M2: " << glm::to_string(matrix2 * matrix3) << endl;

	// Matrix multiplication 2
	cout << "\nMatrix multiplication 2" << endl;
	cout << "Matrix1: " << glm::to_string(matrix2) << endl;
	cout << "Matrix2: " << glm::to_string(matrix3) << endl;
	cout << "Multiply M2 and M1: " << glm::to_string(matrix3 * matrix2) << endl;

	// Matrix multiplication commutative example
	cout << "\nMatrix multiplication commutative example" << endl;
	cout << "Matrix1: " << glm::to_string(matrix1) << endl;
	cout << "Matrix2: " << glm::to_string(matrix3) << endl;
	cout << "Multiply M1 and M2: " << glm::to_string(matrix1 * matrix3) << endl;
	cout << "Multiply M2 and M1: " << glm::to_string(matrix3 * matrix1) << endl;

	return 0;
}