#include<iostream>
#include<string>
#include<list>
#include<fstream>


using namespace std;

int find(string text, int start, int end, char searchedSymbol) {

	for (int i = start; i < end; i++) {
		if (text[i] == searchedSymbol)
			return i;
	}
	return -1;
}

string search1(string text) {
	int count = 0;

	string longest = "";
	string tempStr = "";
	int start = 0;
	int end = 0;
	while (true) {
		end = find(text, start, text.size(), ' ');
		if (end == -1)
		{
			count++;
			if (isalpha(text[start]) &&  toupper(text[start]) == toupper(text[text.size()-1]) && (text.size() - start) > longest.size())
			{
				longest = "";
				for (int i = start; i < text.size(); i++)
				{
					count++;
					longest += text[i];
				}
			}

			break;
		}
		else
		{
			count++;
			if (isalpha(text[start]) && toupper(text[start]) == toupper(text[end - 1]) && ((end - start) > longest.size()))
			{
				longest = "";
				for (int i = start; i < end; i++)
				{
					count++;
					longest += text[i];
				}
			}
			start = end + 1;
		}
	}
	cout << count << endl;
	if (longest.size() > 0 && !isalpha(longest[0])) {
		return "";
	}

	return longest;
}


int search2(string example, string text) {
	int count = 0;
	for (int i = text.size() - example.size(); i > -1 ; i--) {
		for (int j = 0; j < example.size(); j++)
		{
			count++;
			if (text[i + j] != example[j])
				break;
			if (j == example.size() - 1)
			{
				cout << count << endl;
				return i;
			}
		}
	}
	cout << count << endl;
	return -1;
}

void main() {
	setlocale(LC_ALL, "Russian");

	ifstream textReader("t.txt");

	/*
	string text;
	list<string> list;
	while (true)
	{
		getline(cin, text);
		if (text[0] == '@')
			break;
		list.push_back(text);
	}
	
	cout << search1(list) << endl;*/	

	string text = "Разработайте приложения в соответствии с заданиями в индивидуальном варианте (п.2). В отчёте в разделе «Математическая модель решения(описание алгоритма)» разобрать алгоритм поиска на примере.Подсчитать количество сравнений для успешного поиска первого вхождения образца в текст и безуспешного поиска. Определить функцию(или несколько функций) для реализации алгоритма поиска.Определить предусловие и постусловие. Сформировать таблицу тестов с указанием успешного и неуспешного поиска, используя большие и небольшие по объему текст и образец, провести на её основе этап тестирования. Оценить практическую сложность алгоритма в зависимости от длины текста и длины образца и отобразить результаты в таблицу(для отчета). В отчёте сделайте вывод о проделанной работе, основанный на полученных результатах рыба";

	cout << search2("рыба", text) << endl;

	string k = "";

	//cout << search2("aki", "aki lki sdsd ddf dfgg gi") << endl;

	textReader.close();
}