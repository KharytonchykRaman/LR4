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

void showMenu() {
    cout << "=== Меню ===\n";
    cout << "1. Обработать поле Сапёра\n";
    cout << "2. Завершить программу\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!safeInputInt(choice)) {
            cout << "\nВведите 1 или 2.\n\n";
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
        default:
            cout << "\nВыберите 1 или 2.\n\n";
        }
    }
}