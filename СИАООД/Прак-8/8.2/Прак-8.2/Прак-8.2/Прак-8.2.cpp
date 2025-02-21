#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

struct cell {
	int* matrix = nullptr;
	string brackets = "";
};

void out(vector<cell*>* matrix_array) {
	bool brackets_time = true;
	for (cell* object : *matrix_array) {
		if (brackets_time){
			cout << ' ' << object->brackets << ' ';
		}
		else{
			cout << object->matrix[0] << "x" << object->matrix[1];
		}
		brackets_time = !brackets_time;
	}
	cout << endl;
}


bool check_validation(vector<vector<int>> listOf_start_end, int st, int end)
{
	for (int end_value : listOf_start_end[st])
		if (end_value == end)
			return false;
	return true;
}

void make_matrix_array_min(vector<cell*>* matrix_array, int* schet) {  // динамически изменяем массив матриц
	vector<vector<int>> listOf_start_end;
	for (int i = 0; i < matrix_array->size(); i++)
	{
		vector<int> k;
		k.push_back(-1);
		listOf_start_end.push_back(k);
	}

	for (int ammount_of_checks = 0; ammount_of_checks < matrix_array->size()/2; ammount_of_checks++){ // сколько раз проводим проверку
		int st = 0; // начало скобок
		int end = 0; // конец скобок
		int temp_st = 0; // вариант начала скобок
		int temp_end = 0; // вариант конца скобок
		int pos = 0; // счётчик позиции
		int min_ammount_of_multiply = pow(10, 6);
		int right_bracket_count = 0; // счёт правых скобок для правильных рассчётов "("
		int left_bracket_count = 0; // счёт левых скобок для правильных рассчётов ")"
		int right_bracket_previous = right_bracket_count;
		int left_bracket_previous = left_bracket_count;
		bool first_brackets = false;
		int* tempMatrix_first = new int[2] {0, 0};
		int* tempMatrix_second = new int[2] {0, 0};
		int bracket_state =0; // 0 - нет скобок, 1 - идут скобки, 2 - закончились скобки
		bool bracket_time = true; // черёд скобок в массиве?
		int matrix_count = 0;
		for (cell* object : *matrix_array) {
			schet[0]++;
			if (bracket_time) // проверка скобок
			{
				if (right_bracket_count == left_bracket_count && matrix_count == 2 && check_validation(listOf_start_end, temp_st, pos)) {
					if (tempMatrix_first[0] * tempMatrix_second[1] < min_ammount_of_multiply)
					{
						st = temp_st;
						end = pos;
						min_ammount_of_multiply = tempMatrix_first[0] * tempMatrix_second[1];
						//cout << "first_check" << endl;
					}
					temp_st = pos - 2 - right_bracket_count * 2;
					//temp_st = left_bracket_previous;
					left_bracket_previous = pos;
					tempMatrix_first[0] = tempMatrix_second[0];
					tempMatrix_first[1] = tempMatrix_second[1];
					right_bracket_count = left_bracket_count = 0;
					matrix_count--;
				}

				for (char bracket : object->brackets)
					bracket == '(' ? right_bracket_count++ : left_bracket_count++;

				if (right_bracket_count > 0 && left_bracket_count == right_bracket_previous) // проверка окончания скобок в одной череде матриц
					bracket_state = 2;

				if (bracket_state == 2)
				{
					if (matrix_count == 0)
					{
						left_bracket_previous = pos;
					}
					else
					{
						if (matrix_count == 2) {
							if (tempMatrix_first[0] * tempMatrix_second[1] < min_ammount_of_multiply && check_validation(listOf_start_end, temp_st, pos))
							{
								min_ammount_of_multiply = tempMatrix_first[0] * tempMatrix_second[1];
								st = temp_st;
								end = pos;
								//cout << "second_check" << endl;
							}
							tempMatrix_first[0] = tempMatrix_second[0];
							tempMatrix_first[1] = tempMatrix_second[1];
							matrix_count--;
							//temp_st = pos - 4;
							temp_st = left_bracket_previous;
						}
						left_bracket_previous = pos;
						tempMatrix_second = new int[2] {-1, -1};
						right_bracket_count -= left_bracket_count;
						left_bracket_count = 0;
					}
				}


				if (right_bracket_count == 0)
					bracket_state = 0;
				else
					bracket_state = 1;

				right_bracket_previous = right_bracket_count;
				bracket_time = !bracket_time;
			}
			else // проверка матриц
			{
				if (matrix_count == 1)
				{
					if (bracket_state == 1)
					{
						if (tempMatrix_second[0] == -1)
						{
							tempMatrix_second = object->matrix;
							matrix_count++;
						}
						else
							tempMatrix_first[1] = object->matrix[1];
					}
					else
					{
						tempMatrix_second = object->matrix;
						matrix_count++;
					}
				}
				else if (matrix_count == 2)
				{
					if (bracket_state == 1)
					{
						tempMatrix_second[1] = object->matrix[1];
					}
				}
				else
				{
					temp_st = pos - 1;
					tempMatrix_first[0] = object->matrix[0];
					tempMatrix_first[1] = object->matrix[1];
					matrix_count++;
				}
				bracket_time = !bracket_time;
			}
			
			pos++;
		}

		bracket_time = true;
		pos = 0;
		if (end!=0)
			for (cell* object : *matrix_array) {
				if (pos == st)
					object->brackets = object->brackets + '(';
				else if (end != 0 && pos == end)
					object->brackets = ')' + object->brackets;
				pos++;
			}
		listOf_start_end[st].push_back(end);
		out(matrix_array);

		if (end == st)
			break;
	}
}

int create_matrix(int rows, vector<cell*>* matrix_array, int* allowed_numbers = new int[6] {5, 10, 3, 12, 50, 6}) {
	int tempColumns = allowed_numbers[rand() % 6];
	cell* tempCell = new cell;
	tempCell->matrix = new int[2] {rows, tempColumns};
	matrix_array->push_back(tempCell);
	matrix_array->push_back(new cell);
	return tempColumns;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(nullptr));
	
	int* schet = new int[1] {0};

	vector<cell*>* matrix_array = new vector<cell*>;
	vector<cell> false_matrix_array;
	matrix_array->push_back(new cell);

	
	int choice;
	cout << "Ввод автоматом?" << endl
		<< "1 - да |" << "2 - нет" << endl;
	cin >> choice;
	if (choice == 1)
	{
		int tempRows = create_matrix(5, matrix_array);
		for (int i = 0; i < 4; i++)
			tempRows = create_matrix(tempRows, matrix_array);
	}
	else {
		cell* tempCell;
		int tempNum = 0;
		bool allow_cycle = true;
		while (allow_cycle) {
			tempCell = new cell;
			tempCell->matrix = new int[2] {0, 0};
			cout << "Введите матрицу через пробел (000... 000...) (для прекращения введите -1)" << endl;
			for (int i=0; i<2; i++){
				cin >> tempNum;
				if (tempNum == -1){
					allow_cycle = false;
					break;
				}
				tempCell->matrix[i] = tempNum;
			}
			if (allow_cycle){
				matrix_array->push_back(tempCell);
				matrix_array->push_back(new cell);
			}
		}
	}


	for (cell* cell : *matrix_array)
		false_matrix_array.push_back(*cell);

	make_matrix_array_min(matrix_array, schet);

	cout << "Кол-во проходов по \"жадному\" алгоритму :" << schet[0] << endl;

	return 0;
}