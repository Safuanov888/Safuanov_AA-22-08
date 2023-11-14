#include <iostream>
#include <fstream>

#include "pipe.h"
#include "get.cpp"

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
	cout << "Введите диаметр трубы: ";
	diameter = get_correct_value<int>(1, INT_MAX);
	cout << "Подлежит ли она ремонту?: ";
	maintenance = get_correct_value<bool>(0, 1);
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

	}
	else {
		cout << "Ошибка!";
	}
}