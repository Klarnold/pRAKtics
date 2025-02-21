#include<iostream>

using namespace std;

struct dict {
	int size = 1;
	char letter;
	int count=1;
	string path = "";
	dict* next_element=nullptr;
	dict* prev_element = nullptr;
	dict(char _letter) : letter(_letter) {};

	dict* find(char _letter) {
		if (this->letter == _letter)
			return this;
		else
		{
			if (this->next_element == nullptr)
				return nullptr;
			else
				return next_element->find(_letter);
		}
	}

	dict* find(int pos) {
		if (pos != 0)
			if (next_element == nullptr)
				return nullptr;
			else
				return next_element->find(pos - 1);
		else
			return this;
	}

	void add(dict* new_element) {
		this->size += 1;
		if (this->next_element == nullptr)
		{
			this->next_element = new_element;
			this->next_element->prev_element = this;
		}
		else
			this->next_element->add(new_element);
	}

	void sort(dict* head, int st=0) {
		if (this->next_element != nullptr)
		{
			if (this->next_element->count > this->count)
			{
				int temp_st = st;
				dict* temp_dict = this;
				while (temp_dict->prev_element != nullptr)
				{
					if (this->next_element->count > temp_dict->prev_element->count)
					{
						temp_dict = temp_dict->prev_element;
						temp_st--;
					}
					else
						break;
				}
				if (temp_st != 0) {
					this->next_element->prev_element = temp_dict->prev_element;
					temp_dict->prev_element->next_element = this->next_element;
					this->next_element = this->next_element->next_element;
					this->next_element->prev_element = this;
					temp_dict->prev_element = temp_dict->prev_element->next_element;
					temp_dict->prev_element->next_element = temp_dict;
				}
				else
				{
					head = this->next_element;
					this->next_element->size = temp_dict->size;
					temp_dict->prev_element = this->next_element;
					this->next_element = this->next_element->next_element;
					temp_dict->prev_element->next_element = temp_dict;
					this->next_element->prev_element = this;
					temp_dict->prev_element->prev_element = nullptr;
				}
				this->sort(head, st + 1);
			}
			else
				this->next_element->sort(head, st + 1);
		}
		else
			return;
	}

	void out() {
		int pos = 0;
		dict* temp_slovarb = this->find(pos);
		while (temp_slovarb != nullptr)
		{
			cout << temp_slovarb->letter << " - " << temp_slovarb->count <<  " - " << temp_slovarb->path << endl;
			pos++;
			temp_slovarb = this->find(pos);
		}
		cout << "----------------" << endl;
	}

	int sum(int st, int end) {
		int summ = 0;
		while (st != end)
		{
			summ += this->find(st)->count;
			st++;
		}
		return summ;
	}

	void make_path(int st, int end) {
		int summ = 0;
		int end_pos = 0;
		if (end - st > 1)
		{
			bool phase_of_zeroes = true;
			for (int i = st; i < end; i++)
			{
				if (phase_of_zeroes)
				{
					this->find(i)->path += "0";
					summ += this->find(i)->count;
					if (summ >= (this->sum(st, end) / 2) || ((summ + this->find(i+1)->count)>= this->sum(i+1, end)))
					{
						phase_of_zeroes = false;
						end_pos = i + 1;
						this->make_path(st, end_pos);
					}
				}
				else
					this->find(i)->path += "1";
			}
			this->make_path(end_pos, end);
		}
	}

	void sort_path() {
		dict* temp_main_dict = this;
		dict* temp_secondary_dict;
		string temp_path;
		while (temp_main_dict->next_element != nullptr)
		{
			temp_secondary_dict = temp_main_dict->next_element;
			while (temp_secondary_dict != nullptr)
			{
				if (temp_main_dict->path.size() > temp_secondary_dict->path.size())
				{
					temp_path = temp_main_dict->path;
					temp_main_dict->path = temp_secondary_dict->path;
					temp_secondary_dict->path = temp_path;
				}
				temp_secondary_dict = temp_secondary_dict->next_element;
			}
			temp_main_dict = temp_main_dict->next_element;
		}
	}

