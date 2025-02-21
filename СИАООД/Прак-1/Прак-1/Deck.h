#include<iostream>


using namespace std;

struct Deck {
public:
	Deck* first = nullptr;
	Deck* last = nullptr;
	Deck* next = nullptr;
	unsigned char core = 0;

	Deck(unsigned char _current) : core{ _current } {

	};
	void add(Deck* next) {
		this->next = next;
	}
	void make_first(Deck* first)
	{
		this->first = first;
	}

	void make_last(Deck* last) {
		this->last = last;
	}

	void change_core(unsigned char core) {
		this->core = core;
	}

	/*	Deck* first=nullptr;
Deck* last=nullptr;
Deck* next=nullptr;
unsigned long long core= 0;

Deck(unsigned long long _current) : core{ _current }{

};
void add(Deck* next) {
	this->next = next;
}
void make_first(Deck* first)
{
	this->first = first;
}

void make_last(Deck* last) {
	this->last = last;
}

void change_core(unsigned long long core) {
	this->core = core;
}*/
};