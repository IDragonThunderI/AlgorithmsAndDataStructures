#include <iostream>
#include <cmath>
using namespace std;

// Инициализация массива
void init(int A[], int n) {
	wcout << L"Инициализация массива..." << endl;

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 100 + 1; // Наполнение массива случайными числами от 1 до 100
		/* Выводим массив в консоль для наглядности (только если количество чисел в массиве не превышает 100,
			чтобы не забивать консоль большим количеством чисел) */
		if (n <= 100) {
			cout << A[i] << " ";
		}
	}

	wcout << L"\nЗавершено" << endl << endl;
}

// Сортировка Хоара
void Qsort(int A[], int f, int l) {
	int first = f, last = l;					// Определяем индексы первого и последнего элементов
	int separator = A[((first + last) / 2)];	// Определяем "разделитель" как центральный элемент

	while (first <= last) {
		// Находим элемент слева от разделителя, больший по значению разделителя
		while (A[first] < separator) {
			first++;
		}
		// Находим элемент справа от разделителя, меньший по значению разделителя
		while (A[last] > separator) {
			last--;
		}
		// Меняем местами найденые элементы
		if (first <= last) {
		int buf = A[first];
			A[first] = A[last];
			A[last] = buf;
			first++;
			last--;
		}
	}

	// Рекурсивно сортируем полученные две части массива
	if (f < last) {
		Qsort(A, f, last);
	}
	if (first < l) {
		Qsort(A, first, l);
	}
}

// Вход в рекурсивную сортировку Хоара
void Hoar_sort(int A[], int n) {
	wcout << L"Сортировка массива..." << endl;

	Qsort(A, 0, n - 1); // Вход в рекурсию
	
	wcout << L"Завершено" << endl << endl;
}

// Линейный поиск в неупорядоченном массиве
int unsorted_line_search(int A[], int n, int srch_elem) {
	int count;
	bool srch_index = false;

	// Проходимся по каждому элементу массива, пока не найдём искомый или не закончится массив
	for (count = 0; count < n; count++) {
		// Сравниваем элемент массива с искомым элементом
		if (A[count] == srch_elem) {
			srch_index = true;
			count++;
			wcout << L"Искомый элемент найден." << endl;
			break;
		}
	}

	if (!srch_index) {
		wcout << L"Искомый элемент не найден." << endl;
	}

	return count; // Выводим количество итераций поиска
}

// Быстрый линейный поиск в неупорядоченном массиве
int unsorted_fast_line_search(int A[], int n, int srch_elem) {
	int count = 0;
	A[n] = srch_elem; // Добавляем в конец массива искомый элемент

	// Проходимся по каждому элементу массива, пока не найдём искомый
	while (A[count] != srch_elem) {
		count++;
	}

	// Если искомый элемент найден не последним (добавленным вручную), то мы нашли его среди элементов массива
	if (count != n) {
		wcout << L"Искомый элемент найден." << endl;
	// Иначе найден элемент добавленный вручную и среди массива его нет
	} else {
		wcout << L"Искомый элемент не найден." << endl;
	}

	return ++count; // Выводим количество итераций поиска
}

// Быстрый линейный поиск в упорядоченном массиве
int sorted_fast_line_search(int A[], int n, int srch_elem) {
	int count = 0;
	A[n] = srch_elem; // Добавляем в конец массива искомый элемент

	// Проходимся по каждому элементу массива, пока не найдём элемент не меньший искомого
	while (A[count] < srch_elem) {
		count++;
	}

	// Если искомый элемент найден не последним (добавленным вручную), то мы нашли его среди элементов массива
	if (A[count] == srch_elem && count != n) {
		wcout << L"Искомый элемент найден." << endl;
	// Иначе найден элемент больше искомого или добавленный вручную
	} else {
		wcout << L"Искомый элемент не найден." << endl;
	}

	return ++count; // Выводим количество итераций поиска
}

