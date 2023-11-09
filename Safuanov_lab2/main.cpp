#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������
#include <format> 
#include <chrono> // ��� ������ ������� � ������ � ������ �������

#include <unordered_map>  // ��������� ������
#include <unordered_set>

#include "pipe.h"
#include "KS.h"
#include "logging.h"
#include "get.cpp"


using namespace std;
using namespace chrono;

void menu() {
	cout << "					    ������� ����������� ��� �����                                               " << '\n';
	cout << "1. �������� �����" << '\n';
	cout << "2. �������� ��" << '\n';
	cout << "3. �������� ��������" << '\n';
	cout << "4. ������������� �����" << '\n';
	cout << "5. ������������� ��" << '\n';
	cout << "6. ���������" << '\n';
	cout << "7. ���������" << '\n';
	cout << "0. �����" << '\n' << '\n';
}

template <typename T>
vector<int> get_ids(const unordered_map<int, T>& mas) 
{
	unordered_set<int> ids;
	cout << "������� id; ���� ���������, �� -1" << '\n';
	while (1) {
		int id = get_correct_value(0, INT_MAX);
		if (id == -1) {
			break;
		}
		else if (mas.contains(id)) {
			ids.insert(id);
		}
		else {
			cout << "��� ������� � ���� id" << '\n';;
		}
		if (ids.size() == mas.size()) {
			break;
		}
	}
	return vector<int>(ids.begin(), ids.end());
}

template<typename T1, typename T2>
using filter = bool(*)(const T1& mas, T2 param);

template<typename T>
bool filter_by_name(const T& mas, string name) {
	return mas.name.find(name) != string::npos;
}

bool filter_by_status(const Pipe& mas, bool status) {
	return mas.maintenance == status;
}

bool filter_by_non_working(const KS& mas, int non_working) {
	return mas.num_department - mas.work_department == mas.num_department * non_working / 100;
}

template <typename T1, typename T2>
unordered_set<int> find_by_filter(const unordered_map<int, T1>& mas, filter<T1, T2> f, T2 par) {
	unordered_set<int> ids;
	for (auto& pair : mas) {
		if (f(pair.second, par)) {
			ids.insert(pair.first);
		}
	}
	return ids;
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
void view_id(unordered_map<int, F>& mas, int id) {
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
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d-%m-%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	unordered_map<int, Pipe> data_P;
	unordered_map<int, KS> data_KS;
	while (true) {
		menu();  // �������� ����
		cout << "������: ";
		cin.clear();
		int choice = get_correct_value(0, 7);
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
			string choice1 = get_str();
			if (choice1 == "1") {
				view_data(data_P);
				view_data(data_KS);
			}
			else {
				cout << "1 - �����, 0 - ��: ";
				string choice2 = get_str();
				if (choice2 == "1") {
					cout << "1 - �� ��������, 0 - �� �������: ";
					string choice3 = get_str();
					if (choice3 == "1") {
						cout << "������� ��������: ";
						string name = get_str();
						for (int i : find_by_filter(data_P, filter_by_name, name)) {
							view_id(data_P, i);
						}
					}
					else {
						cout << "������� ������: ";
						bool maintenance = get_correct_value(0, 1);
						for (int i : find_by_filter(data_P, filter_by_status, maintenance)) {
							view_id(data_P, i);
						}
					}
				}
				else {
					cout << "1 - �� ��������, 0 - �� �������� ����������������� �����: ";
					string choice4 = get_str();
					if (choice4 == "1") {
						cout << "������� ��������: ";
						string name = get_str();
						for (int i : find_by_filter(data_KS, filter_by_name, name)) {
							view_id(data_KS, i);
						}
					}
					else {
						cout << "������� �������: ";
						int non_working = get_correct_value(0, 100);
						for (int i : find_by_filter(data_KS, filter_by_non_working, non_working)) {
							view_id(data_KS, i);
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			if (!data_P.empty()) {
				cout << "1 - ��������, 0 - ��������� ����: ";
				string choice = get_str();
				vector<int> ids;
				while (1) {
					ids = get_ids(data_P);
					if (ids.empty()) {
						cout << "�� �� ������� id" << '\n';
					}
					else {
						if (choice == "1") {
							for (int id : ids) {
								data_P.erase(id);
							}
						}
						else {
							for (int id : ids) {
								Pipe p;
								p.change(id);
								data_P[id].maintenance = p.maintenance;
							}
						}
					}
					break;
				}
			}
			break;
		}
		case 5:
		{
			if (!data_KS.empty()) {
				cout << "1 - ��������, 0 - ��������� ��: ";
				string choice = get_str();
				vector<int> ids;
				while (1) {
					ids = get_ids(data_KS);
					if (ids.empty()) {
						cout << "�� �� ������� id" << '\n';
					}
					else {
						if (choice == "1") {
							for (int id : ids) {
								data_KS.erase(id);
							}
						}
						else {
							for (int id : ids) {
								KS ks;
								ks.change(id, data_KS[id].num_department);
								data_KS[id].work_department = ks.work_department;
							}
						}
					}
					break;
				}
			}
			break;
		}
		case 6:
		{
			cout << "������� �������� ����� ��� ������: ";
			string in_file = get_str() + ".txt";
			ofstream out(in_file);
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
			cout << "������� �������� ����� ��� ��������: ";
			string read_file = get_str();
			ifstream read(read_file);
			if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
				cout << "����� �� ����������!\n";
			}
			else {
				string Name;
				while (getline(read, Name)) {
					if (Name == "pipe") {
						Pipe read_pipe;
						read_pipe.download(read);
						data_P.insert({ read_pipe.getid(), read_pipe });
						cout << "������ ����� " << read_pipe.getid() << " ��������� �� �����." << '\n';
					}
					if (Name == "comp") {
						KS read_ks;
						read_ks.download(read);
						data_KS.insert({ read_ks.getid(), read_ks });
						cout << "������ �� " << read_ks.getid() << " ��������� �� �����." << '\n';
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