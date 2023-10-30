#include "pipe.h"
#include "get.h"
#include <fstream>
#include <iostream>

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
	cin >> length;
	while (cin.fail() || cin.peek() != '\n' || length < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> length;
	}
	cout << "������� ������� �����: ";
	cin >> diameter;
	while (cin.fail() || cin.peek() != '\n' || diameter < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> diameter;
	}
	cout << "�������� �� ��� �������?: ";
	cin >> maintenance;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> maintenance;
	}
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

void Pipe::change() {
	if (name.empty()) {        // �������� �� ������� �����
		cout << "�� �� ����� �����\n";
	}
	else {
		cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
		cin >> maintenance;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> maintenance;
		}
	}
}

void Pipe::save(ofstream& out, int id) {
	if (out.is_open()) {
		out << "pipe " << id << endl;
		out << name << endl;
		out << length << endl;
		out << diameter << endl;
		out << maintenance << endl << endl;
		cout << "������ ����� " << id << " ��������� � ����." << endl;
	}
	else {
		cout << "������!";
	}
}

void Pipe::download() {
	ifstream read;
	if (read.is_open()) {
		read >> name;
		read >> length;
		read >> diameter;
		read >> maintenance;
		cout << "������ ����� ��������� �� �����." << endl;

	}
	else {
		cout << "������!";
	}
}
