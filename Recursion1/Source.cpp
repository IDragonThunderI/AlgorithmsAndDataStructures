#include <iostream>
using namespace std;

int calc(unsigned long long n) {
	if (n % 10 == 0) return 0;
	if (n % 10 == 1) return calc(n / 10) + 1;
	return calc(n / 10);
}

int main() {
	setlocale(LC_ALL, "");

	unsigned long long n;
	wcout << L"Введите последовательность натуральных чисел:" << endl;
	cin >> n;

	while (n % 10 != 0) {
		n /= 10;
	}
	n /= 100;

	wcout << L"Количество единиц до появления 00: " << calc(n) << endl;

	return 0;
}
