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

	//�������
	void setHead(Leaf* _head);
	void setRight(Leaf* _right);
	void setLeft(Leaf* _left);
	void setValue(double _value);

	//�������
	Leaf* getHead();
	Leaf* getRight();
	Leaf* getLeft();
	double getValue();

	//�����������
	Leaf(double _value, Leaf* _head);

	// ������� �������
	Leaf* deleteLeaf(double key);

	// �������� �������
	void addValue(double _value);

	//����� ����� ������
	double findTotalSum();

	//�������� ������
	Leaf* changeRoot();

	// ����� ������ �� ��������
	Leaf* search(double _value);

	//�������� ������
	Leaf* spinLeft();
	Leaf* spinRight();

	// ����� ������
	void printBT(string prefix, Leaf* node, bool isLeft);
};