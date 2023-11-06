#include "pipe.h"
#include "get.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

int Pipe::Nextid = 1;

Pipe::Pipe()
{
	this->id = Nextid;
	Nextid += 2;
}

void Pipe::add() {
	cout << "Введите название трубы: ";
	name = get_str();
	cout << "Введите длину трубы: ";
	length = get_int();
	cout << "Введите диаметр трубы: ";
	diameter = get_int();
	cout << "Подлежит ли она ремонту?: ";
	maintenance = get_bool();
}

void Pipe::view() {
	if (!name.empty()) {
		cout << "					    Труба                                                                 " << '\n';
		cout << getid() << endl;
		cout << "Название трубы - " << name << '\n';
		cout << "Длина трубы - " << length << '\n';
		cout << "Диаметр трубы - " << diameter << '\n';
		if (maintenance == 1) {
			cout << "Ремонт?: Yes\n";
		}
		else {
			cout << "Ремонт?: No\n";
		}
	}
	else {
		cout << "						Труба отсутствует\n";
	}
}

void Pipe::change(int id) {
	cout << "Меняется труба с id " << id << endl;
	cout << "Работает труба или нет(0 - не работает, 1 - работает): ";
	bool maintenance = get_bool();
}

void Pipe::save(ofstream& out, int id) {
	if (out.is_open()) {
		out << "pipe" << endl;
		out << id << endl;
		out << name << endl;
		out << length << endl;
		out << diameter << endl;
		out << maintenance << endl;
		cout << "Данные трубы " << id << " загружены в файл." << endl;
	}
	else {
		cout << "Ошибка!";
	}
}

void Pipe::download(ifstream& read) {
	if (read.is_open()) {
		read >> id;
		read >> name;
		read >> length;
		read >> diameter;
		read >> maintenance;

	}
	else {
		cout << "Ошибка!";
	}
}
