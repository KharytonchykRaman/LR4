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
    cout << "������� ������� ���������� ������� N (N > 0): ";
    while (true) {
        if (!safeInputInt(N)) {
            cout << "������: ������� ����� �����. ���������� �����: ";
        }
        else if (N <= 0) {
            cout << "������: N ������ ���� �������������. ���������� �����: ";
        }
        else {
            break;
        }
    }

    double** A = new double* [N];
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
    }

    cout << "������� �������� ������������ ������� " << N << "x" << N << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "A[" << i << "][" << j << "] = ";
            while (!safeInputDouble(A[i][j])) {
                cout << "������: ������� ������������ �����. ��������� ���� ��� A[" << i << "][" << j << "]: ";
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

    cout << "\n�������� ������������ �������:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(8);
            cout.precision(2);
            cout << fixed << A[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n������������� ������� (1 ���� A[i][j] > A[i][i], ����� 0):\n";
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