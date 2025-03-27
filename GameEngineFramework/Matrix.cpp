#include "Matrix.h"
#include "StandardIncludes.h"

Matrix::Matrix() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_values[i][j] = 0.0f;
        }
    }
}

Matrix::Matrix(float _values[16]) {
    int inputIndex = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_values[i][j] = _values[inputIndex];
            inputIndex++;
        }
    }
}

void Matrix::SetValues(float _values[16]) {
    int inputIndex = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_values[i][j] = _values[inputIndex];
            inputIndex++;
        }
    }
}

void Matrix::ToString() {
    string output = "mat4x4(";
    for (int i = 0; i < 4; ++i) {
        output += "(";
        for (int j = 0; j < 4; ++j) {
            output += to_string(m_values[i][j]);
            if (j != 3) {
                output += ", ";
            }
        }
        output += ")";
        if (i != 3) {
            output += ", ";
        }
    }
    output += ")";
    cout << output << endl;
}

Matrix Matrix::operator+(Matrix& other) {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m_values[i][j] = m_values[i][j] + other.m_values[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix& other) {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m_values[i][j] = m_values[i][j] - other.m_values[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(Matrix& other) {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m_values[i][j] = ((other.m_values[i][0]) * (m_values[0][j])) + ((other.m_values[i][1]) * (m_values[1][j])) + ((other.m_values[i][2]) * (m_values[2][j]) + ((other.m_values[i][3]) * (m_values[3][j])));
        }
    }
    return result;
}