// Бинарный поиск
int bin_search(int A[], int srch_elem, int begin, int end) {
	int mid_index = (begin + end) / 2; // Определяем индекс центрального элемента

	// Если центральный элемент равен искомому, то мы нашли его
	if (A[mid_index] == srch_elem) {
		wcout << L"Искомый элемент найден." << endl;
		return 1; // Выводим количество итераций поиска
	}

	// Если начальный и конечный индексы равны, значит больше не осталось элементов для проверки
	if (begin == end) {
		wcout << L"Искомый элемент не найден." << endl;
		return 1; // Выводим количество итераций поиска
	}

	// Рекурсивно выполняем поиск
	// Если центральный элемент меньше искомого, то определяем левую границу массива как индекс центрального элемента + 1
	if (A[mid_index] < srch_elem) {
		return bin_search(A, srch_elem, ++mid_index, end) + 1;
	// Иначе если центральный элемент больше искомого, то определяем правую границу массива, как индекс центрального элемента
	} else {
		return bin_search(A, srch_elem, begin, mid_index) + 1;
	}
}

// Блочный поиск
int block_search(int A[], int n, int srch_elem) {
	int count = 0, curr_elem = 0;
	int block_amount = (int)(sqrt(n));	// Определяем количество блоков как корень из количества элементов массива
	A[n] = srch_elem;					// Добавляем в конец массива искомый элемент (для быстрого линейного поиска)

	// Выполняем пока остались непроверенные блоки
	while (count < block_amount) {
		count++;
		// Если последний элемент блока равен искомому, то мы нашли его
		if (A[(block_amount * count) - 1] == srch_elem) {
			wcout << L"Искомый элемент найден." << endl;
			return count; // Выводим количество итераций поиска
		}

		// Если последний элемент блока больше искомого, то искомый элемент может находиться где-то в этом блоке
		if (A[(block_amount * count) - 1] > srch_elem) {
			curr_elem = block_amount * count - block_amount; // Определяем начальный элемент поиска как первый элемент блока
			goto line_srch; // Переходим к быстрому линейному поиску
		}
	}

	curr_elem = block_amount * count; // Определяем начальный элемент поиска как первый элемент последнего блока
	line_srch: // Быстрый линейный поиск
	while (A[curr_elem] < srch_elem) {
		curr_elem++;
		count++;
	}

	if (A[curr_elem] == srch_elem && curr_elem != n) {
		wcout << L"Искомый элемент найден." << endl;
	} else {
		wcout << L"Искомый элемент не найден." << endl;
	}

	return ++count; // Выводим количество итераций поиска
}

int main() {
	setlocale(LC_ALL, "");

	int n, srch_elem;
	wcout << L"Введите размер массива: ";
	cin >> n;

	int* A = new int[n + 1];

	init(A, n); // Инициализация массива

	wcout << L"Введите искомый элемент массива: ";
	cin >> srch_elem;

	wcout << L"\nПоиск числа " << srch_elem << L" в массиве..." << endl << endl;

	// Алгоритмы поиска в неупорядоченном массиве:
	wcout << L"Количество итераций поиска Unsorted_line_search: " << unsorted_line_search(A, n, srch_elem) << endl << endl;
	wcout << L"Количество итераций поиска Unsorted_fast_line_search: " << unsorted_fast_line_search(A, n, srch_elem) << endl << endl;

	Hoar_sort(A, n); // Сортировка массива
	
	// Алгоритмы поиска в упорядоченном массиве:
	wcout << L"Количество итераций поиска Sorted_fast_line_search: " << sorted_fast_line_search(A, n, srch_elem) << endl << endl;
	wcout << L"Количество итераций поиска Bin_search: " << bin_search(A, srch_elem, 0, n - 1) << endl << endl;
	wcout << L"Количество итераций поиска Block_search: " << block_search(A, n, srch_elem) << endl << endl;

	delete[] A;

	return 0;
}
