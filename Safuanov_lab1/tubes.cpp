#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������
#include <unordered_map> // ���� ������� ��������� ������
#include "pipe.h"
#include "KS.h"
#include "get.h"


using namespace std;

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

void unordered_map_view(const unordered_map<int, Pipe>& pipe, const unordered_map<int, KS>& ks) {
	for (auto const& p : pipe) {
		{
			Pipe value;
			value = p.second;
			value.view();
		}
	}
	for (auto const& k : ks) {
		{
			KS value;
			value = k.second;
			value.view();
		}
	}
}

/*void view(pipe& obj_pipe, comp_station& obj_comp_station) {
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
}*/

int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	unordered_map<int, Pipe> data_P; 
	unordered_map<int, KS> data_KS;
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

				data_P.insert({ obj_pipe.getid(), obj_pipe });
				break;
			}
			case 2:
			{
				KS obj_comp_station;

				obj_comp_station.add();

				data_KS.insert({ obj_comp_station.getid(), obj_comp_station });
				break;
			}
			case 3:
			{
				for (auto const& p : data_P) {
					{
						Pipe l;
						l = p.second;
						l.view();
					}
				}
				for (auto const& k : data_KS) {
					{
						KS l;
						l = k.second;
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