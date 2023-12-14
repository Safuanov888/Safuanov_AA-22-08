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
	cout << "������� �������� �����: ";
	name = get_str();
	cout << "������� ����� �����: ";
	length = get_correct_value<int>(1, INT_MAX);
	diameter = get_diameter();
	cout << "�������� �� ��� �������?: ";
	maintenance = get_correct_value<bool>(0, 1);
	id_of_entrance = 0;
	id_of_exit = 0;
}

void Pipe::view() {
	if (!name.empty()) {
		cout << "					    �����                                                                 " << '\n';
		cout << id << endl;
		cout << "�������� ����� - " << name << '\n';
		cout << "����� ����� - " << length << '\n';
		cout << "������� ����� - " << diameter << '\n';
		if (maintenance == 1) {
			cout << "������?: Yes\n";
		}
		else {
			cout << "������?: No\n";
		}
	}
	else {
		cout << "						����� �����������\n";
	}
}

void Pipe::change() {
	cout << "�������� ����� � id " << id << '\n';
	cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
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
		cout << "������ ����� " << id << " ��������� � ����." << '\n';
	}
	else {
		cout << "������!";
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
		cout << "������!";
	}
}

void Pipe::connection(int entrance, int exit) {
	id_of_entrance = entrance;
	id_of_exit = exit;
}