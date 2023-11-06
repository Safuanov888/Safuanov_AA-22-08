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
	cout << "������� �������� �����: ";
	name = get_str();
	cout << "������� ����� �����: ";
	length = get_int();
	cout << "������� ������� �����: ";
	diameter = get_int();
	cout << "�������� �� ��� �������?: ";
	maintenance = get_bool();
}

void Pipe::view() {
	if (!name.empty()) {
		cout << "					    �����                                                                 " << '\n';
		cout << getid() << endl;
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

void Pipe::change(int id) {
	cout << "�������� ����� � id " << id << endl;
	cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
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
		cout << "������ ����� " << id << " ��������� � ����." << endl;
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

	}
	else {
		cout << "������!";
	}
}
