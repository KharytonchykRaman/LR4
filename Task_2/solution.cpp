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
    cout << "\n=== Меню ===\n";
    cout << "1. Показать матрицу и найти минимумы в столбцах\n";
    cout << "2. Завершить программу\n";
    cout << "Выберите пункт: ";
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

    cout << "\nМатрица:\n";
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(4);
            cout << matrix[i][j];
        }
        cout << "\n";
    }

    cout << "\nМинимальные элементы в столбцах:\n";
    for (int j = 0; j < N; ++j) {
        int minVal = matrix[0][j];
        for (int i = 1; i < M; ++i) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        cout << "Столбец " << j << ": " << minVal << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\nОшибка: введите целое число (1 или 2).\n";
            continue;
        }

        switch (choice) {
        case 1:
            processMatrix();
            break;
        case 2:
            cout << "Программа завершена.\n";
            return 0;
        default:
            cout << "\nНеверный выбор. Введите 1 или 2.\n";
            break;
        }
    }

    return 0;
}