#include<iostream>
#include<vector>
using namespace std;

class Tree {
private:
	string name; // ���������� ��� �����
	int value; // �������� �����
	bool part = false; // �������� �� ������ ������ ������ �����
protected:
	void setName(string _name);// ����� ���������� ��� ������, ��� ��� �� ���������� ��������� ������������ ����� ������� �������� �������� ���� name
	void setPart(bool _part) { this->part = _part; }
	bool getPart() { return this->part; }
public:
	bool visited = false; // ������� �� ��� ������ �������
	vector<Tree*> elements; // ������ ��������� ��������� �����

	

	//������� � ������� ��������� ������
	void setValue(int _value);
	int getValue();

	string getName();

	// �������� ������� � ������
	void addElement(string _name, int _value, vector<string> elements_names);

	// ��������������� ��� ��������
	void addElement(Tree* newElement, string headName);

	// ����������� 
	Tree(string _name, int _value);

	// ����� ������
	void out(Tree* node);

	// ������ ������ ��������� ��� ���������
	void reset();

	// ������ �� ������ ������ �������� ������� �����
	Tree* makePrim(int finalParts);
};