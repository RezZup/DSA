

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
typedef vector<vector<int>> Matrix;

void validateMultiplicationInput(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty()) {
        throw invalid_argument("Matrices must not be empty");
    }

    const size_t n = A.size();
    if (B.size() != n) {
        throw invalid_argument("Matrices must have the same dimensions");
    }

    for (const auto& row : A) {
        if (row.size() != n) {
            throw invalid_argument("Matrices must be square");
        }
    }
    for (const auto& row : B) {
        if (row.size() != n) {
            throw invalid_argument("Matrices must be square");
        }
    }
}

// Native matrix multiplication
Matrix nativeMultiply(const Matrix& A, const Matrix& B) {
    validateMultiplicationInput(A, B);
    const int n = static_cast<int>(A.size());
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Add two matrices
Matrix add(const Matrix& A, const Matrix& B) {
    const int n = static_cast<int>(A.size());
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Subtract two matrices
Matrix subtract(const Matrix& A, const Matrix& B) {
    const int n = static_cast<int>(A.size());
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Strassen's recursive matrix multiplication for power-of-two matrix sizes.
Matrix strassenRecursive(const Matrix& A, const Matrix& B) {
    const int n = static_cast<int>(A.size());

    // Base case: 1x1 matrix, direct multiplication
    if (n == 1) {
        return { { A[0][0] * B[0][0] } };
    }

    int half = n / 2;
    Matrix A11(half, vector<int>(half)), A12(half, vector<int>(half)),
           A21(half, vector<int>(half)), A22(half, vector<int>(half)),
           B11(half, vector<int>(half)), B12(half, vector<int>(half)),
           B21(half, vector<int>(half)), B22(half, vector<int>(half));

    // Divide A and B into quadrants
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Compute the 7 products recursively
    Matrix M1 = strassenRecursive(add(A11, A22), add(B11, B22));
    Matrix M2 = strassenRecursive(add(A21, A22), B11);
    Matrix M3 = strassenRecursive(A11, subtract(B12, B22));
    Matrix M4 = strassenRecursive(A22, subtract(B21, B11));
    Matrix M5 = strassenRecursive(add(A11, A12), B22);
    Matrix M6 = strassenRecursive(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassenRecursive(subtract(A12, A22), add(B21, B22));

    // Combine into result quadrants
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    // Combine quadrants into result matrix
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    validateMultiplicationInput(A, B);

    const int n = static_cast<int>(A.size());
    int paddedSize = 1;
    while (paddedSize < n) {
        paddedSize *= 2;
    }

    Matrix paddedA(paddedSize, vector<int>(paddedSize));
    Matrix paddedB(paddedSize, vector<int>(paddedSize));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            paddedA[i][j] = A[i][j];
            paddedB[i][j] = B[i][j];
        }
    }

    Matrix paddedResult = strassenRecursive(paddedA, paddedB);
    Matrix result(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = paddedResult[i][j];
        }
    }
    return result;
}

void printMatrix(const Matrix& M) {
    for (auto& row : M) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
}

int main() {
    Matrix A = { {1, 2}, {3, 4} };
    Matrix B = { {5, 6}, {7, 8} };

    Matrix C = strassenMultiply(A, B);
    Matrix D = nativeMultiply(A, B);

    cout << "Result of Strassen's Multiplication:" << endl;
    printMatrix(C);

    cout << "Result of Native Multiplication:" << endl;
    printMatrix(D);

    return 0;
}