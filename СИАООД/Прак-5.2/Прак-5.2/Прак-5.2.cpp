#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<chrono>

using namespace std;

int compare(const void* x1, const void * x2) {
	//cout << (*(int*)x1 - *(int*)x2) << endl;
	return (*(int*)x1 - *(int*)x2);
}

int searchLink(int* ar, int* arL, int size, int key) {
	int tempS = size/2;
	int prev = tempS;
	int tempPrev;
	if (ar[tempS] == key)
		return arL[tempS];
	else if (ar[tempS] > key)
		tempS -= tempS / 2;
	else
		tempS += (size - tempS) / 2;
	while (true) {
		tempPrev = tempS;
		if (ar[tempS] == key)
			return arL[tempS];
		else if (ar[tempS] > key){
			tempS -= abs(tempS - prev) / 2;
			if (tempPrev == prev)
				tempS--;
		}
		else{
			tempS += abs(tempS - prev) / 2;
			if (tempPrev == prev)
				tempS++;
		}
		prev = tempPrev;
	}
	return -1;
}

void static make(ofstream* writer, char* sp) {

	int temp = rand() % 10000000 + 10000000;
	writer->write((char*)&temp, sizeof(int));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++) {
			sp[j] = (char)-52;
		}
		temp = rand() % 3 + 3;
		for (int j = 0; j < 5; j++)
		{
			if (sp[0] == (char)-52)
				sp[j] = (char)(rand() % 26 + 65);
			else
				sp[j] = (char)(rand() % 26 + 97);
		}
		writer->write(sp, sizeof(sp));
	}
}

void spOut(char* sp) {
	for (int i = 0; i < 10; i++) {
		if (sp[i] == -52)
			break;
		else
			cout << sp[i];
	}
}
int convert(string num) {
	int temp = 0;
	for (int i = 0; i < num.size(); i++)
		temp += ((int)num[i] - 48) * pow(10, num.size()-i-1);
	return temp;
}

/* неудачная идея
int long convertString(string str) {
	int temp = int(str[0]);
	for (int i = 1; i < str.size(); i++)
	{
		if ((int)str[i] / 100 == 1)
			temp = temp * pow(10, 3) + (int)str[i];
		else
			temp = temp * pow(10, 2) + (int)str[i];
	}
	return temp;
}
*/
string static schet(ifstream* reader) {
	srand(time(NULL));
	string temp = "";
	string output;
	if (reader->eof())
		return temp;
	while (true) {
		temp = reader->get();
		if (temp[0] == ' ' or temp[0] == '\n' or reader->eof())
			break;
		else
			output.append(temp);
	}
	return output;
}


