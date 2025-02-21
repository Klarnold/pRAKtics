#include "Tree.h"

int main() {
	setlocale(LC_ALL, "ru");

	Tree* body = new Tree("a", 87);
	int finalParts = 1;
	int value;
	string name;
	vector<string> elements;
	string tempName = "";
	cout << "Начинаем создание графа" << endl;
	while (name!= "- 1"){
		elements.clear();
		cout << "Введите имя и значение ячейки через пробел (для остановки работы программы введите -1):" << endl;
		cin >> name;
		if (name == "-1")
			break;
		cin >> value;
		finalParts++;
		cout << "Введите через пробел элементы, которые должны будут быть связаны с этой ячейкой (для остановки введите -1):" << endl;

		
		while (true) {
			cin >> tempName;
			if (tempName == "-1")
				break;
			elements.push_back(tempName);
		}
		tempName = "";

		body->addElement(name, value, elements);
	}
	body->visited = true;
	body->out(body);
	body->reset();

	cout << " ||||| " << endl;

    Tree* bodyPrima = body->makePrim(finalParts);
	bodyPrima->visited = true;
	bodyPrima->out(bodyPrima);
	bodyPrima->reset();
	return 0;
}