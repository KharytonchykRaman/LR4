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

void showMenu() {
    cout << "\n=== ���� ===\n";
    cout << "1. �������� ������� � ����� �������� � ��������\n";
    cout << "2. ��������� ���������\n";
    cout << "�������� �����: ";
}

void processMatrix() {
    const int M = 4;
    const int N = 5;

    int matrix[M][N] = {
        {10,  5,  8,  3, 12},
        { 7,  2,  9,  6,  1},
        {15,  4, 11,  2,  8},
        { 6,  9,  3,  7,  5}
    };

    cout << "\n�������:\n";
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(4);
            cout << matrix[i][j];
        }
        cout << "\n";
    }

    cout << "\n����������� �������� � ��������:\n";
    for (int j = 0; j < N; ++j) {
        int minVal = matrix[0][j];
        for (int i = 1; i < M; ++i) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        cout << "������� " << j << ": " << minVal << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\n������: ������� ����� ����� (1 ��� 2).\n";
            continue;
        }

        switch (choice) {
        case 1:
            processMatrix();
            break;
        case 2:
            cout << "��������� ���������.\n";
            return 0;
        default:
            cout << "\n�������� �����. ������� 1 ��� 2.\n";
            break;
        }
    }

    return 0;
}