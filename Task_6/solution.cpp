#include <iostream>
#include <clocale>
#include <limits>
#include <string>
#include <cstring>

using namespace std;

const int MAX_N = 10;

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

void buildMagicSquare(int square[][MAX_N], int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            square[i][j] = 0;

    int row = 0;
    int col = n / 2;

    for (int num = 1; num <= n * n; ++num) {
        square[row][col] = num;

        int nextRow = (row - 1 + n) % n;
        int nextCol = (col + 1) % n;

        if (square[nextRow][nextCol] != 0) {
            nextRow = (row + 1) % n;
            nextCol = col;
        }

        row = nextRow;
        col = nextCol;
    }
}

bool isMagicSquare(int square[][MAX_N], int n) {
    if (n <= 0) return false;

    long long magicSum = (long long)n * (n * n + 1) / 2;

    for (int i = 0; i < n; ++i) {
        long long rowSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += square[i][j];
        }
        if (rowSum != magicSum) return false;
    }

    for (int j = 0; j < n; ++j) {
        long long colSum = 0;
        for (int i = 0; i < n; ++i) {
            colSum += square[i][j];
        }
        if (colSum != magicSum) return false;
    }

    long long diag1 = 0;
    for (int i = 0; i < n; ++i) diag1 += square[i][i];
    if (diag1 != magicSum) return false;

    long long diag2 = 0;
    for (int i = 0; i < n; ++i) diag2 += square[i][n - 1 - i];
    if (diag2 != magicSum) return false;

    bool seen[MAX_N * MAX_N + 1] = { false };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val = square[i][j];
            if (val < 1 || val > n * n || seen[val]) {
                return false;
            }
            seen[val] = true;
        }
    }

    return true;
}

void printSquare(int square[][MAX_N], int n) {
    cout << "\n���������� ������� ������� " << n << ":\n";
    int width = to_string(n * n).length() + 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout.width(width);
            cout << square[i][j];
        }
        cout << "\n";
    }

    long long magicSum = (long long)n * (n * n + 1) / 2;
    cout << "\n���������� �����: " << magicSum << "\n";
}

void runMagicSquare() {
    int n;
    cout << "������� ������� ����������� �������� (�������� ����� �� 1 �� 10): ";
    while (true) {
        if (!safeInputInt(n)) {
            cout << "������: ������� ����� �����. ���������� �����: ";
        }
        else if (n < 1 || n > 10) {
            cout << "������: n ������ ���� �� 1 �� 10. ���������� �����: ";
        }
        else if (n % 2 == 0) {
            cout << "������: ���������� ������� �������� ������ ��� �������� n (1,3,5,7,9). ���������� �����: ";
        }
        else {
            break;
        }
    }

    int square[MAX_N][MAX_N] = { 0 };
    buildMagicSquare(square, n);
    printSquare(square, n);
    cout << "\n";
}

void runTests() {
    cout << "\n=== ������ ���������� ������ ===\n";

    {
        const int n = 1;
        int square[MAX_N][MAX_N] = { 0 };
        buildMagicSquare(square, n);
        bool ok = isMagicSquare(square, n);
        cout << (ok ? "���� 1 (n=1): OK\n" : "���� 1: FAIL\n");
    }

    {
        const int n = 3;
        int square[MAX_N][MAX_N] = { 0 };
        buildMagicSquare(square, n);
        bool ok = isMagicSquare(square, n);
        cout << (ok ? "���� 2 (n=3): OK\n" : "���� 2: FAIL\n");

        if (ok && square[1][1] != 5) {
            cout << "����� �� ����� 5!\n";
        }
    }

    {
        const int n = 5;
        int square[MAX_N][MAX_N] = { 0 };
        buildMagicSquare(square, n);
        bool ok = isMagicSquare(square, n);
        cout << (ok ? "���� 3 (n=5): OK\n" : "���� 3: FAIL\n");
    }

    {
        const int n = 7;
        int square[MAX_N][MAX_N] = { 0 };
        buildMagicSquare(square, n);
        bool ok = isMagicSquare(square, n);
        cout << (ok ? "���� 4 (n=7): OK\n" : "���� 4: FAIL\n");
    }

    {
        const int n = 9;
        int square[MAX_N][MAX_N] = { 0 };
        buildMagicSquare(square, n);
        bool ok = isMagicSquare(square, n);
        cout << (ok ? "���� 5 (n=9): OK\n" : "���� 5: FAIL\n");
    }

    cout << "\n--- ������������ ��������� ---\n\n";
}

void showMenu() {
    cout << "\n=== ���� ===\n";
    cout << "1. ��������� ���������� �������\n";
    cout << "2. ��������� ���������\n";
    cout << "3. ��������� �����\n";
    cout << "��� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!safeInputInt(choice)) {
            cout << "\n������: ������� 1, 2 ��� 3.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            runMagicSquare();
            break;
        case 2:
            cout << "��������� ���������.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\n�������� �����. ������� 1, 2 ��� 3.\n\n";
        }
    }

    return 0;
}