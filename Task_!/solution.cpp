#include <iostream>
#include <limits>
#include <clocale>  

using namespace std;

const int MAX_SIZE = 100;

long long countInversions(int arr[], int n) {
    long long invCount = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                ++invCount;
            }
        }
    }
    return invCount;
}

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

int getArraySize() {
    int n;
    cout << "Введите количество элементов (от 1 до " << MAX_SIZE << "): ";
    while (true) {
        if (!safeInputInt(n)) {
            cout << "Ошибка: введено не число. Попробуйте снова: ";
        }
        else if (n <= 0 || n > MAX_SIZE) {
            cout << "Ошибка: число должно быть от 1 до " << MAX_SIZE << ". Попробуйте снова: ";
        }
        else {
            return n;
        }
    }
}

void inputArray(int arr[], int n) {
    cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Элемент [" << i << "]: ";
        while (!safeInputInt(arr[i])) {
            cout << "Ошибка: введите целое число. Повторите ввод для элемента [" << i << "]: ";
        }
    }
}

void runProgram() {
    int n = getArraySize();
    int arr[MAX_SIZE];
    inputArray(arr, n);
    long long inversions = countInversions(arr, n);
    cout << "\nКоличество инверсий: " << inversions << "\n\n";
}

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    struct TestCase {
        const char* name;
        int arr[10];     
        int n;
        long long expected;
    };

    TestCase tests[] = {
        {"Пустой массив", {}, 0, 0},
        {"Один элемент", {42}, 1, 0},
        {"Отсортированный", {1,2,3,4,5}, 5, 0},
        {"Обратный порядок (4 эл.)", {4,3,2,1}, 4, 6},
        {"Обратный порядок (5 эл.)", {5,4,3,2,1}, 5, 10},
        {"Смешанный массив", {2,3,8,6,1}, 5, 5},
        {"Одинаковые элементы", {7,7,7}, 3, 0},
        {"Два элемента — инверсия", {10,5}, 2, 1},
        {"Два элемента — порядок", {5,10}, 2, 0}
    };

    int total = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; ++i) {
        long long result = countInversions(tests[i].arr, tests[i].n);
        if (result == tests[i].expected) {
            cout << tests[i].name << ": OK\n";
            passed++;
        }
        else {
            cout << tests[i].name << ": FAIL (ожидалось "
                << tests[i].expected << ", получено " << result << ")\n";
        }
    }

    cout << "\n--- Итог: " << passed << " из " << total << " тестов пройдено ---\n\n";
}

void showMenu() {
    cout << "=== Меню ===\n";
    cout << "1. Запустить программу\n";
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
            cout << "\nОшибка: введите число (1, 2 или 3).\n\n";
            continue;
        }

        switch (choice) {
        case 1:
            runProgram();
            break;
        case 2:
            cout << "Программа завершена.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\nНеверный выбор. Введите 1, 2 или 3.\n\n";
            break;
        }
    }

    return 0;
}