#include<iostream>
#include<vector>
using namespace std;

class Leaf {
private:
	Leaf* right = nullptr;
	Leaf* left = nullptr;
	Leaf* head = nullptr;
	double value;
	bool righteous = false;

public:
	bool checked;
	int* rightLeftCount = new int[2] {0, 0};
	int rightLeft = 0;

	//сеттеры
	void setHead(Leaf* _head);
	void setRight(Leaf* _right);
	void setLeft(Leaf* _left);
	void setValue(double _value);

	//геттеры
	Leaf* getHead();
	Leaf* getRight();
	Leaf* getLeft();
	double getValue();

	//конструктор
	Leaf(double _value, Leaf* _head);

	// удалить элемент
	Leaf* deleteLeaf(double key);

	// добавить элемент
	void addValue(double _value);

	//найти сумму дерева
	double findTotalSum();

	//помен€ть корень
	Leaf* changeRoot();

	// поиск €чейки по значению
	Leaf* search(double _value);

	//повороты дерева
	Leaf* spinLeft();
	Leaf* spinRight();

	// вывод дерева
	void printBT(string prefix, Leaf* node, bool isLeft);
};