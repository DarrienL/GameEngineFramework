#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
	Matrix();
	Matrix(float _values[16]);
	virtual ~Matrix() {};

	void SetValues(float _values[16]);
	void ToString();
	Matrix operator+(Matrix& other);
	Matrix operator-(Matrix& other);
	Matrix operator*(Matrix& other);

private:
	float m_values[4][4];
};

#endif

