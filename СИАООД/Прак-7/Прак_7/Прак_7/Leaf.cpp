#include"Leaf.h"

//сеттеры
void Leaf::setHead(Leaf* _head) { this->head = _head; }
void Leaf::setLeft(Leaf* _left) { this->left = _left; }
void Leaf::setRight(Leaf* _right) { this->right = _right; }
void Leaf::setValue(double _value) { this->value = _value; }

//геттеры
Leaf* Leaf::getHead() { return this->head; }
Leaf* Leaf::getLeft() { return this->left; }
Leaf* Leaf::getRight() { return this->right; }
double Leaf::getValue() { return this->value; }

//конструктор
Leaf::Leaf(double _value,Leaf* _head) {
	setHead(_head);
	setValue(_value);
	this->checked = false;
}

// поиск ячейки по зачению
Leaf* Leaf::search(double _value) {
	Leaf* tempLeaf = this;
	while (tempLeaf != nullptr) {
		if (_value == tempLeaf->getValue()) {
			return tempLeaf;
		}
		if (_value > tempLeaf->getValue()) {
			if (tempLeaf->getRight() == nullptr)
				return nullptr;
			tempLeaf = tempLeaf->getRight();
		}
		else
		{
			if (tempLeaf->getLeft() == nullptr)
				return nullptr;
			tempLeaf = tempLeaf->getLeft();
		}
	}
}

//добавить элемент
void Leaf::addValue(double _value){
	if (_value > this->getValue()) {
		this->rightLeftCount[1]++;
		if (this->getRight() == nullptr)
		{ 
			this->setRight(new Leaf(_value, this));
			this->getRight()->rightLeft = 1;
		}
		else
			this->getRight()->addValue(_value);
	}
	else
	{
		this->rightLeftCount[0]++;
		if (this->getLeft() == nullptr){
			this->setLeft(new Leaf(_value, this));
			this->getLeft()->rightLeft = 0;
		}
		else
			this->getLeft()->addValue(_value);
	}
}

// удалить элемент
Leaf* Leaf::deleteLeaf(double _value) {
	Leaf* tempLeaf = this->search(_value);

	if (tempLeaf == nullptr)
		return nullptr;

	if (tempLeaf->getHead() == nullptr) { // мы изменим значение root так, что 0 - root переходит к левому элементу, 1 - root переходит к правому элементу, 2 - root не переходить ни к кому
		if (tempLeaf->getLeft() == nullptr && tempLeaf->getRight() == nullptr)
		{
			tempLeaf->setValue(2);
		}
		else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() == nullptr)
		{
			tempLeaf->setValue(0);
			tempLeaf->getLeft()->setHead(nullptr);
		}
		else if (tempLeaf->getLeft() == nullptr && tempLeaf->getRight() != nullptr)
		{
			tempLeaf->setValue(1);
			tempLeaf->getRight()->setHead(nullptr);
		}
		else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() != nullptr)
		{
			tempLeaf->setValue(1);
			Leaf* tempRightLeaf = tempLeaf->getRight();
			tempRightLeaf->rightLeftCount[0] += tempLeaf->rightLeftCount[0];
			while (tempRightLeaf->getLeft() != nullptr) {
				tempRightLeaf = tempRightLeaf->getLeft();
				tempRightLeaf->rightLeftCount[0] += tempLeaf->rightLeftCount[0];
			}

			tempRightLeaf->setLeft(tempLeaf->getLeft());
			tempLeaf->getLeft()->setHead(tempRightLeaf);
			tempLeaf->setLeft(nullptr);
			tempLeaf->getRight()->setHead(nullptr);
		}
		return tempLeaf;
	}
	else {
		Leaf* tempHead = tempLeaf->getHead();
		int right = tempLeaf->rightLeft;
		while (tempHead != nullptr) {
			tempHead->rightLeftCount[right]--;
			right = tempHead->rightLeft;
			tempHead = tempHead->getHead();
		}
		if (tempLeaf->getLeft() == nullptr && tempLeaf->getRight() == nullptr)
		{
			if (tempLeaf->rightLeft == 0)
				tempLeaf->getHead()->setLeft(nullptr);
			else
				tempLeaf->getHead()->setRight(nullptr);
		}
		else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() == nullptr)
		{
			if (tempLeaf->rightLeft == 0)
				tempLeaf->getHead()->setLeft(tempLeaf->getLeft());
			else
				tempLeaf->getHead()->setRight(tempLeaf->getLeft());
			tempLeaf->getLeft()->setHead(tempLeaf->getHead());
		}
		else if (tempLeaf->getLeft() == nullptr && tempLeaf->getRight() != nullptr)
		{
			if (tempLeaf->rightLeft == 0)
				tempLeaf->getHead()->setLeft(tempLeaf->getRight());
			else
				tempLeaf->getHead()->setRight(tempLeaf->getRight());
			tempLeaf->getRight()->setHead(tempLeaf->getHead());
		}
		else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() != nullptr)
		{
			if (tempLeaf->rightLeft == 0)
				tempLeaf->getHead()->setLeft(tempLeaf->getRight());
			else
				tempLeaf->getHead()->setRight(tempLeaf->getRight());

			Leaf* tempRightLeaf = tempLeaf->getRight();
			while (tempRightLeaf->getLeft() != nullptr)
			{
				tempRightLeaf->rightLeftCount[0] += tempLeaf->rightLeftCount[0];
				tempRightLeaf = tempRightLeaf->getLeft();
			}
			tempLeaf->getRight()->setHead(tempLeaf->getHead());
			tempLeaf->getLeft()->setHead(tempRightLeaf);
			tempRightLeaf->setLeft(tempLeaf->getLeft());

		}
		tempLeaf->setRight(nullptr);
		tempLeaf->setLeft(nullptr);
		return tempLeaf;
	}
}

