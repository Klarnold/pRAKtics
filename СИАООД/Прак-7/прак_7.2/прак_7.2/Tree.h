#include<iostream>
#include<vector>
using namespace std;

class Tree {
private:
	string name; // уникальное им€ листа
	int value; // значение листа
	bool part = false; // €вл€етс€ ли объект частью дерева ѕрима
protected:
	void setName(string _name);// здесь защищЄнный тип данных, так как не желательно позвол€ть пользователю после задани€ измен€ть значение пол€ name
	void setPart(bool _part) { this->part = _part; }
	bool getPart() { return this->part; }
public:
	bool visited = false; // посещЄн ли был данный элемент
	vector<Tree*> elements; // список св€з€ннах элементов листа

	

	//геттеры и сеттеры приватных данных
	void setValue(int _value);
	int getValue();

	string getName();

	// добавить элемент в дерево
	void addElement(string _name, int _value, vector<string> elements_names);

	// переопределение дл€ простоты
	void addElement(Tree* newElement, string headName);

	// конструктор 
	Tree(string _name, int _value);

	// вывод дерева
	void out(Tree* node);

	// делаем дерево доступным дл€ изменений
	void reset();

	// делаем из нашего дерева остовное методом ѕрима
	Tree* makePrim(int finalParts);
};