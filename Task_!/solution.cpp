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

void showMenu() {
    cout << "=== Меню ===\n";
    cout << "1. Запустить программу\n";
    cout << "2. Завершить программу\n";
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\nОшибка: введите число (1 или 2).\n\n";
            continue;
        }

        switch (choice) {
        case 1:
            runProgram();
            break;
        case 2:
            cout << "Программа завершена.\n";
            return 0;
        default:
            cout << "\nНеверный выбор. Введите 1 или 2.\n\n";
            break;
        }
    }

    return 0;
}