// найти сумму дерева
double Leaf::findTotalSum() {
	double sum = 0;

	int state = 0; // список сотояний: 0 - идём налево, 1 - идём направо, 2 - идём вверх, -1 - прекращение работы программы

	Leaf* tempLeaf = this;
	while (tempLeaf!=nullptr)
	{
		if (state == 0)
		{
			if (tempLeaf->getLeft() == nullptr) {
				if (tempLeaf->checked == false){
					sum += tempLeaf->getValue();
					tempLeaf->checked = true;
				}
				state = 1;
			}
			else {
				if (tempLeaf->getLeft()->checked) {
					if (tempLeaf->getRight() == nullptr) {
						if (tempLeaf->checked == false){
							sum += tempLeaf->getValue();
							tempLeaf->checked = true;
						}
						state = 2;
					}
					else{
						if (tempLeaf->getRight()->checked == false)
						{ 
							if (tempLeaf->checked == false) {
								sum += tempLeaf->getValue();
								tempLeaf->checked = true;
							}
							state = 1;
						}
						else {
							state = 2;
						}
					}
				}
				else {
					tempLeaf = tempLeaf->getLeft();
				}
			}
		}
		else if (state == 1) {
			if (tempLeaf->getRight() == nullptr) {
				state = 2;
			}
			else {
				if (tempLeaf->getRight()->checked == false){
					tempLeaf = tempLeaf->getRight();
					state = 0;
				}
				else {
					state = 2;
				}
			}
		}
		else {
			if (tempLeaf->getLeft() == nullptr && tempLeaf->getRight() == nullptr) {
				if (tempLeaf->getHead() == nullptr) {
					tempLeaf->checked = false;
					break;
				}
				tempLeaf = tempLeaf->getHead();
				if (tempLeaf->checked == false) {
					sum += tempLeaf->getValue();
					tempLeaf->checked = true;
				}
			}
			else if ( tempLeaf->getLeft() == nullptr && tempLeaf->getRight() != nullptr) {
				if (tempLeaf->getRight()->checked) {
					tempLeaf->getRight()->checked = false;
					tempLeaf = tempLeaf->getHead();
					state = 0;
				}
				else {
					state = 0;
				}
			}
			else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() == nullptr) {
				if (tempLeaf->getLeft()->checked == false) {
					state = 0;
				}
				else {
					tempLeaf->getLeft()->checked = false;
					if (tempLeaf->getHead() == nullptr)
						break;
					tempLeaf = tempLeaf->getHead();
					if (tempLeaf->checked == false) {
						sum += tempLeaf->getValue();
						tempLeaf->checked = true;
					}
					state = 0;
				}
				
			}
			else if (tempLeaf->getLeft() != nullptr && tempLeaf->getRight() != nullptr) {
				if (tempLeaf->getRight()->checked == false)
					state = 1;
				else {
					tempLeaf->getRight()->checked = false;
					tempLeaf->getLeft()->checked = false;
					tempLeaf = tempLeaf->getHead();
					if (tempLeaf != nullptr && tempLeaf->checked == false) {
						sum += tempLeaf->getValue();
						tempLeaf->checked = true;
					}
				}
			}
		}
	}

	this->checked = false;
	return sum;
}

// балансировка
Leaf* Leaf::changeRoot() {
	Leaf* tempLeaf = this;
	int* tempCount = tempLeaf->rightLeftCount;
	if (abs(tempLeaf->rightLeftCount[0] - tempLeaf->rightLeftCount[1]) < 2){
		cout << "Не нужна балансировка" << endl;
		return this;
	}

	if (tempLeaf->rightLeftCount[1] > tempLeaf->rightLeftCount[0])
	{
		return this->spinLeft();
	}
	else
	{
		return this->spinRight();
	}

	cout << "Не получилась балансировка" << endl;
}

// поворот налево
Leaf* Leaf::spinLeft() {
	Leaf* tempRoot = this->getRight();
	tempRoot->rightLeftCount[0] += this->rightLeftCount[0] + 1;
	this->rightLeft = 0;
	Leaf* tempLeft = tempRoot;

	while (tempLeft->getLeft() != nullptr) {
		tempLeft = tempLeft->getLeft();
		tempLeft->rightLeftCount[0] += this->rightLeftCount[0] + 1;
	}

	tempLeft->setLeft(this);
	this->setHead(tempLeft);
	this->rightLeftCount[1] = 0;
	this->setRight(nullptr);
	tempRoot->rightLeft = 0;
	tempRoot->setHead(nullptr);
	return tempRoot;
}

// поворот направо
Leaf* Leaf::spinRight() {
	Leaf* tempRoot = this->getLeft();
	this->rightLeft = 1;
	this->rightLeftCount[0] = tempRoot->rightLeftCount[1];
	this->setLeft(tempRoot->getRight());
	this->setHead(tempRoot);
	if (tempRoot->getRight() != nullptr) {
		tempRoot->getRight()->setHead(this);
	}

	tempRoot->setHead(nullptr);
	tempRoot->setRight(this);
	tempRoot->rightLeft = 0;
	tempRoot->rightLeftCount[1] = this->rightLeftCount[0] + this->rightLeftCount[1] + 1;

	return tempRoot;
}

// вывод дерева
void Leaf::printBT(string prefix, Leaf* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "--" : "|-");

		// print the value of the node
		cout << node->getValue() << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), node->getRight(), true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->getLeft(), false);
		
	}
}
