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

void runTests() {
    cout << "\n=== ������ ���������� ������ ===\n";

    struct TestCase {
        const char* name;
        int arr[10];     
        int n;
        long long expected;
    };

    TestCase tests[] = {
        {"������ ������", {}, 0, 0},
        {"���� �������", {42}, 1, 0},
        {"���������������", {1,2,3,4,5}, 5, 0},
        {"�������� ������� (4 ��.)", {4,3,2,1}, 4, 6},
        {"�������� ������� (5 ��.)", {5,4,3,2,1}, 5, 10},
        {"��������� ������", {2,3,8,6,1}, 5, 5},
        {"���������� ��������", {7,7,7}, 3, 0},
        {"��� �������� � ��������", {10,5}, 2, 1},
        {"��� �������� � �������", {5,10}, 2, 0}
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
            cout << tests[i].name << ": FAIL (��������� "
                << tests[i].expected << ", �������� " << result << ")\n";
        }
    }

    cout << "\n--- ����: " << passed << " �� " << total << " ������ �������� ---\n\n";
}

void showMenu() {
    cout << "=== ���� ===\n";
    cout << "1. ��������� ���������\n";
    cout << "2. ��������� ���������\n";
    cout << "3. ��������� �����\n";
    cout << "�������� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();

        if (!safeInputInt(choice)) {
            cout << "\n������: ������� ����� (1, 2 ��� 3).\n\n";
            continue;
        }

        switch (choice) {
        case 1:
            runProgram();
            break;
        case 2:
            cout << "��������� ���������.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\n�������� �����. ������� 1, 2 ��� 3.\n\n";
            break;
        }
    }

    return 0;
}