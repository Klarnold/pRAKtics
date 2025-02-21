#include<iostream>
#include<vector>
using namespace std;

class Tree {
private:
	string name; // уникальное имя листа
	int value; // значение листа

public:
	bool visited = false;
	vector<Tree*> elements; // список связяннах элементов листа

	//геттеры и сеттеры приватных данных
	void setName(string _name) { this->name = _name; }
	void setValue(int _value) { this->value = _value; }
	string getName() { return this->name; }
	int getValue() { return this->value; }

	// конструктор 
	Tree(string _name, int _value) {
		this->setName(_name);
		this->setValue(_value);
	}

	// добавить элемент в дерево
	void addElement(string _name, int _value, vector<string> elements_names) {
		Tree* newElement = new Tree(_name, _value);

		vector<Tree*> tempArray;
		tempArray.push_back(this);
		while (tempArray.size() != 0) {
			Tree* tempElement = tempArray[tempArray.size() - 1]; // берём элемент на рассмотрение

			tempElement->visited = true; // делаем элемент посещённым 
			for (string searched_name : elements_names) // ищем заданные элементы на связь
				if (tempElement->getName() == searched_name) {
					tempElement->elements.push_back(newElement);
					newElement->elements.push_back(tempElement);
					break;
				}


			tempArray.pop_back();
			for (Tree* obj : tempElement->elements) {
				if (!obj->visited)
					tempArray.push_back(obj);
			}
		}

		this->set_false();
	}

	// устанавливаем ложь везде
	void set_false() {
		
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	Tree* body = new Tree("A", 88);

	int value;
	string name;
	vector<string> elements;
	string tempName;
	cout << "Начинаем создание графа" << endl;
	while (name != "- 1") {
		tempName = "";
		cout << "Введите имя и значение ячейки через пробел (для остановки работы программы введите -1):" << endl;
		cin >> name;
		if (name == "- 1")
			break;
		cin >> value;

		cout << "Введите через пробел элементы, которые должны будут быть связаны с этой ячейкой (для остановки введите -1):" << endl;


		while (tempName != "-1") {
			cin >> tempName;
			elements.push_back(tempName);
		}

		body->addElement(name, value, elements);
	}

	return 0;
}