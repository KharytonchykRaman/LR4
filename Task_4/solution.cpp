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
	cout << "������� " << n * n * n << " ��������������� ����� �����:\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				cout << "arr[" << i << "][" << j << "][" << k << "] = ";
				while (true) {
					int val;
					if (!safeInputInt(val)) {
						cout << "������: ������� ����� �����. ���������: ";
					}
					else if (val < 0) {
						cout << "����� ������ ���� ���������������. ���������: ";
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
	cout << "������� ������ ���� n (n > 0): ";
	while (true) {
		if (!safeInputInt(n) || n <= 0) {
			cout << "������: ������� ������������� ����� �����: ";
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

	cout << "\n����� �� ����������:\n";
	cout << "��������� 1 (i,i,i): " << s1 << "\n";
	cout << "��������� 2 (i,i,n-1-i): " << s2 << "\n";
	cout << "��������� 3 (i,n-1-i,i): " << s3 << "\n";
	cout << "��������� 4 (i,n-1-i,n-1-i): " << s4 << "\n";
	cout << "\n������������ �����: " << maxSum << " (��������� " << bestDiag << ")\n";

	free3D(cube, n);
	cout << "\n";
}

void showMenu() {
	cout << "=== ���� ===\n";
	cout << "1. ����� ��������� ���� � ���������� ������\n";
	cout << "2. ��������� ���������\n";
	cout << "�������� �����: ";
}

int main() {
	setlocale(LC_ALL, "Russian");

	int choice;
	while (true) {
		showMenu();
		if (!safeInputInt(choice)) {
			cout << "\n������: ������� 1 ��� 2.\n\n";
			continue;
		}

		switch (choice) {
		case 1:
			runTask();
			break;
		case 2:
			cout << "��������� ���������.\n";
			return 0;
		default:
			cout << "\n�������� �����. ������� 1 ��� 2.\n\n";
		}
	}

	return 0;
}