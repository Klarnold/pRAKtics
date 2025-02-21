#include "Deck.h"
#include<bitset>
#include<ctime>
#include<fstream>
#include <random>
#include<string>
using namespace std;

void main() {
	setlocale(LC_ALL, "Russian");
	/*unsigned char a = 255;
	unsigned char mask = 1;
	a = a & ~(mask << 4);
	cout << int(a) << endl;*/

	/*unsigned char id = 300;
	unsigned char mask = 1;
	id = id | (mask << 6);
	cout << int(id) << endl;*/

	
	unsigned int x = 25;
	const int n = sizeof(int) * 8; //=32 - кол-во разрядов в чисе типа int
	unsigned mask = (1 << n - 1); //1 в старшем бите 32-разрядной сетки
	cout << "Начальный вид маски: " << bitset<n>(mask) << endl; // bitset - хранит битовые значения
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) // 32 раза по кол-ву разрядов
	{
		cout << ((x & mask) >> (n - i));
		mask = mask >> 1; //смещение 1 в маске на разрял вправо
	}
	cout << endl 
		<<  n << endl
		<< sizeof(int);


	/*int count = 0;
	int temp=0;
	unsigned char mask = 1;
	unsigned char list = 0;
	cout << "Введите произвольные цифры (от 0 до 7) в кол-ве не более 8 штук"<<endl
		<< "Для прекращения ввода чисел введите 8" << endl;
	while (count < 8){
		cin >> temp;
		if (temp == 8){
			break;
		}
		else if (temp <= 7 and temp >= 0){
			list = list | (mask << (7 - temp));
			count++;
		}
		else {
			cout << "Число введено некорректно, повторите ввод" << endl;
		}
	}

	//cout << int(list) << endl;

	mask = mask << 7;

	for (int i = 0; i<8; i++) {
		cout << ((list & mask) >> (7 - i));
		mask = mask >> 1;
	}
	*/
	srand(time(nullptr));

	int tempor =pow(10, 7);
	//int* sp = new int[pow(10, 7)];
	//int schet = 0;
	//int num;

	/*
	while (schet != (tempor / 100)) {
		num = rand() % tempor / 100;
		sp[schet] = num;
		int i = 0;
		for (; i < schet; i++)
		{
			if (sp[i] == num)
				break;
		}
		if (i == schet)
		{
			writer << num << endl;
			schet++;
		}
	}
	writer.close();
	*/



/*
	cout << "Введите желаемые числа (для прекращения работы ввода введите -1): " << endl;
	while (true){
		int temp;
		cin >> temp;
		if (temp == -1)
			break;
		
		for (int i = 0; i < (temp / 8); i++) {
			if (ls->next == nullptr)
			{
				ls->next = new Deck(0);
			}

			ls = ls->next;
			ls->make_first(first);
		}

		temp %= 8;
		unsigned char tempo =  (ls->core | (mask << temp));
		ls->change_core(tempo);
		ls = ls->first;
	}
	
	for (int j = 0; j < 3; j++) {
		mask = mask << 7;
		for (int i = 0; i < 8; i++) {
			cout << (((ls->core) & mask) >> (7 - i));
			mask = mask >> 1;
		}
		mask = 1;
		cout << endl;
		ls = ls->next;
	}
	*/

	
	ifstream reader;
	reader.open("numList.txt");
	
	ofstream writer("numList.txt");
	
	for (int i = 0; i < pow(10, 7); i++)
	{
		writer << rand() % tempor << endl;
	}
	writer.close();
	
	unsigned char mask = 1;

	int temp;
	string st;
	unsigned char* sp = new unsigned char[pow(10, 6) * 1.25];
	int sec = time(NULL);
	int id;
	cout << sec << endl;
	for (int k = 0; k < pow(10, 7); k++) {
		mask = 1;
		reader >> st;
		temp = 0;
		for (int i = 0; i < st.size(); i++)
		{
			temp += ((int)st[i] - 48) * pow(10, st.size() - i - 1);
		}
		
		id = temp / 8;
		sp[id] = sp[id] | (mask << (temp % 8));


	}
	
	cout <<"Было затрачено " << time(NULL) - sec << " секунд на сортировку" << endl
		 << "Массив весит " << sizeof(sp) * pow(10, 6) * 1.25 / 1024 / 1024 / 8 << " Мбайт" << endl;
	reader.close();
	
}