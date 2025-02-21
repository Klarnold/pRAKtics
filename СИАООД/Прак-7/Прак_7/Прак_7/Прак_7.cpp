#include"Leaf.h"

void main() {
	setlocale(LC_ALL, "ru");

	Leaf* body = new Leaf(8.8, nullptr);

	double sum = 8.8;
	double tempValue = 0.0;
	cin >> tempValue;
	while (tempValue != -1){
		body->addValue(tempValue);
		sum += tempValue;
		cin >> tempValue;
	}

	cout << "------------" << endl <<
		sum << endl
		<< body->findTotalSum() << endl;


	cout << " ----- \"Программа для решения 7.1\" - v1.0 ----- " << endl;
	int choice = 0;
	while (true) {
		cout << "1 - Вывести на экран дерево | " << "2 - Удалить элемент по значению | " << "3 - Добавить элемент" << endl
			<< "4 - Вывести сумму дерева | " << "5 - Вывести среднее арифметическое дерева | " << " 6 - Сделать балансировку корня" << endl
			<< "7 - Найти ячейку по значению | " << "8 - Очистить консоль | " << "9 - завершить работу программы" << endl;
		cin >> choice;
		if (choice == 1) {
			body->printBT("", body, false);
		}
		else if (choice == 2) {
			cout << "Введите вещественное значение (пример: 0.0000...): " << endl;
			cin >> tempValue;
			Leaf* tempLeaf = body->deleteLeaf(tempValue);
			if (tempLeaf == nullptr)
			{
				cout << "Элемента со значением " << tempValue << " нет в дереве. Отмена удаления" << endl;
				continue;
			}
			if (tempLeaf->getHead() != nullptr) {
				tempLeaf->setHead(nullptr);
				delete tempLeaf;
			}
			else
			{
				if (tempLeaf->getValue() == 0)
				{
					body = tempLeaf->getLeft();
					tempLeaf->setLeft(nullptr);
					delete tempLeaf;
				}
				else if (tempLeaf->getValue() == 1)
				{
					body = tempLeaf->getRight();
					tempLeaf->setRight(nullptr);
					delete tempLeaf;
				}
				else
				{
					delete tempLeaf;
					body = nullptr;
					cout << "Прекращение работы программы: вы удалили корень" << endl;
					return;
				}
			}
		}
		else if (choice == 3) {
			cout << "Введите вещественное значение (пример: 0.0000...): " << endl;
			cin >> tempValue;
			body->addValue(tempValue);
		}
		else if (choice == 4) {
			cout << "Сумма дерева равна " << body->findTotalSum() << endl;
		}
		else if (choice == 5) {
			cout << "Среднее арифметическое дерева равно " << body->findTotalSum() / (body->rightLeftCount[0] + body->rightLeftCount[1] + 1) << endl;
		}
		else if (choice == 6) {
			cout << "Стабилизурием корень" << endl;
			body = body->changeRoot();
		}
		else if (choice == 7) {
			cout << "Введите искомое значение (пример: 0.000...):" << endl;
			cin >> tempValue;
			Leaf* tempLeaf = body->search(tempValue);
			if (tempLeaf == nullptr)
			{
				cout << "Элемента со значением " << tempValue << " нет в дереве. Отмена поиска" << endl;
				continue;
			}
			cout << tempLeaf->getValue() << endl;
		}
		else if (choice == 8) {
			system("CLS");
			cout << " ----- \"Программа для решения 7.1\" - v1.0 ----- " << endl;
		}
		else {
			cout << "Завершаем работу программы" << endl;
			break;
		}
	}
}