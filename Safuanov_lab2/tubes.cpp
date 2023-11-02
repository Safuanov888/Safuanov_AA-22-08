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

template<typename T>

vector<int> press_str(const unordered_map<int, T>& mas, string value) {
	vector<int> g;
	for (auto const& f : mas) {
		T obj;
		int id;
		obj = f.second;
		id = f.first;
		if (obj.name == value) {
			g.push_back(id);
		}
	}
	return g;
}

vector<int> press_bool(const unordered_map<int, Pipe>& mas, bool value) {
	vector<int> g;
	for (auto const& f : mas) {
		Pipe obj;
		int id;
		obj = f.second;
		id = f.first;
		if (obj.maintenance == value) {
			g.push_back(id);
		}
	}
	return g;
}

vector<int> press_double(const unordered_map<int, KS>& mas, double value) {
	vector<int> g;
	for (auto const& f : mas) {
		KS obj;
		int id;
		double percent;
		obj = f.second;
		id = f.first;
		percent = 100 * ((double)(obj.num_department - obj.work_department) / (double)obj.num_department);
		if (percent == value) {
			g.push_back(id);
		}
	}
	return g;
}

template <typename M>

void view_data(unordered_map<int, M>& mas) {
	for (auto const& pair : mas) {
		M value;
		value = pair.second;
		value.view();
	}
}

template <typename F>

void find_id(unordered_map<int, F>& mas, int id) {
	for (auto const& pair : mas) {
		if (id == pair.first) {
			F value;
			value = pair.second;
			value.view();
		}
	}
}

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
				cout << "1 - ���������� ��� �������, 0 - ������������� ����������: ";
				string choice1;
				cin >> choice1;
				if (choice1 == "1") {
					view_data(data_P);
					view_data(data_KS);
				}
				else {
					string choice2;
					vector<int> arr;
					cout << "1 - �����, 0 - ��: ";
					cin >> choice2;
					if (choice2 == "1") {
						string choice3;
						cout << "1 - �� ��������, 0 - �� �������: ";
						cin >> choice3;
						if (choice3 == "1") {
							string name;
							cout << "������� ��������: ";
							cin >> name;
							arr = press_str(data_P, name);
						}
						else {
							bool maintenance;
							cout << "1 - � �������, 0 - ���";
							cin >> maintenance;
							arr = press_bool(data_P, maintenance);
						}
					}
					else {
						string choice4;
						cout << "1 - �� ��������, 0 - �� �������� ����������������� �����: ";
						cin >> choice4;
						if (choice4 == "1") {
							string name;
							cout << "������� ��������: ";
							cin >> name;
							arr = press_str(data_KS, name);
						}
						else {
							double non_working;
							cout << "������� �������: ";
							cin >> non_working;
							arr = press_double(data_KS, non_working);
						}
					}
					for (int id : arr) {
						if (arr[0] % 2 == 1) {
							find_id(data_P, id);
						}
						else {
							find_id(data_KS, id);
						}
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
			case 6:
			{
				ofstream out("file.txt");
				for (auto const& p : data_P) {
					{
						int pipe_id;
						Pipe pipe_value;
						pipe_value = p.second;
						pipe_id = p.first;
						if (!pipe_value.name.empty()) {
							pipe_value.save(out, pipe_id);
						}
					}
				}
				for (auto const& k : data_KS) {
					{
						int ks_id;
						KS ks_value;
						ks_value = k.second;
						ks_id = k.first;
						if (!ks_value.name.empty()) {
							ks_value.save(out, ks_id);
						}
					}
				}
				break;
			}
			case 7:
			{
				ifstream read("file.txt");
				if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
					cout << "���� ����!\n";
				}
				else {
					string line;
					while (getline(read, line)) {
						istringstream iss(line);
						string Name;

						int id;
						iss >> Name >> id;
						if (Name == "pipe") {
							Pipe read_pipe;
							read_pipe.download(read, data_P);
							data_P.insert({ id, read_pipe});
							cout << "������ ����� " << id << " ��������� �� �����." << endl;
						}
						if (Name == "comp") {
							KS read_ks;
							read_ks.download(read, data_KS);
							data_KS.insert({ id, read_ks});
							cout << "������ �� " << id << " ��������� �� �����." << endl;
						}
					}
				}
				break;
			}
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