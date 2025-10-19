#include <iostream>
#include <clocale>
#include <limits>

using namespace std;

const int MAX_M = 10;
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

int getMatrixDimension(const char* name, int maxVal) {
    int dim;
    cout << "Введите количество " << name << " (от 1 до " << maxVal << "): ";
    while (true) {
        if (!safeInputInt(dim)) {
            cout << "Ошибка: введите целое число. Повторите ввод: ";
        }
        else if (dim < 1 || dim > maxVal) {
            cout << "Ошибка: значение должно быть от 1 до " << maxVal << ". Повторите: ";
        }
        else {
            return dim;
        }
    }
}

void findColumnMins(int matrix[][MAX_N], int M, int N, int mins[]) {
    for (int j = 0; j < N; ++j) {
        int minVal = matrix[0][j];
        for (int i = 1; i < M; ++i) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        mins[j] = minVal;
    }
}

void printMatrix(int matrix[][MAX_N], int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(4);
            cout << matrix[i][j];
        }
        cout << "\n";
    }
}

void inputMatrix(int matrix[][MAX_N], int M, int N) {
    cout << "Введите элементы матрицы " << M << "x" << N << ":\n";
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            while (!safeInputInt(matrix[i][j])) {
                cout << "Ошибка: введите целое число. Повторите ввод для [" << i << "][" << j << "]: ";
            }
        }
    }
}

void processMatrix() {
    int M = getMatrixDimension("строк", MAX_M);
    int N = getMatrixDimension("столбцов", MAX_N);

    int matrix[MAX_M][MAX_N];
    inputMatrix(matrix, M, N);

    cout << "\nВаша матрица:\n";
    printMatrix(matrix, M, N);

    int mins[MAX_N];
    findColumnMins(matrix, M, N, mins);

    cout << "\nМинимальные элементы в столбцах:\n";
    for (int j = 0; j < N; ++j) {
        cout << "Столбец " << j << ": " << mins[j] << "\n";
    }
}

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    {
        const int M1 = 2, N1 = 3;
        int matrix[MAX_M][MAX_N] = {
            {5, 8, 3},
            {2, 9, 1}
        };
        int expected[N1] = { 2, 8, 1 };
        int result[MAX_N];
        findColumnMins(matrix, M1, N1, result);

        bool ok = true;
        for (int j = 0; j < N1; ++j) {
            if (result[j] != expected[j]) ok = false;
        }
        cout << (ok ? "Тест 1 (2x3): OK\n" : "Тест 1: FAIL\n");
    }

    {
        const int M2 = 3, N2 = 2;
        int matrix[MAX_M][MAX_N] = {
            {-1,  5},
            {-3,  2},
            {-2,  0}
        };
        int expected[N2] = { -3, 0 };
        int result[MAX_N];
        findColumnMins(matrix, M2, N2, result);

        bool ok = true;
        for (int j = 0; j < N2; ++j) {
            if (result[j] != expected[j]) ok = false;
        }
        cout << (ok ? "Тест 2 (с отрицательными): OK\n" : "Тест 2: FAIL\n");
    }

    {
        const int M3 = 1, N3 = 4;
        int matrix[MAX_M][MAX_N] = { {10, -5, 0, 7} };
        int expected[N3] = { 10, -5, 0, 7 };
        int result[MAX_N];
        findColumnMins(matrix, M3, N3, result);

        bool ok = true;
        for (int j = 0; j < N3; ++j) {
            if (result[j] != expected[j]) ok = false;
        }
        cout << (ok ? "Тест 3 (1 строка): OK\n" : "Тест 3: FAIL\n");
    }

    {
        const int M4 = 4, N4 = 1;
        int matrix[MAX_M][MAX_N] = { {8}, {3}, {9}, {1} };
        int expected[N4] = { 1 };
        int result[MAX_N];
        findColumnMins(matrix, M4, N4, result);

        bool ok = (result[0] == expected[0]);
        cout << (ok ? "Тест 4 (1 столбец): OK\n" : "Тест 4: FAIL\n");
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Ввести матрицу и найти минимумы в столбцах\n";
    cout << "2. Завершить программу\n";
    cout << "3. Запустить тесты\n";
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\nОшибка: введите целое число (1, 2 или 3).\n";
            continue;
        }

        switch (choice) {
        case 1:
            processMatrix();
            break;
        case 2:
            cout << "Программа завершена.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\nНеверный выбор. Введите 1, 2 или 3.\n";
            break;
        }
    }

    return 0;
}