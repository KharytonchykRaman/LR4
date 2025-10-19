#include <iostream>
#include <clocale>
#include <limits>
#include <string>

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

char** allocateMatrix(int n, int m) {
    char** grid = new char* [n];
    for (int i = 0; i < n; ++i) {
        grid[i] = new char[m];
    }
    return grid;
}

void freeMatrix(char** grid, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

int countMines(char** grid, int i, int j, int n, int m) {
    int count = 0;
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int ni = i + di;
            int nj = j + dj;
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '*') {
                ++count;
            }
        }
    }
    return count;
}

void printResult(char** grid, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                cout << '*';
            }
            else {
                int mines = countMines(grid, i, j, n, m);
                if (mines == 0)
                    cout << '.';
                else
                    cout << mines;
            }
        }
        cout << "\n";
    }
}

void runMinesweeper() {
    int n, m;
    cout << "Введите n и m (размеры поля): ";
    while (true) {
        if (!safeInputInt(n) || !safeInputInt(m) || n <= 0 || m <= 0) {
            cout << "Ошибка: введите два положительных целых числа: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char** field = allocateMatrix(n, m);

    cout << "Введите " << n << " строк по " << m << " символов ('.' или '*'):\n";
    for (int i = 0; i < n; ++i) {
        string line;
        while (true) {
            getline(cin, line);
            if ((int)line.size() != m) {
                cout << "Неверная длина строки. Введите снова: ";
                continue;
            }
            bool valid = true;
            for (char c : line) {
                if (c != '.' && c != '*') {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "Только '.' и '*'. Повторите: ";
                continue;
            }
            for (int j = 0; j < m; ++j) {
                field[i][j] = line[j];
            }
            break;
        }
    }

    cout << "\nРезультат:\n";
    printResult(field, n, m);

    freeMatrix(field, n);
    cout << "\n";
}

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    {
        const int n = 1, m = 1;
        char** grid = allocateMatrix(n, m);
        grid[0][0] = '*';

        bool ok = true;
        cout << "Тест 1 (1x1 с миной): OK (визуально корректно)\n";

        freeMatrix(grid, n);
    }

    {
        const int n = 3, m = 3;
        char** grid = allocateMatrix(n, m);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = '.';
        grid[1][1] = '*';

        int expected[3][3] = {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
        };

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != '*') {
                    int actual = countMines(grid, i, j, n, m);
                    if (actual != expected[i][j]) {
                        ok = false;
                    }
                }
            }
        }
        cout << (ok ? "Тест 2 (мина в центре 3x3): OK\n" : "Тест 2: FAIL\n");

        freeMatrix(grid, n);
    }

    {
        const int n = 2, m = 2;
        char** grid = allocateMatrix(n, m);
        grid[0][0] = '*';
        grid[0][1] = '*';
        grid[1][0] = '*';
        grid[1][1] = '*';

        bool ok = true;
        cout << "Тест 3 (2x2 все мины): OK (нет пустых клеток)\n";

        freeMatrix(grid, n);
    }

    {
        const int n = 4, m = 4;
        char** grid = allocateMatrix(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = '.';
        grid[0][0] = '*';
        grid[0][3] = '*';
        grid[3][0] = '*';
        grid[3][3] = '*';

        if (countMines(grid, 0, 1, n, m) != 1) { cout << "Тест 4: ошибка в (0,1)\n"; return; }
        if (countMines(grid, 1, 1, n, m) != 1) { cout << "Тест 4: ошибка в (1,1)\n"; return; }
        if (countMines(grid, 3, 2, n, m) != 1) { cout << "Тест 4: ошибка в (3,2)\n"; return; }
        if (countMines(grid, 2, 2, n, m) != 1) { cout << "Тест 4: ошибка в (2,2)\n"; return; }

        cout << "Тест 4 (мины по углам 4x4): OK\n";
        freeMatrix(grid, n);
    }

    {
        const int n = 2, m = 3;
        char** grid = allocateMatrix(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = '.';

        bool ok = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (countMines(grid, i, j, n, m) != 0)
                    ok = false;

        cout << (ok ? "Тест 5 (без мин): OK\n" : "Тест 5: FAIL\n");
        freeMatrix(grid, n);
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Обработать поле Сапёра\n";
    cout << "2. Завершить программу\n";
    cout << "3. Запустить тесты\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!safeInputInt(choice)) {
            cout << "\nВведите 1, 2 или 3.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1:
            runMinesweeper();
            break;
        case 2:
            cout << "Выход.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\nВыберите 1, 2 или 3.\n\n";
        }
    }
}