#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������
#include <unordered_map> // ���� ������� ��������� ������
#include "pipe.h"
#include "get.h"

using namespace std;

/*struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};*/

void menu() {
	cout << "					    ������� ����������� ��� �����                                               " << endl;
	cout << "1. �������� �����" << endl;
	cout << "2. �������� ��" << endl;
	cout << "3. �������� ��������" << endl;
	cout << "4. ������������� �����" << endl;
	cout << "5. ������������� ��" << endl;
	cout << "6. ���������" << endl;
	cout << "7. ���������" << endl;
	cout << "0. �����" << endl << endl;
}



/*void add_comp_station(comp_station& obj_comp_station) {
	cout << "������� �������� �������: ";
	obj_comp_station.name = get_str();
	cout << "������� ���������� �����: ";
	cin >> obj_comp_station.num_department;
	while (cin.fail() || cin.peek() != '\n' || obj_comp_station.num_department < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_comp_station.num_department;
	}
	cout << "������� ���������� ���������� �����: ";
	cin >> obj_comp_station.work_department;
	while (cin.fail() || cin.peek() != '\n' || 
		obj_comp_station.work_department < 0 || obj_comp_station.work_department > obj_comp_station.num_department) { // �������� ������� �������,
		cin.clear();																								  // ������ ���� ������
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_comp_station.work_department;
	}
	cout << "������� ��� �������������: ";
	cin >> obj_comp_station.efficiency;
	while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_comp_station.efficiency;
	}
}

void view_comp_station(comp_station & obj_comp_station) {
	if (!obj_comp_station.name.empty()) {
		cout << "					    �������                                                                 " << '\n';
		cout << "�������� ������� - " << obj_comp_station.name << '\n';
		cout << "���������� ����� - " << obj_comp_station.num_department << '\n';
		cout << "���������� ���������� ����� - " << obj_comp_station.work_department << '\n';
		cout << "������������� ������� - " << obj_comp_station.efficiency << '\n';
	}
	else {
		cout << "						�� �����������\n";
	}
}

void view(pipe& obj_pipe, comp_station& obj_comp_station) {
	cout << "��� �� ������ ����������? (0 - �����, 1 - ��, ���-�� ������ - ��)\n";
	string choice;
	cin >> choice;
	if (choice == "0") {
		view_pipe(obj_pipe);
	}
	else if (choice == "1") {
		view_comp_station(obj_comp_station);
	}
	else {
		view_pipe(obj_pipe);
		view_comp_station(obj_comp_station);
	}
}

void change_comp_station(comp_station& obj_comp_station) {
	if (obj_comp_station.name.empty()) {	// �������� �� ������� ��
		cout << "�� �� ����� ��\n";
	}
	else {
		cout << "������� ����� ������������� � ������: ";
		cin >> obj_comp_station.efficiency;
		while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0 || obj_comp_station.work_department > obj_comp_station.num_department) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> obj_comp_station.efficiency;
		}
	}
}

void save_comp_station(comp_station& obj_comp_station, ofstream& out) {
	if (out.is_open()) {
		out << obj_comp_station.name << endl;
		out << obj_comp_station.num_department << endl;
		out << obj_comp_station.work_department << endl;
		out << obj_comp_station.efficiency << endl;
		cout << "������ �� ��������� � ����." << endl;
	}
	else {
		cout << "������!";
	}
}

void download_comp_station(comp_station& obj_comp_station, ifstream& read) {
	if (read.is_open()) {
		read >> obj_comp_station.name;
		read >> obj_comp_station.num_department;
		read >> obj_comp_station.work_department;
		read >> obj_comp_station.efficiency;
		cout << "������ �� ��������� �� �����." << endl;
	}
	else {
		cout << "������!";
	}
}*/

int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	unordered_map<int, Pipe> data; 
	while (true) {
		int choice;
		menu();  // �������� ����
		cin.clear();
		cin >> choice;
		while (cin.fail() || cin.peek() != '\n' || choice < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> choice;
		}
		switch (choice) {
			case 1:
			{
				Pipe obj_pipe;

				obj_pipe.add();

				data.insert({ obj_pipe.getid(), obj_pipe });
				break;
			}
			/*case 2:
			{
				add_comp_station(obj_comp_station);
				break;
			}*/
			case 3:
			{
				for (auto const& p : data) {
					{
						Pipe l;
						l = p.second;
						l.view();
					}
				}
				break;
			}
			/*case 4:
			{
				change_pipe(obj_pipe);
				break;
			}
			case 5:
			{
				change_comp_station(obj_comp_station);
				break;
			}*/
			/*case 6:
			{
				ofstream out;
				out.open("file.txt");
				if (!obj_pipe.name.empty()) {
					out << "pipe\n";
					save_pipe(obj_pipe, out);
				}
				if (!obj_comp_station.name.empty()) {
					out << "comp_station\n";
					save_comp_station(obj_comp_station, out);
				}
				break;
			}
			case 7:
			{
				read.open("file.txt");
				if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
					cout << "���� ����!\n";
				}
				else {
					string line;
					while (getline(read, line)) {
						if (line.find("pipe") != string::npos) {
							download_pipe(obj_pipe, read);
						}
						if (line.find("comp_station") != string::npos) {
							download_comp_station(obj_comp_station, read);
						}
					}
				}
				break;
			}*/
			case 0:
			{
				cout << "����� �� ���������";
				exit(0);
			}
			default:
			{
				cout << "������� ����� �� 0 �� 7\n";
				break;
			}
		}
	}
	return 0;
}