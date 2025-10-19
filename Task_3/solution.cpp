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

void buildBinaryMatrix(double** A, int** B, int N) {
    for (int i = 0; i < N; ++i) {
        double diag = A[i][i];
        for (int j = 0; j < N; ++j) {
            B[i][j] = (A[i][j] > diag) ? 1 : 0;
        }
    }
}

void printMatrices(double** A, int** B, int N) {
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
}

void runInteractiveMode() {
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

    buildBinaryMatrix(A, B, N);
    printMatrices(A, B, N);

    freeMatrix(A, N);
    freeMatrix(B, N);
}

void runTests() {
    cout << "\n=== ������ ���������� ������ ===\n";

    {
        const int N = 2;
        double** A = new double* [N];
        int** B = new int* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
            B[i] = new int[N];
        }

        A[0][0] = 1.0; A[0][1] = 3.0;
        A[1][0] = 2.0; A[1][1] = 2.5;

        buildBinaryMatrix(A, B, N);

        int expected[2][2] = { {0, 1}, {0, 0} };
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (B[i][j] != expected[i][j]) {
                    ok = false;
                }
            }
        }

        cout << (ok ? "���� 1 (2x2): OK\n" : "���� 1: FAIL\n");

        freeMatrix(A, N);
        freeMatrix(B, N);
    }

    {
        const int N = 3;
        double** A = new double* [N];
        int** B = new int* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
            B[i] = new int[N];
        }

        A[0][0] = 5.0; A[0][1] = 2.0; A[0][2] = 1.0;
        A[1][0] = 3.0; A[1][1] = 6.0; A[1][2] = 4.0;
        A[2][0] = 0.0; A[2][1] = -1.0; A[2][2] = 10.0;

        buildBinaryMatrix(A, B, N);

        bool ok = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (B[i][j] != 0) {
                    ok = false;
                }
            }
        }

        cout << (ok ? "���� 2 (��������� � ��������): OK\n" : "���� 2: FAIL\n");

        freeMatrix(A, N);
        freeMatrix(B, N);
    }

    {
        const int N = 2;
        double** A = new double* [N];
        int** B = new int* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
            B[i] = new int[N];
            for (int j = 0; j < N; ++j) {
                A[i][j] = 7.7;
            }
        }

        buildBinaryMatrix(A, B, N);

        bool ok = (B[0][0] == 0 && B[0][1] == 0 && B[1][0] == 0 && B[1][1] == 0);
        cout << (ok ? "���� 3 (��� ����������): OK\n" : "���� 3: FAIL\n");

        freeMatrix(A, N);
        freeMatrix(B, N);
    }

    {
        const int N = 2;
        double** A = new double* [N];
        int** B = new int* [N];
        for (int i = 0; i < N; ++i) {
            A[i] = new double[N];
            B[i] = new int[N];
        }

        A[0][0] = -5.0; A[0][1] = -3.0;  
        A[1][0] = -10.0; A[1][1] = -7.0;

        buildBinaryMatrix(A, B, N);

        bool ok = (B[0][0] == 0 && B[0][1] == 1 && B[1][0] == 0 && B[1][1] == 0);
        cout << (ok ? "���� 4 (�������������): OK\n" : "���� 4: FAIL\n");

        freeMatrix(A, N);
        freeMatrix(B, N);
    }

    cout << "\n--- ������������ ��������� ---\n\n";
}

void showMenu() {
    cout << "\n=== ���� ===\n";
    cout << "1. ������ ������� � ��������� �������� �������\n";
    cout << "2. ��������� ���������\n";
    cout << "3. ��������� �����\n";
    cout << "�������� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\n������: ������� ����� ����� (1, 2 ��� 3).\n";
            continue;
        }

        switch (choice) {
        case 1:
            runInteractiveMode();
            break;
        case 2:
            cout << "��������� ���������.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\n�������� �����. ������� 1, 2 ��� 3.\n";
            break;
        }
    }

    return 0;
}