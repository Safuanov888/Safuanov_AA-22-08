#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������

using namespace std;

struct pipe {
	string name;
	int length;
	int diameter;
	bool maintenance;
};

struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};

string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
}

void add_pipe(pipe& obj_pipe) {
	cout << "������� �������� �����: ";
	obj_pipe.name = get_str();
	cout << "������� ����� �����: ";
	cin >> obj_pipe.length;
	while (cin.fail() || cin.peek() != '\n' || obj_pipe.length < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_pipe.length;
	}
	cout << "������� ������� �����: ";
	cin >> obj_pipe.diameter;
	while (cin.fail() || cin.peek() != '\n' || obj_pipe.diameter < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_pipe.diameter;
	}
	cout << "�������� �� ��� �������?: ";
	cin >> obj_pipe.maintenance;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		cin >> obj_pipe.maintenance;
	}
}

void add_comp_station(comp_station& obj_comp_station) {
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
		obj_comp_station.work_department < 0 || obj_comp_station.work_department > obj_comp_station.num_department) { // �������� ������� ������� 
		cin.clear();																								// ������ ���� ������
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

void rewiew(pipe& obj_pipe, comp_station& obj_comp_station) {
	if (!obj_pipe.name.empty()) {
		cout << "					    �����                                                                 " << '\n';
		cout << "�������� ����� - " << obj_pipe.name << '\n';
		cout << "����� ����� - " << obj_pipe.length << '\n';
		cout << "������� ����� - " << obj_pipe.diameter << '\n';
		if (obj_pipe.maintenance == 1) {
			cout << "������?: Yes\n";
		}
		else {
			cout << "������?: No\n";
		}
	}
	else {
		cout << "						����� �����������\n";
	}
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

void change_pipe(pipe& obj_pipe) {
	if (obj_pipe.name.empty()) {        // �������� �� ������� �����
		cout << "�� �� ����� �����\n";
	}
	else {
		cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
		cin >> obj_pipe.maintenance;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> obj_pipe.maintenance;
		}
	}
}

void change_comp_station(comp_station& obj_comp_station) {
	if (obj_comp_station.name.empty()) {	// �������� �� ������� ��
		cout << "�� �� ����� ��\n";
	}
	else {
		cout << "������� ����� ������������� � ������: ";
		cin >> obj_comp_station.efficiency;
		while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> obj_comp_station.efficiency;
		}
	}
}

void save_pipe(pipe& obj_pipe, ofstream& out) {
	if (out.is_open()) {
		out << obj_pipe.name;
		out << obj_pipe.length;
		out << obj_pipe.diameter;
		out << obj_pipe.maintenance;
	}
	else {
		cout << "������!";
	}
	cout << "������ ������� ��������� � ����." << endl;
}

void save_comp_station(comp_station& obj_comp_station, ofstream& out) {
	if (out.is_open()) {
		out << obj_comp_station.name;
		out << obj_comp_station.num_department;
		out << obj_comp_station.work_department;
		out << obj_comp_station.efficiency;
	}
	else {
		cout << "������!";
	}
	cout << "������ ������� ��������� � ����." << endl;
}

void download_info(pipe& obj_pipe, comp_station& obj_comp_station) {
	ifstream outputFile("file.txt");
	if (outputFile.is_open()) {
		outputFile >> obj_pipe.name;
		outputFile >> obj_pipe.length;
		outputFile >> obj_pipe.diameter;
		outputFile >> obj_pipe.maintenance;
		outputFile >> obj_comp_station.num_department;
		outputFile >> obj_comp_station.name;
		outputFile >> obj_comp_station.work_department;
		outputFile >> obj_comp_station.efficiency;
	}
	else {
		cout << "������!";
	}
	outputFile.close();
	cout << "������ ������� ��������� �� �����." << endl;
}


int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	pipe obj_pipe;
	comp_station obj_comp_station;
	while (true) {
		int choice;
		cout << "					    ������� ����������� ��� �����                                               " << '\n';
		cout << "1. �������� �����" << '\n';
		cout << "2. �������� ��" << '\n';
		cout << "3. �������� ���� ��������" << '\n';
		cout << "4. ������������� �����" << '\n';
		cout << "5. ������������� ��" << '\n';
		cout << "6. ���������" << '\n';
		cout << "7. ���������" << '\n';
		cout << "0. �����" << '\n' << '\n';
		cin.clear();
		cin >> choice;
		while (cin.fail() || cin.peek() != '\n' || choice < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "������ ������� �������, ���������� ��� ���: ";
			cin >> choice;
		}
		ofstream out;
		switch (choice) {
		case 1:
			add_pipe(obj_pipe);
			break;
		case 2:
			add_comp_station(obj_comp_station);
			break;
		case 3:
			rewiew(obj_pipe, obj_comp_station);
			break;
		case 4:
			change_pipe(obj_pipe);
			break;
		case 5:
			change_comp_station(obj_comp_station);
			break;
		case 6:
			out.open("file.txt");
			out.close();
			if (!obj_pipe.name.empty()) {
				out.open("file.txt", ios_base::app);
				out << "p\n";
				save_pipe(obj_pipe, out);
				out.close();
			}
			if (!obj_comp_station.name.empty()) {
				out.open("file.txt", ios_base::app);
				out << "c\n";
				save_comp_station(obj_comp_station, out);
				out.close();
			}
			break;
		case 7:
			download_info(obj_pipe, obj_comp_station);
			break;
		case 0:
			cout << "����� �� ���������";
			exit(0);
		default:
			cout << "������� ����� �� 0 �� 7\n";
			break;
		}
	}
	return 0;
}