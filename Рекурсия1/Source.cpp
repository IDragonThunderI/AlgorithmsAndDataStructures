#include <iostream>
using namespace std;

int calc(unsigned long long n);

int main()
{
	system("chcp 1251");
	system("cls");

	unsigned long long n;
	cout << "Введите последовательность натуральных чисел:" << endl;
	cin >> n;

	while (n % 10 != 0)
		n /= 10;
	n /= 100;

	cout << "Количество единиц до появления 00: " << calc(n) << endl;

	system("pause");
	return 0;
}

int calc(unsigned long long n)
{
	if (n % 10 == 0) return 0;
	if (n % 10 == 1) return calc(n / 10) + 1;
	return calc(n / 10);
}