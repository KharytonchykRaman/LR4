#include <iostream>
#include <clocale>
#include <limits>
#include <string>

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

    int magicSum = n * (n * n + 1) / 2;
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

void showMenu() {
    cout << "=== ���� ===\n";
    cout << "1. ��������� ���������� �������\n";
    cout << "2. ��������� ���������\n";
    cout << "��� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!safeInputInt(choice)) {
            cout << "\n������: ������� 1 ��� 2.\n\n";
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
        default:
            cout << "\n�������� �����. ������� 1 ��� 2.\n\n";
        }
    }

    return 0;
}