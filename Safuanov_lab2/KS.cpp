#include "KS.h"
#include "get.h"
#include <fstream>
#include <iostream>

using namespace std;

int KS::Nextid = 2;

KS::KS()
{
	this->id = Nextid;
	Nextid += 2;
}

void KS::add() {
	cout << "������� �������� �������: ";
	name = get_str();
	cout << "������� ���������� �����: ";
	cin >> num_department;
	while (cin.fail() || cin.peek() != '\n' || num_department < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> num_department;
	}
	cout << "������� ���������� ���������� �����: ";
	cin >> work_department;
	while (cin.fail() || cin.peek() != '\n' ||
		work_department < 0 || work_department > num_department) { // �������� ������� �������, ������ ���� ������
		cin.clear();																								
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> work_department;
	}
	cout << "������� ��� �������������: ";
	cin >> efficiency;
	while (cin.fail() || cin.peek() != '\n' || efficiency < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> efficiency;
	}
}

void KS::view() {
	if (!name.empty()) {
		cout << "					    �������                                                                 " << '\n';
		cout << getid() << endl;
		cout << "�������� ������� - " << name << endl;
		cout << "���������� ����� - " << num_department << endl;
		cout << "���������� ���������� ����� - " << work_department << endl;
		cout << "������������� ������� - " << efficiency << endl;
	}
	else {
		cout << "						�� �����������\n";
	}
}

void KS::change() {
	if (name.empty()) {	// �������� �� ������� ��
		cout << "�� �� ����� ��\n";
	}
	else {
		cout << "������� ����� ������������� � ������: ";
		cin >> efficiency;
		while (cin.fail() || cin.peek() != '\n' || efficiency < 0 || work_department > num_department) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> efficiency;
		}
	}
}

void KS::save() {
	ofstream out;
	if (out.is_open()) {
		out << name << endl;
		out << num_department << endl;
		out << work_department << endl;
		out << efficiency << endl;
		cout << "������ �� ��������� � ����." << endl;
	}
	else {
		cout << "������!";
	}
}

void KS::download() {
	ifstream read;
	if (read.is_open()) {
		read >> name;
		read >> num_department;
		read >> work_department;
		read >> efficiency;
		cout << "������ �� ��������� �� �����." << endl;
	}
	else {
		cout << "������!";
	}
}