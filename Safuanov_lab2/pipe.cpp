#include <iostream>
#include <fstream>

#include "pipe.h"
#include "utils_and_samples.h"

using namespace std;

int Pipe::Nextid = 1;

Pipe::Pipe()
{
	this->id = Nextid;
	Nextid += 1;
}

void Pipe::add() {
	cout << "Введите название трубы: ";
	name = get_str();
	cout << "Введите длину трубы: ";
	length = get_correct_value<int>(1, INT_MAX);
	diameter = get_diameter();
	cout << "Подлежит ли она ремонту?: ";
	maintenance = get_correct_value<bool>(0, 1);
	id_of_entrance = 0;
	id_of_exit = 0;
}

void Pipe::view() {
	if (!name.empty()) {
		cout << "					    Труба                                                                 " << '\n';
		cout << id << endl;
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

void Pipe::change() {
	cout << "Меняется труба с id " << id << '\n';
	cout << "Работает труба или нет(0 - не работает, 1 - работает): ";
	maintenance = get_correct_value(0, 1);
}

void Pipe::save(ofstream& out) {
	if (out.is_open()) {
		out << "pipe" << '\n';
		out << id << '\n';
		out << name << '\n';
		out << length << '\n';
		out << diameter << '\n';
		out << maintenance << '\n';
		out << id_of_entrance << '\n';
		out << id_of_exit << '\n';
		cout << "Данные трубы " << id << " загружены в файл." << '\n';
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
		read >> id_of_entrance;
		read >> id_of_exit;
	}
	else {
		cout << "Ошибка!";
	}
}

void Pipe::connection(int entrance, int exit) {
	id_of_entrance = entrance;
	id_of_exit = exit;
}