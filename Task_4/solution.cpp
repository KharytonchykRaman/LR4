#include <iostream>
#include <clocale>
#include <limits>
#include <cstdlib>
#include <ctime>

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

int*** allocate3D(int n) {
	int*** arr = new int** [n];
	for (int i = 0; i < n; ++i) {
		arr[i] = new int* [n];
		for (int j = 0; j < n; ++j) {
			arr[i][j] = new int[n];
		}
	}
	return arr;
}

void free3D(int*** arr, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			delete[] arr[i][j];
		}
		delete[] arr[i];
	}
	delete[] arr;
}

void input3D(int*** arr, int n) {
	cout << "Введите " << n * n * n << " неотрицательных целых чисел:\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				cout << "arr[" << i << "][" << j << "][" << k << "] = ";
				while (true) {
					int val;
					if (!safeInputInt(val)) {
						cout << "Ошибка: введите целое число. Повторите: ";
					}
					else if (val < 0) {
						cout << "Число должно быть неотрицательным. Повторите: ";
					}
					else {
						arr[i][j][k] = val;
						break;
					}
				}
			}
		}
	}
}

long long sumDiagonal1(int*** arr, int n) { // (i, i, i)
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += arr[i][i][i];
	}
	return s;
}

long long sumDiagonal2(int*** arr, int n) { // (i, i, n-1-i)
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += arr[i][i][n - 1 - i];
	}
	return s;
}

long long sumDiagonal3(int*** arr, int n) { // (i, n-1-i, i)
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += arr[i][n - 1 - i][i];
	}
	return s;
}

long long sumDiagonal4(int*** arr, int n) { // (i, n-1-i, n-1-i)
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += arr[i][n - 1 - i][n - 1 - i];
	}
	return s;
}

void runTask() {
	int n;
	cout << "Введите размер куба n (n > 0): ";
	while (true) {
		if (!safeInputInt(n) || n <= 0) {
			cout << "Ошибка: введите положительное целое число: ";
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else {
			break;
		}
	}

	int*** cube = allocate3D(n);

	input3D(cube, n);

	long long s1 = sumDiagonal1(cube, n);
	long long s2 = sumDiagonal2(cube, n);
	long long s3 = sumDiagonal3(cube, n);
	long long s4 = sumDiagonal4(cube, n);

	long long maxSum = s1;
	int bestDiag = 1;

	if (s2 > maxSum) { maxSum = s2; bestDiag = 2; }
	if (s3 > maxSum) { maxSum = s3; bestDiag = 3; }
	if (s4 > maxSum) { maxSum = s4; bestDiag = 4; }

	cout << "\nСуммы по диагоналям:\n";
	cout << "Диагональ 1 (i,i,i): " << s1 << "\n";
	cout << "Диагональ 2 (i,i,n-1-i): " << s2 << "\n";
	cout << "Диагональ 3 (i,n-1-i,i): " << s3 << "\n";
	cout << "Диагональ 4 (i,n-1-i,n-1-i): " << s4 << "\n";
	cout << "\nМаксимальная сумма: " << maxSum << " (диагональ " << bestDiag << ")\n";

	free3D(cube, n);
	cout << "\n";
}

void showMenu() {
	cout << "=== Меню ===\n";
	cout << "1. Найти диагональ куба с наибольшей суммой\n";
	cout << "2. Завершить программу\n";
	cout << "Выберите пункт: ";
}

int main() {
	setlocale(LC_ALL, "Russian");

	int choice;
	while (true) {
		showMenu();
		if (!safeInputInt(choice)) {
			cout << "\nОшибка: введите 1 или 2.\n\n";
			continue;
		}

		switch (choice) {
		case 1:
			runTask();
			break;
		case 2:
			cout << "Программа завершена.\n";
			return 0;
		default:
			cout << "\nНеверный выбор. Введите 1 или 2.\n\n";
		}
	}

	return 0;
}