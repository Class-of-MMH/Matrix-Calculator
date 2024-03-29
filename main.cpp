#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


template<typename T>
void displayResult(const vector<vector<T>>& result) {
    cout << "Resultant Matrix:" << endl;
    for (const auto& row : result) {
        for (const T& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

   
    ofstream outputFile("previous_results.txt", ios::app);

    if (outputFile.is_open()) {
 
        for (const auto& row : result) {
            for (const T& val : row) {
                outputFile << val << " ";
            }
            outputFile << endl;
        }

        outputFile << "-------------------------" << endl;


        outputFile.close();
        cout << "Result saved to previous_results.txt." << endl;
    } else {
        cout << "Error opening the file for writing." << endl;
    }
}


void storeLUInFile(const vector<vector<int>>& L, const vector<vector<int>>& U) {
    ofstream luFile("lu_decomposition.txt");

    if (luFile.is_open()) {
        luFile << "Matrix L:" << endl;
        for (const auto& row : L) {
            for (int val : row) {
                luFile << val << " ";
            }
            luFile << endl;
        }

        luFile << "\nMatrix U:" << endl;
        for (const auto& row : U) {
            for (int val : row) {
                luFile << val << " ";
            }
            luFile << endl;
        }

        luFile.close();
        cout << "LU decomposition saved to lu_decomposition.txt." << endl;
    } else {
        cout << "Error opening the file for writing." << endl;
    }
}



vector<vector<int>> addMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (rows1 != rows2 || cols1 != cols2) {
        cout << "Invalid matrix addition: Matrices must have the same dimensions." << endl;
        return {};
    }

    vector<vector<int>> result(rows1, vector<int>(cols1, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

vector<vector<int>> subtractMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (rows1 != rows2 || cols1 != cols2) {
        cout << "Invalid matrix subtraction: Matrices must have the same dimensions." << endl;
        return {};
    }

    vector<vector<int>> result(rows1, vector<int>(cols1, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}


vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        cout << "Invalid matrix multiplication: Number of columns in matrix1 must be equal to the number of rows in matrix2." << endl;
        return {};
    }

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

vector<vector<double>> inverseMatrix(const vector<vector<int>>& mat) {
    int size = mat.size();
    vector<vector<double>> augmentedMatrix(size, vector<double>(2 * size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            augmentedMatrix[i][j] = mat[i][j];
            augmentedMatrix[i][j + size] = (i == j) ? 1 : 0;
        }
    }

    for (int i = 0; i < size; i++) {
        double pivot = augmentedMatrix[i][i];

        for (int j = 0; j < 2 * size; j++) {
            augmentedMatrix[i][j] /= pivot;
        }

        for (int k = 0; k < size; k++) {
            if (k != i) {
                double factor = augmentedMatrix[k][i];
                for (int j = 0; j < 2 * size; j++) {
                    augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                }
            }
        }
    }

    // extract the inverse matrix 
    vector<vector<double>> inverse(size, vector<double>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inverse[i][j] = augmentedMatrix[i][j + size];
        }
    }

    return inverse;
}
vector<vector<int>> minorMatrix(const vector<vector<int>>& mat, int row, int col) {
    int rows = mat.size();
    int cols = mat[0].size();

    vector<vector<int>> minor(rows - 1, vector<int>(cols - 1));

    for (int i = 0, r = 0; i < rows; ++i) {
        if (i == row) {
            continue; 
        }

        for (int j = 0, c = 0; j < cols; ++j) {
            if (j == col) {
                continue; 
            }

            minor[r][c++] = mat[i][j];
        }

        ++r;
    }

    return minor;
}

vector<vector<int>> transposeMatrix(const vector<vector<int>>& mat) {
    int rows = mat.size();
    int cols = (rows > 0) ? mat[0].size() : 0;

    if (rows == 0 || cols == 0) {
        cout << "Error: Cannot transpose an empty matrix." << endl;
        return {};
    }

    vector<vector<int>> transpose(cols, vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transpose[j][i] = mat[i][j];
        }
    }

    return transpose;
}

double determinantMatrix(const vector<vector<int>>& mat) {
    int size = mat.size();

    if (size == 1) {
        return mat[0][0];
    }

    double det = 0.0;

    for (int i = 0; i < size; i++) {
        vector<vector<int>> minor = minorMatrix(mat, 0, i);
        det += (i % 2 == 0 ? 1 : -1) * mat[0][i] * determinantMatrix(minor);
    }

    return det;
}
int findMatrixRank(vector<vector<int>>& matrix) {
    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    int rank = 0;
    for (int i = 0; i < rowCount; i++) {
        int pivotRow = i;
        while (pivotRow < rowCount && matrix[pivotRow][i] == 0) {
            pivotRow++;
        }

        if (pivotRow < rowCount) {
            swap(matrix[i], matrix[pivotRow]);

            for (int j = 0; j < rowCount; j++) {
                if (j != i) {
                    double ratio = matrix[j][i] / matrix[i][i];
                    for (int k = i; k < colCount; k++) {
                        matrix[j][k] -= ratio * matrix[i][k];
                    }
                }
            }

            rank++;
        }
    }

    return rank;
}

void luDecomposition(const vector<vector<int>>& A, vector<vector<int>>& L, vector<vector<int>>& U) {
    int n = A.size();

    L = vector<vector<int>>(n, vector<int>(n, 0));
    U = A;

    for (int k = 0; k < n; ++k) {
        L[k][k] = 1; 

        if (U[k][k] == 0) {
            cout << "LU decomposition is not possible (zero pivot)." << endl;
            return;
        }

        for (int i = k + 1; i < n; ++i) {
            int factor = U[i][k] / U[k][k];
            L[i][k] = factor;

            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }
}

int matrixTrace(const std::vector<std::vector<int>>& matrix) {

    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        if (matrix[i].size() != n) {
            throw std::invalid_argument("Input matrix must be square");
        }
    }

    int trace = 0;
    for (int i = 0; i < n; ++i) {
        trace += matrix[i][i];
    }

    return trace;
}
vector<vector<int>> multiplyMatrixByScalar(const vector<vector<int>>& matrix, int n) {

    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> result(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] * n;
        }
    }

    return result;
}

