#include <iostream>
#include <iomanip>
using namespace std;

void Depth_First_Search(int n, int** Graph, bool* Visited, int Node) {
	Visited[Node] = true;
	wcout << L"Посещённый узел: " << Node + 1 << endl;

	for (int i = 0; i < n; i++) {
		if (Graph[Node][i] && !Visited[i]) {
			Depth_First_Search(n, Graph, Visited, i);
		}
	}
}

void Breadth_First_Search(int n, int** Graph, bool* Visited, int Node) {
	int* List = new int[n](); // Очередь
	int Count = 0, Head = 0;  // Указатели очереди
	int i;

	// Помещение в очередь вершины Node
	List[Count++] = Node;
	Visited[Node] = true;

	while (Head < Count) {
		// Взятие вершины из очереди
		Node = List[Head++];
		wcout << L"Посещённый узел: " << Node + 1 << endl;

		// Просмотр всех вершин, связанных с вершиной Node
		for (i = 0; i < n; i++) {
			// Если вершина ранее не просмотрена, то заносим ее в очередь
			if (Graph[Node][i] && !Visited[i]) {
				List[Count++] = i;
				Visited[i] = true;
			}
		}
	}

	delete[] List;
}

void Dijkstra(int n, int** Graph, int Node) {
	bool* Selected = new bool[n];
	int* Distance = new int[n];
	int* Path = new int[n];
	int i, j, Max_Sum = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Max_Sum += Graph[i][j];
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (Graph[i][j] == 0) {
				Graph[i][j] = Max_Sum;
			}
		}
	}

	for (i = 0; i < n; i++) {
		Selected[i] = false;
		Path[i] = Node;
		Distance[i] = Graph[Node][i];
	}

	Selected[Node] = true;
	Path[Node] = -1;

	for (i = 0; i < n - 1; i++) {
		int w = 0;
		for (j = 1; j < n; j++) {
			if (!Selected[w]) {
				if (!Selected[j] && Distance[j] <= Distance[w]) {
					w = j;
				}
			} else {
				w++;
			}
		}

		Selected[w] = true;

		for (j = 1; j < n; j++) {
			if (!Selected[j]) {
				if (Distance[w] + Graph[w][j] < Distance[j]) {
					Distance[j] = Distance[w] + Graph[w][j];
					Path[j] = w;
				}
			}
		}
	}

	wcout << L"Начальный узел: " << Node + 1 << endl;
	for (i = 0; i < n; i++) {
		wcout << setw(5) << i + 1;
	}
	wcout << L"\n";
	for (i = 0; i < (n * 5 + 1); i++) {
		wcout << L"_";
	}
	wcout << L"\n";

	for (i = 0; i < n; i++) {
		wcout << setw(5) << Distance[i];
	}
	wcout << L"\n";
	
	for (i = 0; i < n; i++) {
		wcout << setw(5) << Path[i] + 1;
	}
	wcout << L"\n";
	
	delete[] Path;
	delete[] Distance;
	delete[] Selected;
}

void Floyd(int n, int** Graph) {
	int i, j, k, Max_Sum = 0;
	
	int** ShortestPath = new int* [n];
	for (i = 0; i < n; i++) {
		ShortestPath[i] = new int[n]();
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i != j) {
				ShortestPath[i][j] = Graph[i][j];
			}
		}
	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Max_Sum += ShortestPath[i][j];
		}
	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (ShortestPath[i][j] == 0 && i != j) {
				ShortestPath[i][j] = Max_Sum;
			}
		}
	}
	
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if ((ShortestPath[i][k] + ShortestPath[k][j]) < ShortestPath[i][j]) {
					ShortestPath[i][j] = ShortestPath[i][k] + ShortestPath[k][j];
				}
			}
		}
	}

	wcout << L"  ";
	for (i = 0; i < n; i++) {
		wcout << setw(4) << i + 1;
	}
	wcout << L"\n  +";
	for (i = 0; i < (n * 4 + 1); i++) {
		wcout << L"-";
	}
	for (i = 0; i < n; i++) {
		wcout << L"\n" << i + 1 << L" |";
		for (int j = 0; j < n; j++) {
			wcout << setw(4) << ShortestPath[i][j];
		}
	}
	wcout << "\n";

	for (i = 0; i < n; i++) {
		delete[] ShortestPath[i];
	}
	delete[] ShortestPath;
}

int main() {
	setlocale(LC_ALL, "");

	int n;
	wcout << L"Введите количество узлов: ";
	cin >> n;

	// Инициализация двумерного динамического массива
	int** Graph = new int* [n];
	for (int i = 0; i < n; i++) {
		Graph[i] = new int[n]();
	}

	char answer;
	wcout << L"\nВыберите тип графа (u - неориентированный / o - ориентированный): ";
	cin >> answer;
	
	// Заполнение матрицы смежности
	switch (answer) {
	case 'u':
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				wcout << i + 1 << L" > " << j + 1 << L": ";
				cin >> Graph[i][j];
				Graph[j][i] = Graph[i][j];
			}
		}
		wcout << L"\n  ";
		break;
	case 'o':
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				wcout << i + 1 << L" > " << j + 1 << L": ";
				cin >> Graph[i][j];
			}
		}
		wcout << L"\n  ";
		break;
	default:
		break;
	}
	
	// Вывод матрицы смежности на экран
	for (int i = 0; i < n; i++) {
		wcout << setw(4) << i + 1;
	}
	wcout << L"\n  +";
	for (int i = 0; i < (n * 4); i++) {
		wcout << L"-";
	}
	for (int i = 0; i < n; i++) {
		wcout << L"\n" << i + 1 << L" |";
		for (int j = 0; j < n; j++) {
			wcout << setw(4) << Graph[i][j];
		}
	}

	// Поиск в глубину
	wcout << L"\n\nПоиск в глубину:" << endl;
	bool* Visited = new bool[n]();
	Depth_First_Search(n, Graph, Visited, 0);

	// Поиск в ширину
	wcout << L"\nПоиск в ширину:" << endl;
	for (int i = 0; i < n; i++) {
		Visited[i] = false;
	}
	Breadth_First_Search(n, Graph, Visited, 0);

	// Алгоритм Дейкстры
	wcout << L"\nАлгоритм Дейкстры:" << endl;
	Dijkstra(n, Graph, 0);

	// Алгоритм Флойда
	wcout << L"\nАлгоритм Флойда:" << endl;
	Floyd(n, Graph);

	// Освобождение памяти
	for (int i = 0; i < n; i++) {
		delete[] Graph[i];
	}
	delete[] Graph;
	delete[] Visited;

	return 0;
}
