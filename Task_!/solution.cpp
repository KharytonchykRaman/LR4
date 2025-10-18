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
    cout << "������� ���������� ��������� (�� 1 �� " << MAX_SIZE << "): ";
    while (true) {
        if (!safeInputInt(n)) {
            cout << "������: ������� �� �����. ���������� �����: ";
        }
        else if (n <= 0 || n > MAX_SIZE) {
            cout << "������: ����� ������ ���� �� 1 �� " << MAX_SIZE << ". ���������� �����: ";
        }
        else {
            return n;
        }
    }
}

void inputArray(int arr[], int n) {
    cout << "������� " << n << " ����� �����:\n";
    for (int i = 0; i < n; ++i) {
        cout << "������� [" << i << "]: ";
        while (!safeInputInt(arr[i])) {
            cout << "������: ������� ����� �����. ��������� ���� ��� �������� [" << i << "]: ";
        }
    }
}

void runProgram() {
    int n = getArraySize();
    int arr[MAX_SIZE];
    inputArray(arr, n);
    long long inversions = countInversions(arr, n);
    cout << "\n���������� ��������: " << inversions << "\n\n";
}

void showMenu() {
    cout << "=== ���� ===\n";
    cout << "1. ��������� ���������\n";
    cout << "2. ��������� ���������\n";
    cout << "�������� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\n������: ������� ����� (1 ��� 2).\n\n";
            continue;
        }

        switch (choice) {
        case 1:
            runProgram();
            break;
        case 2:
            cout << "��������� ���������.\n";
            return 0;
        default:
            cout << "\n�������� �����. ������� 1 ��� 2.\n\n";
            break;
        }
    }

    return 0;
}