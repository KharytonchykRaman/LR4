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

int findBestDiagonal(long long s1, long long s2, long long s3, long long s4) {
	long long maxSum = s1;
	int best = 1;
	if (s2 > maxSum) { maxSum = s2; best = 2; }
	if (s3 > maxSum) { maxSum = s3; best = 3; }
	if (s4 > maxSum) { maxSum = s4; best = 4; }
	return best;
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
	int best = findBestDiagonal(s1, s2, s3, s4);

	cout << "\n����� �� ����������:\n";
	cout << "��������� 1 (i,i,i): " << s1 << "\n";
	cout << "��������� 2 (i,i,n-1-i): " << s2 << "\n";
	cout << "��������� 3 (i,n-1-i,i): " << s3 << "\n";
	cout << "��������� 4 (i,n-1-i,n-1-i): " << s4 << "\n";
	cout << "\n������������ �����: " << (s1 > s2 && s1 > s3 && s1 > s4 ? s1 : (s2 > s3 && s2 > s4 ? s2 : (s3 > s4 ? s3 : s4)))
		<< " (��������� " << best << ")\n";

	free3D(cube, n);
	cout << "\n";
}

void runTests() {
	cout << "\n=== ������ ���������� ������ ===\n";

	{
		const int n = 1;
		int*** cube = allocate3D(n);
		cube[0][0][0] = 42;

		long long s1 = sumDiagonal1(cube, n);
		long long s2 = sumDiagonal2(cube, n);
		long long s3 = sumDiagonal3(cube, n);
		long long s4 = sumDiagonal4(cube, n);

		bool ok = (s1 == 42 && s2 == 42 && s3 == 42 && s4 == 42);
		cout << (ok ? "���� 1 (1x1x1): OK\n" : "���� 1: FAIL\n");

		free3D(cube, n);
	}

	{
		const int n = 2;
		int*** cube = allocate3D(n);

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k)
					cube[i][j][k] = 0;

		cube[0][0][0] = 10;
		cube[1][1][1] = 20;

		cube[0][0][1] = 100;
		cube[1][1][0] = 200;

		cube[0][1][0] = 1000;
		cube[1][0][1] = 2000;

		cube[0][1][1] = 10000;
		cube[1][0][0] = 20000;

		long long s1 = sumDiagonal1(cube, n); // 10+20 = 30
		long long s2 = sumDiagonal2(cube, n); // 100+200 = 300
		long long s3 = sumDiagonal3(cube, n); // 1000+2000 = 3000
		long long s4 = sumDiagonal4(cube, n); // 10000+20000 = 30000

		bool ok = (s1 == 30 && s2 == 300 && s3 == 3000 && s4 == 30000);
		cout << (ok ? "���� 2 (2x2x2 � ������� �������): OK\n" : "���� 2: FAIL\n");

		free3D(cube, n);
	}

	{
		const int n = 3;
		int*** cube = allocate3D(n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k)
					cube[i][j][k] = 0;

		long long s1 = sumDiagonal1(cube, n);
		long long s2 = sumDiagonal2(cube, n);
		long long s3 = sumDiagonal3(cube, n);
		long long s4 = sumDiagonal4(cube, n);

		bool ok = (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0);
		cout << (ok ? "���� 3 (��� ����): OK\n" : "���� 3: FAIL\n");

		free3D(cube, n);
	}

	{
		const int n = 2;
		int*** cube = allocate3D(n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k)
					cube[i][j][k] = 0;

		cube[0][0][0] = 100;
		cube[1][1][1] = 100;

		cube[0][0][1] = 10; 
		cube[1][1][0] = 10;


		int best = findBestDiagonal(
			sumDiagonal1(cube, n),
			sumDiagonal2(cube, n),
			sumDiagonal3(cube, n),
			sumDiagonal4(cube, n)
		);

		bool ok = (best == 1);
		cout << (ok ? "���� 4 (��������� 1 � ��������): OK\n" : "���� 4: FAIL\n");

		free3D(cube, n);
	}

	cout << "\n--- ������������ ��������� ---\n\n";
}

void showMenu() {
	cout << "\n=== ���� ===\n";
	cout << "1. ����� ��������� ���� � ���������� ������\n";
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
			cout << "\n������: ������� 1, 2 ��� 3.\n\n";
			continue;
		}

		switch (choice) {
		case 1:
			runTask();
			break;
		case 2:
			cout << "��������� ���������.\n";
			return 0;
		case 3:
			runTests();
			break;
		default:
			cout << "\n�������� �����. ������� 1, 2 ��� 3.\n\n";
		}
	}

	return 0;
}