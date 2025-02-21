#include "Tree.h"

//������� � ������� ��������� ������
void Tree::setName(string _name) { this->name = _name; } 
void Tree::setValue(int _value) { this->value = _value; }
string Tree::getName() { return this->name; }
int Tree::getValue() { return this->value; }

// ����������� 
Tree::Tree(string _name, int _value) {
	this->setName(_name);
	this->setValue(_value);
}

// �������� ������� � ������
void Tree::addElement(string _name, int _value, vector<string> elements_names) {
	Tree* newElement = new Tree(_name, _value);

	vector<Tree*> tempArray;
	this->visited = true; // ������ ������� ���������� 
	tempArray.push_back(this);
	while (tempArray.size() != 0) {
		Tree* tempElement = tempArray[tempArray.size() - 1]; // ���� ������� �� ������������

		tempArray.pop_back();
		for (Tree* obj : tempElement->elements) {
			if (!obj->visited){
				obj->visited = true;
				tempArray.push_back(obj);
			}
		}

		for (string searched_name : elements_names) // ���� �������� �������� �� �����
			if (tempElement->getName() == searched_name) {
				tempElement->elements.push_back(newElement);
				newElement->elements.push_back(tempElement);
				break;
			}
	}

	this->reset();
}

void Tree::addElement(Tree* newElement, string headName) {
	Tree* elem = new Tree(newElement->getName(), newElement->getValue());
	Tree* tempElem;
	vector<Tree*> array;
	array.push_back(this);
	this->visited = true;
	while (array.size() != 0)
	{

		tempElem = array[array.size() - 1];
		tempElem->visited = true;
		array.pop_back();

		if (tempElem->getName() == headName)
		{
			tempElem->elements.push_back(elem);
			elem->elements.push_back(tempElem);
			break;
		}

		for (Tree* obj : tempElem->elements) {
			if (!obj->visited){
				obj->visited = true;
				array.push_back(obj);
			}
		}
	}

	this->reset();
}

// ������ ������ ��������� ��� ���������
void Tree::reset() {
	vector<Tree*>tempArray;

	tempArray.push_back(this);
	this->visited = false;
	while (tempArray.size() != 0) {
		Tree* tempElement = tempArray[tempArray.size() - 1]; // ���� ������� �� ������������

		tempArray.pop_back();

		for (Tree* obj : tempElement->elements) {
			if (obj->visited) {
				obj->visited = false;
				tempArray.push_back(obj);
			}
		}
	}
}

// ����� ������
void Tree::out(Tree* node) {

	cout << "|-" + node->getName() << endl;
	for (Tree* obj : node->elements)
		cout << "   |-" + obj->getName()<< endl;

	cout << "  ----  " << endl;
	for (int i = 0; i < node->elements.size(); i++)
	{
		if (!node->elements[i]->visited){
			node->elements[i]->visited = true;
			out(node->elements[i]);
		}
	}
}

// ������ �� ������ ������ �������� ������� �����
Tree* Tree::makePrim(int finalParts) {
	Tree* newTree = new Tree(this->getName(), this->getValue());
	this->setPart(true);
	int countParts = 1;
	vector<Tree*> parts;
	parts.push_back(this);
	Tree* currentPart;
	Tree* futurePart; 
	while (countParts != finalParts) {
		currentPart = new Tree("ERROR", 999);
		futurePart = new Tree("ERROR", 0);
		for (Tree* part : parts) {
			for (Tree* obj : part->elements) {
				if (  !obj->getPart() && (abs(part->getValue() - obj->getValue()) < abs(currentPart->getValue() - futurePart->getValue())))
				{
					futurePart = obj;
					currentPart = part;
				}
			}
		}

		futurePart->setPart(true);
		newTree->addElement(futurePart, currentPart->getName());

		countParts++;
		parts.push_back(futurePart);
	}

	return newTree;
}