#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<iterator>
#include<algorithm>
using namespace std;

int convertToInt(string numStr) { // преобразование строк в числа
	int tempNum = 0;
	for (int i = 0; i < numStr.size(); i++)
		tempNum += ((int)numStr[i] - 48) * pow(10, numStr.size() - i - 1);
	return tempNum;
}

class hashClass {
public:
	int arrSize = 10;
	int* arrKey = new int [arrSize]; // хранит захешированные ключи
	string* arrUsefulInf = new string[arrSize]; // хранит полезную информацию

	void del(int key, int collInd=-1) { // удаляет элемент по ключу
		int tempInd = search(key, collInd);

		cout << "Вы удалили " << this->arrUsefulInf[tempInd] << endl;
		arrKey[tempInd] = -1;
		arrUsefulInf[tempInd] = "";
	}

	int search(int key, int collInd=-1) // ищет индекс полезной информации по ключу
	{
		if (collInd == -1)
		{
			for (int i = 0; i < arrSize; i++)
			{
				if (arrKey[i] == key)
				{
					return i;
					cout << "Вы нашли " << arrUsefulInf[i] << endl;
				}
			}
		}
		else
		{
			int stInd=0;
			for (int i = 0; i < arrSize; i++)
			{
				if (arrKey[i] == key)
				{
					stInd = i;
					break;
				}
			}

			cout << "Вы нашли " << arrUsefulInf[stInd + 7 * collInd] << endl;
			return stInd + 7*collInd;
		}
	}



	void add(string fullInformation) { // добавляем элемент в список
		int tempKey =hashFunc(convertToInt(fullInformation.substr(0, 6)));

		int collisionInd = collisionManager(tempKey);

		if (collisionInd == -1) {
			for (int i = 0; i < arrSize; i++)
			{
				if (arrKey[i] == -1)
				{
					if (i >= 3 * arrSize / 4)
						this->arrReHash();
					arrKey[i] = tempKey;
					arrUsefulInf[i] = fullInformation;
					return;
				}
			}
		}

		while (arrKey[collisionInd] != -1)
		{
			collisionInd += 7;
			if (3 * (this->arrSize) / 4 <= collisionInd)
				this->arrReHash();
		}

		arrKey[collisionInd] = tempKey;
		arrUsefulInf[collisionInd] = fullInformation;
	}

	hashClass(){ // конструктор класса
		for (int i = 0; i < 10; i++)
		{
			arrKey[i] = -1;
		}
		
	}

	int collisionManager(int key) { // метод нахождения свободного места  в случае коллизии
		int c = 7;
		int i = 0;
		int stInd = -1;
		for (int j = 0; j < this->arrSize; j++)
		{
			if (this->arrKey[j] == key){
				stInd = j;
				break;
			}
		}
		if (stInd == -1)
			return -1;
		while (true) {
			if (3 * (this->arrSize) / 4 <= (c * i + stInd))
				this->arrReHash();
			if (this->arrKey[c * i + stInd] == key && arrKey[c * i + stInd]!=-1)
				i++;
			else
				return c * i + stInd;
		}
	}

	void arrReHash() { // рехеширование тыблицы и массива
		this->arrSize *= 2;
		//int* tempMiniArr = new int[2];
		string* tempArrUsefulInf = new string [this->arrSize];
		int* tempArrKey = new int[this->arrSize];
		for (int i = 0; i < this->arrSize / 2; i++)
		{
			tempArrUsefulInf[i] = this->arrUsefulInf[i];
			tempArrKey[i] = this->arrKey[i];
		}
		for (int i = this->arrSize / 2; i < this->arrSize; i++)
		{
			tempArrKey[i] = -1;
		}
		delete[] this->arrKey;
		delete[] this->arrUsefulInf;
		this->arrKey = tempArrKey;
		this->arrUsefulInf = tempArrUsefulInf;
	}

	void outArr() { // вывод на экран содержимого хеш-таблицы и массива с полезной информацией
		for (int i = 0; i < this->arrSize; i++)
		{
			cout << this->arrKey[i] << " | " << this->arrUsefulInf[i] << endl;
		}
	}

	int hashFunc(int num) { // хеш-функция (делает магию)
		return (num % 100 + (num / 100) % 100) % 100;
	}
};

void main() {
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	ofstream writer("t.txt");
	
	int temp;
	string tempText = "";

	//st генерация txt файла
	int n = 17; // кол-во строк в txt файле
	for (int i=0; i < n; i++)
	{
		tempText = "";
		temp = rand() % 100000 + 100000;
		writer << temp << ' ';
		for (int j = 0; j < (rand() % 6 + 3); j++)
		{
			if (j == 0)
				writer << (char)(rand() % 26 + 65);
			else
				writer << (char)(rand() % 26 + 97);
		}
		writer << ' ' << rand() % 101 + 100 << '\n';

	}
	writer.close();

	//end генерация txt файла
	hashClass* h = new hashClass();

	//st считывание чисел из txt и их запись в bin
	ifstream reader("t.txt");
	ofstream writerBin("t.bin", ios_base::binary);

	
	for (int i = 0; i < n; i++) {
		getline(reader, tempText);
		h->add(tempText);
		tempText = tempText.substr(0, 6);
		temp = 0;
		for (int j = 0; j < tempText.size(); j++)
			temp += ((int)tempText[j] - 48) * pow(10, tempText.size() - j -1);
		writerBin.write((char*)&temp, sizeof(temp));
	}
	
	writerBin.close();
	//st считывание чисел из txt и их запись в bin



	ifstream readerBin("t.bin", ios_base::binary);
	for (int i = 0; i < n; i++) {
		readerBin.read((char*)&temp, sizeof(int));
	//	cout << temp << endl;
	}
	
	readerBin.close();
	reader.close();

	//h->outArr();
	cout << "----- Добро пожаловать в нашу программу! -----" << endl;
	while (true) {
		
		string tempText;
		

		cout << "1 - Вывести на экран список\t2 - Удалить элемент по ключу\t3 - Добавить элемент\n4 - Найти элемент по ключу\t5 - Очистить консоль\t6 - Завершить работу программы" << endl;
		
		getline(cin, tempText);
		if (tempText == "1") {
			h->outArr();
		}
		else if (tempText == "2") {
			cout << "Удаляйте по шаблону - \"00(ключ) 000....(индекс коллизии)\"" << endl;
			getline(cin, tempText);
			int tempKey = convertToInt(tempText.substr(0, 2));
			int tempColl = convertToInt(tempText.substr(3, h->arrSize-3));
			h->del(tempKey, tempColl);
		}
		else if (tempText == "3") {
			cout << "Добавляйте элемент по шаблону:" << endl
				<< "000000(шестизначное число) ааааа...(слово n-ой длины) 000(треёхзначное число)" << endl;
			getline(cin, tempText);
			h->add(tempText);
		}
		else if (tempText == "4"){
			cout << "Ищите по шаблону - \"00(ключ) 000....(индекс коллизии)\"" << endl;
			getline(cin, tempText);
			int tempKey = convertToInt(tempText.substr(0, 2));
			int tempColl = convertToInt(tempText.substr(3, h->arrSize - 3));
			h->search(tempKey, tempColl);
		}
		else if (tempText == "5") {
			system("CLS");
			cout << "----- Добро пожаловать в нашу программу! -----" << endl;
		}
		else if (tempText == "6") {
			cout << "Завершение работы программы" << endl;
			break;
		}
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

	}
	/*
	cout << "-------------" << endl;
	h->arrReHash();
	h->outArr();
	cout << "-------------" << endl;
	h->arrReHash();
	h->outArr();*/
}