	int count_bytes() {
		dict* temp_dict = this;
		int summ = 0;
		while (temp_dict != nullptr)
		{
			summ += temp_dict->count * temp_dict->path.length();
			temp_dict = temp_dict->next_element;
		}
		return summ;
	}
};

struct leaf {
	string value = "";
	leaf* right_leaf = nullptr;
	leaf* left_leaf = nullptr;
	leaf* head = nullptr;

	void add_dict(dict* _dict) {
		leaf* temp_leaf = this;
		for (char letter : _dict->path) {
			if (letter == '0')
			{
				if (temp_leaf->left_leaf == nullptr)
				{
					temp_leaf->left_leaf = new leaf("0");
					temp_leaf->left_leaf->head = temp_leaf;
				}
				temp_leaf = temp_leaf->left_leaf;
			}
			else
			{
				if (temp_leaf->right_leaf == nullptr)
				{
					temp_leaf->right_leaf = new leaf("1");
					temp_leaf->right_leaf->head = temp_leaf;
				}
				temp_leaf = temp_leaf->right_leaf;
			}
		}
		temp_leaf->value = temp_leaf->value + " " + _dict->letter;
	}

	leaf(string _value) : value(_value) {};

	void out(string text, bool right=true) {

		if (right) 
			cout << text << "-" << this->value << endl;
		else
			cout << text << "--" << this->value << endl;

		if (this->right_leaf != nullptr)
			this->right_leaf->out(text + "\t|");

		if (this->left_leaf != nullptr)
			this->left_leaf->out(text + "\t", false);
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	string text = "";
	int choice;
	
	cout << "Какая часть задания (1 или 2)?" << endl;
	cin >> choice;
	if (choice == 1)
	{
		text = "Дрынцы-брынцыбубенцы, Раззвонилисьудальцы, Диги-диги-диги-дон, Выхо-ди-скорее-вон!";
		dict* slovarb = new dict(char(tolower(text[0])));
		dict* temp_slovarb;
		slovarb->find(char(tolower(text[0])))->count--;
		for (char letter : text)
		{
			letter = tolower(letter);
			temp_slovarb = slovarb->find(letter);
			if (temp_slovarb != nullptr)
				temp_slovarb->count++;
			else
				slovarb->add(new dict(letter));
		}
		slovarb->out();
		slovarb->sort(slovarb);
		while (slovarb->prev_element != nullptr)
			slovarb = slovarb->prev_element;
		slovarb->make_path(0, slovarb->size);
		slovarb->out();
		cout << slovarb->count_bytes() << endl;
		slovarb->sort_path();
		slovarb->out();
		cout << slovarb->count_bytes() << endl;
		
		leaf* body = new leaf("head");
		for (int i = 0; i < slovarb->size; i++)
			body->add_dict(slovarb->find(i));

		body->out("");
		
	}
	else
	{
		text = "Кузнецов Лев Андреевич";
		dict* slovarb = new dict(char(tolower(text[0])));
		dict* temp_slovarb;
		slovarb->find(char(tolower(text[0])))->count--;
		for (char letter : text)
		{
			letter = tolower(letter);
			temp_slovarb = slovarb->find(letter);
			if (temp_slovarb != nullptr)
				temp_slovarb->count++;
			else
				slovarb->add(new dict(letter));
		}
		slovarb->out();
		slovarb->sort(slovarb);
		while (slovarb->prev_element != nullptr)
			slovarb = slovarb->prev_element;
		slovarb->out();
		string path_text = "";
		for (int i = 0; i < (slovarb->size-1); i++)
		{
			slovarb->find(i)->path=path_text + "0";
			path_text += "1";
		}
		slovarb->find(slovarb->size-1)->path = path_text;
		slovarb->out();
		cout << slovarb->count_bytes() << endl;
		cout << slovarb->size << endl;

		leaf* body = new leaf("head");
		for (int i = 0; i < slovarb->size; i++)
			body->add_dict(slovarb->find(i));

		body->out("");
	}

	return 0;
}