void main(){
	setlocale(LC_ALL, "Russian");
//write
	/*
	string temp = "aboba";
	int tempor;
	ofstream writer("file.bin", ios_base::binary);
	for (int i = 0; i < temp.size(); i++)
	{
		tempor = (int)temp[i];
		writer.write((char*)&tempor, sizeof(int));
	}
	
	writer.close();
//read
	int const tmpor = temp.size();
	string temp1;
	ifstream reader("file.bin", ios_base::binary);
	reader.read((char*)&temp1, temp.size());

	string temporary;
	for (int i = 0; i < temp.size(); i++)
	{
		reader.read((char*)&tempor, sizeof(int));
		temporary = (char)tempor;
		temp1.append(temporary);
	}


	reader.close();
	
//out

	for (int i = 0; i < temp.size(); i++) {
		cout << temp[i];
	}
	cout << endl;

	for (int i = 0; i < temp.size(); i++) {
		cout << temp1[i];
	}
	cout << endl;
	*/


	/*
	string x = "asdfghkjgfefsdghbnb";
	ofstream writer("txt.bin", ios_base::binary);
	writer.write((char*)&x, sizeof(string));
	writer.close();

	string a;

	ifstream reader("txt.bin", ios_base::binary);
	reader.read((char*)&a, sizeof(string));
	cout << a << endl;
	*/

	//запись строк в bin
	/*
	ifstream reader("file.txt"); 
	ofstream writer("file.bin", ios_base::binary);
	string temp;
	int tempNum;
	for (int i = 0; i < 12; i++) {
		temp = schet(&reader);
		if (temp == "")
			break;
		tempNum = convert(temp);
		writer.write((char*)&tempNum, sizeof(int));
	}
	reader.close();
	*/

	// генерация строк
/*	ofstream f("file.txt");
	cout << "its ok " << endl;

	for (int i = 0; i < 10; i++) {
		int temp = rand() % 10000000 + 10000000;
		f << temp << ' ' << "fio " << "ad\n";
	}
	f.close();
	*/
	//writer.close();
	/*
	int tempNum;
	ifstream binReader("file.bin", ios_base::binary);
	string str;
	*/
	/*for (int i = 0; i < 10; i++)
	{
		//binReader.read((char*)&tempNum, sizeof(int));
		binReader.read((char*)&tempNum, sizeof(int));
		cout << tempNum << ' ';
		binReader.read((char*)&tempNum, sizeof(int));
		cout << tempNum << endl;
	}*/
	/*
	binReader.seekg(sizeof(int)*2);
	binReader.read((char*)&tempNum, sizeof(int));
	cout << tempNum << endl;
	binReader.seekg(sizeof(int) * 2);
	binReader.read((char*)&tempNum, sizeof(int));
	cout << tempNum << endl;
	binReader.close();
	*/
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	ofstream writerBin("file.bin", ios_base::binary);
	ifstream reader("file.txt");
	int temp;
	string tempStr;
	char sp[5];
	for (int i=0; i<10; i++){ 
		for (int j = 0; j < 5; j++)
		{
			tempStr = schet(&reader);
			if (tempStr == "")
				break;

			if (j == 0){
				temp = convert(tempStr);
				writerBin.write((char*)&temp, sizeof(int));
			}
			else{
				for (int i = 0; i < 5; i++)
					if (i < tempStr.size())
						sp[i] = tempStr[i];
					else
						sp[i] = (char)-52;
				writerBin.write(sp, sizeof(sp));
			}
		}
	}

	//cout << endl;
	writerBin.close();
	ifstream readerBin("file.bin", ios_base::binary);
	string st;
	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++)
		{
			if (j == 0)
			{
				readerBin.read((char*)&temp, sizeof(int));
				cout << temp << ' ';
			}
			else {
				for (int i = 0; i < 10; i++)
					sp[i] = (char)-52;
				readerBin.read(sp, sizeof(sp));
				if (j != 4) {
					spOut(sp);
					cout << ' ';
				}
				else {
					spOut(sp);
					cout << '\n';
				}

			}
		}
	}*/

	/*
	for (int j = 0; j < 10; j++)
	{
		readerBin.read((char*)&temp, sizeof(int));
		cout << temp << ' ';
		for(int i = 0; i<4; i++)
			readerBin.read(sp, sizeof(sp));
	}
	*/

	readerBin.close();

	ifstream r("file.txt");
	
	ofstream wrBin("b.bin", ios_base::binary);
	int sear = 10;
	for (int i = 0; i < (sear - 1); i++)
	{

		int temp = rand() % 10000000 + 10000000;
		wrBin.write((char*)&temp, sizeof(temp));
		
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 5; j++) {
				sp[j] = (char)-52;
			}
			temp = rand() % 3 + 2;
			for (int j = 0; j < temp; j++)
			{
				if (sp[0] == (char)-52)
					sp[j] = (char)(rand() % 26 + 65);
				else
					sp[j] = (char)(rand() % 26 + 97);
			}
			wrBin.write(sp, sizeof(sp));
		}
	}


	temp = 30000000;
	wrBin.write((char*)&temp, sizeof(temp));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++) {
			sp[j] = (char)-52;
		}
		temp = rand() % 3 + 2;
		for (int j = 0; j < temp; j++)
		{
			if (sp[0] == (char)-52)
				sp[j] = (char)(rand() % 26 + 65);
			else
				sp[j] = (char)(rand() % 26 + 97);
		}
		wrBin.write(sp, sizeof(sp));
	}




	wrBin.close();
	ifstream rBin("b.bin", ios_base::binary);
	int* ar = new int[sear];
	 //если надо будет убедиться в правильности вывода из бинарного файла
	/*for (int i = 0; i < 10; i++) {
		if (i%5 == 0) {
			rBin.read((char*)&temp, sizeof(temp));
			cout << temp << ' ';
		}
		else {
			for (int j = 0; j < 5; j++)
				sp[j] = (char)-52;
			rBin.read(sp, sizeof(sp));
			cout << sp << ' ';
		}

	}*/
	int goal = 30000000;
	int* arL = new int[sear];
	int* arK = new int[sear];

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < sear; i++)
	{
		rBin.read((char*)&temp, sizeof(int));
		ar[i] = temp;
		arK[i] = temp;
		if (temp == goal)
			break;
		for (int j = 0; j < 4; j++)
			rBin.read(sp, sizeof(sp));
	}

	//auto end = chrono::high_resolution_clock::now();

	//chrono::duration<double> time = end - start;

	//cout << "Линейный поиск за " << time.count() << " секунд" << endl;

	qsort(ar, sear, sizeof(int), compare);
	for (int i = 0; i < sear; i++) {
		cout << ar[i] << " ---- " << arK[i] << " ---- " << arL[i] << endl;
	}
	
	for (int i = 0; i < sear; i++) {
		for (int j = 0; j < sear; j++) {
			if (ar[i] == arK[j]) {
				arL[i] = j;
				break;
			}
		}
	}
	
	int poisk = sear-1;
	//auto start = chrono::high_resolution_clock::now();
	
	// поиск ключа по ссылке
	rBin.seekg(poisk* (sizeof(int) + sizeof(sp) * 4));
	rBin.read((char*)&temp, sizeof(int));
	


	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> time = end - start;

	cout << "Найдено " << arK[searchLink(ar, arL, sear, ar[5])] << endl
		<< ar[0] << endl
		<< "За " << time.count() << " секунд" << endl;


	//rBin.seekg(-5 * (sizeof(int) + 4 * sizeof(sp)));
	//rBin.seekg(2 * (sizeof(int) + 4 * sizeof(sp)));
//	rBin.read((char*)&temp, sizeof(int));
	//cout << temp  << endl;
	rBin.close();

	for (int i = 0; i < sear; i++) {
		cout << ar[i] << " ---- " << arL[i]  << " ---- " << arK[i] << endl;
	}
}