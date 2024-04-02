#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

wstring palindrom(wstring word, int i) {
	if (i == floor(word.length() / 2)) return L"YES";
	if (word[i] != word[word.length() - 1 - i]) return L"NO";
	return palindrom(word, ++i);
}

int main() {
	string loc(strcat(setlocale(LC_ALL, ""), " > nul"));
    system(loc.replace(0, loc.find('.') + 1, "chcp ").c_str());

	wstring word;
	wcout << L"Введите слово строчными буквами: ";
	wcin >> word;

	wcout << palindrom(word, 0);

	return 0;
}