void displayresult(const vector<vector<int>>& result) {
    cout << "Resultant Matrix:" << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}



void displayPreviousResults() {
    ifstream inputFile("previous_results.txt");

    if (inputFile.is_open()) {
        string line;
        cout << "Previous Results:" << endl;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }

        inputFile.close();
    } else {
        cout << "Error opening the file for reading." << endl;
    }
}


int main()
{
        int choice;

    do {
        cout << "=======================\n";
        cout << "MATRIX OPERATIONS\n";
        cout << "=======================\n";
        cout << " [1] ADDITION\n";
        cout << " [2] SUBTRACTION\n";
        cout << " [3] MULTIPLICATION\n";
        cout << " [4] INVERSE\n";
        cout << " [5] TRANSPOSE\n";
        cout << " [6] DETERMINANT\n";
        cout << " [7] RANK\n";
        cout << " [8] LU DECOMPOSITION\n";
        cout << " [9] TRACE\n";
        cout << " [10] MULTIPLY MATRIX BY SCALAR\n";
       


        cout << "=======================\n";
        cin >> choice;


        int rows, cols;
        cout << "Enter the number of rows and columns for the matrices: ";
        cin >> rows >> cols;

        vector<vector<int>> matrix1(rows, vector<int>(cols));
        vector<vector<int>> matrix2(rows, vector<int>(cols));

        cout << "Enter the elements of Matrix 1:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix1[i][j];
            }
        }

        if (choice == 1 || choice == 2 || choice == 3) {
            int rows2, cols2;
            cout << "Enter the number of rows and columns for the second matrix: ";
            cin >> rows2 >> cols2;

            matrix2.resize(rows2, vector<int>(cols2));

            if ((choice == 1 || choice == 2) && (rows != rows2 || cols != cols2)) {
                cout << "Invalid matrix operation: Matrices must have the same dimensions." << endl;
                continue;
            }

            if (choice == 3 && cols != rows2) {
                cout << "Invalid matrix multiplication: Number of columns in matrix1 must be equal to the number of rows in matrix2." << endl;
                continue;
            }

            cout << "Enter the elements of Matrix 2:" << endl;
            for (int i = 0; i < rows2; i++) {
                for (int j = 0; j < cols2; j++) {
                    cin >> matrix2[i][j];
                }
            }
        }

             vector<vector<int>> result;
        double determinantResult;
        vector<vector<int>> L, U; 

                switch (choice) {



            case 1:
            result = addMatrices(matrix1, matrix2);
            break;
        case 2:
            result = subtractMatrices(matrix1, matrix2);
            break;
        case 3:
            result = multiplyMatrices(matrix1, matrix2);
            break;


          case 4:
    if (rows == cols) {
        vector<vector<double>> inverseResult = inverseMatrix(matrix1);

        cout << "Inverse Matrix:" << endl;
        displayResult(inverseResult);
    } else {
        cout << "Invalid choice! Please enter a square matrix for inversion." << endl;
        return 1;
    }
    break;


case 5:
{
    vector<vector<int>> transposeResult = transposeMatrix(matrix1);
    cout << "Transposed Matrix:" << endl;
    displayResult(transposeResult);
    break;
}


         case 6:

            if (rows == cols) {
                determinantResult = determinantMatrix(matrix1);
                cout << "Determinant: " << determinantResult << endl;
            } else {
                cout << "Invalid choice! Please enter a square matrix for determinant calculation." << endl;
                return 1;
            }
            break;
        case 7:
            cout<< "Rank is:"<<findMatrixRank(matrix1)<<endl;
            break;

    case 8:
        luDecomposition(matrix1, L, U);

        cout << "Matrix L:" << endl;
        displayResult(L);

        cout << "\nMatrix U:" << endl;
        displayResult(U);

 
        storeLUInFile(L, U);
        break;

            case 9:
             cout << "Trace: " << matrixTrace(matrix1) << endl;
            break;
    
case 10:
{
    int scalar;
    cout << "Enter the scalar for multiplication: ";
    cin >> scalar;

    vector<vector<int>> result = multiplyMatrixByScalar(matrix1, scalar);

    cout << "Matrix multiplied by " << scalar << ":\n";
    displayResult(result);
    break;
}



           
        default:
            cout << "Invalid choice! Please enter a number between 1 and 3." << endl;
            return 1;
    } 

          if (choice != 0) {
            displayResult(result);
        }

    } while (choice != 0);

    return 0;
}   
