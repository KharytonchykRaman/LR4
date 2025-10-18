#include <iostream>
#include <clocale>
#include <limits>

using namespace std;

bool safeInputInt(int& value) {
    if (cin >> value) {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

bool safeInputDouble(double& value) {
    if (cin >> value) {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    cout << "Введите порядок квадратной матрицы N (N > 0): ";
    while (true) {
        if (!safeInputInt(N)) {
            cout << "Ошибка: введите целое число. Попробуйте снова: ";
        }
        else if (N <= 0) {
            cout << "Ошибка: N должно быть положительным. Попробуйте снова: ";
        }
        else {
            break;
        }
    }

    double** A = new double* [N];
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
    }

    cout << "Введите элементы вещественной матрицы " << N << "x" << N << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "A[" << i << "][" << j << "] = ";
            while (!safeInputDouble(A[i][j])) {
                cout << "Ошибка: введите вещественное число. Повторите ввод для A[" << i << "][" << j << "]: ";
            }
        }
    }

    int** B = new int* [N];
    for (int i = 0; i < N; ++i) {
        B[i] = new int[N];
    }

    for (int i = 0; i < N; ++i) {
        double diag = A[i][i]; 
        for (int j = 0; j < N; ++j) {
            if (A[i][j] > diag) {
                B[i][j] = 1;
            }
            else {
                B[i][j] = 0;
            }
        }
    }

    cout << "\nИсходная вещественная матрица:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(8);
            cout.precision(2);
            cout << fixed << A[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nЦелочисленная матрица (1 если A[i][j] > A[i][i], иначе 0):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(3);
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }

    freeMatrix(A, N);
    freeMatrix(B, N);

    return 0;
}